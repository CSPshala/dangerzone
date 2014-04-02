///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle an entity's collision
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CollisionComponent.h"
#include "../messaging/MessageManager.h"
#include "Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string CollisionComponent::COLLISION_COMPONENT_NAME("collision");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
CollisionComponent::CollisionComponent(int componentType, int componentID) : IComponent(componentType, componentID),
    m_dirty(true)
{    
}

CollisionComponent::~CollisionComponent()
{    
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::Update(float deltaTime)
{
    if(m_dirty)
        CalculateAABB();
}

void CollisionComponent::RegisterForMessages()
{    
    // Register ourself with the CollisionQuadTree
    RegisterForCollisionMsg* newMsg = new RegisterForCollisionMsg;
    newMsg->mRegister = this;
    MessageManager::GetInstance()->Send(newMsg);   
}

void CollisionComponent::ReceiveMessage(IMessage* message)
{
}

void CollisionComponent::RegisterForLocalMessages()
{
}

void CollisionComponent::UnRegisterForMessages()
{
    // Tell collision system we're unregistered
    UnregisterForCollisionMsg* newMsg = new UnregisterForCollisionMsg;
    newMsg->mUnregister = this;
    MessageManager::GetInstance()->Send(newMsg);
}

bool CollisionComponent::LoadComponentAttributes(xml_node& component)
{    
	m_layer = component.attribute("layer").as_int();
    return true;
}

bool CollisionComponent::CheckCollision(CollisionComponent* other)
{
	return isRectCollision(m_AABB, other->getAABB());
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::CalculateAABB()
{
    float halfHeight = static_cast<float>(getParentEntity()->GetHeight()) * 0.5f;
    float halfWidth  = static_cast<float>(getParentEntity()->GetWidth()) * 0.5f;

	m_AABB.Min.y = getParentEntity()->GetPosition().y - halfHeight;
    m_AABB.Max.y = getParentEntity()->GetPosition().y + halfHeight;
    m_AABB.Min.x = getParentEntity()->GetPosition().x - halfWidth;
    m_AABB.Max.x = getParentEntity()->GetPosition().x + halfWidth;
}

void CollisionComponent::_ReceiveLocalMessage(CompMessage* message)
{
    switch(message->GetType())
	{
	case ENTITY_DIRTY:
		{
			m_dirty = true;
		}
		break;
	case ENTITY_COLLIDING:
		{
			handleCollisions(static_cast<CollidingMsg*>(message));
		}
		break;
	}
}

void CollisionComponent::handleCollisions(CollidingMsg* message)
{
	// TODO: HANDLE MULTIPLE COLLISIONS IN ONE FRAME YOU FUCK
	
	// The correction vector
	vec3<float> correctionVec;

	// For now only handle the first collision
	vec3<float> objectCenter = (*message->mCollidingWith)[0]->getParentEntity()->GetPosition();
	rectangle objectRect = (*message->mCollidingWith)[0]->getAABB();

	// Doing 2D AABB stuff, same as 3D w/o the 3, duhhhhhhhh #STEELRESERVE
	vec3<float> direction = getParentEntity()->GetPosition() - objectCenter;

	//Get extents
	vec3<float> ExtentOne = this->getAABB().Max - getParentEntity()->GetPosition();
	vec3<float> ExtentTwo = objectRect.Max - objectCenter;

	float minPen = FLT_MAX;
	int minAxis = 0;
	float pen = 0.0f;

	for(unsigned int i = 0; i < 2; ++i)
	{
		pen = (ExtentOne.v[i] + ExtentTwo.v[i]) - fabs(direction.v[i]);

		// Make sure no correction on non overlapping objects
		if(pen <= 0)
			return;

		if(pen < minPen)
		{
			minPen = pen;
			minAxis = i;
		}
	}

	if(direction.v[minAxis] < 0)
		minPen = -minPen;

	correctionVec.v[minAxis] = minPen;

	getParentEntity()->SetPosition(getParentEntity()->GetPosition() + correctionVec);
}

bool CollisionComponent::isRectCollision(rectangle& rectOne, rectangle& rectTwo)
{
	return (rectOne.Max.y > rectTwo.Min.y) && (rectOne.Min.y < rectTwo.Max.y) &&
		(rectOne.Min.x < rectTwo.Max.x) && (rectOne.Max.x > rectTwo.Min.x);
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string CollisionComponent::getComponentName()
{
    return CollisionComponent::COLLISION_COMPONENT_NAME;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////