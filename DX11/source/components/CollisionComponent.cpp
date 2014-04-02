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
	// Doing 2D AABB stuff, same as 3D w/o the 3, duhhhhhhhh #STEELRESERVE
	//vec3<float> direction = 
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