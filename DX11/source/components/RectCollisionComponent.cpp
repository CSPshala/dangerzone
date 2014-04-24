///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RectCollisionComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle behavior of a rectangular collidable object
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "RectCollisionComponent.h"
#include "Entity.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string RectCollisionComponent::POINT_COLLISION_COMPONENT_NAME("rect_collision");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RectCollisionComponent::RectCollisionComponent(int componentType, int componentID) :
	CollisionComponent(componentType, componentID)
{
}

RectCollisionComponent::~RectCollisionComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void RectCollisionComponent::Update(float deltaTime)
{
	if(isDirty())
        CalculateAABB();
}

bool RectCollisionComponent::LoadComponentAttributes(xml_node& component)
{    
	setLayer(component.attribute("layer").as_int());
    return true;
}

bool RectCollisionComponent::CheckCollision(CollisionComponent* other)
{
	switch(other->getComponentType())
	{
	case ENUMS::COMPONENTS::RECT_COLLISION:
		{
			return isRectCollision(m_AABB, static_cast<RectCollisionComponent*>(other)->getAABB());
		}
		break;
	default:
		{
			return false;
		}
		break;
	}	

	return false;
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool RectCollisionComponent::isRectCollision(rectangle& rectOne, rectangle& rectTwo)
{
	return (rectOne.Max.y > rectTwo.Min.y) && (rectOne.Min.y < rectTwo.Max.y) &&
		(rectOne.Min.x < rectTwo.Max.x) && (rectOne.Max.x > rectTwo.Min.x);
}

void RectCollisionComponent::CalculateAABB()
{
    float halfHeight = static_cast<float>(getParentEntity()->GetHeight()) * 0.5f;
    float halfWidth  = static_cast<float>(getParentEntity()->GetWidth()) * 0.5f;

	m_AABB.Min.y = getParentEntity()->GetPosition().y - halfHeight;
    m_AABB.Max.y = getParentEntity()->GetPosition().y + halfHeight;
    m_AABB.Min.x = getParentEntity()->GetPosition().x - halfWidth;
    m_AABB.Max.x = getParentEntity()->GetPosition().x + halfWidth;
}

void RectCollisionComponent::handleCollisions(CollidingMsg* message)
{	
	// Ease of access to colliding with vector
	vector<CollisionComponent*>& collidingWith = *(message->mCollidingWith);
	// Separate shape types
	vector<RectCollisionComponent*> rectCol;
	for(unsigned int i = 0; i < collidingWith.size(); ++i)
	{
		switch(collidingWith[i]->getComponentType())
		{
		case ENUMS::COMPONENTS::RECT_COLLISION:
			{
				rectCol.push_back(static_cast<RectCollisionComponent*>(collidingWith[i]));
			}
			break;
		case ENUMS::COMPONENTS::CIRCLE_COLLISION:
			{
			}
			break;
		default:
			{
				LOG("A RectCollisionComponent received an unrecognized shape.");					
			}
		}
	}

	// Handle collision based on type
	handleRectangleCollisions(rectCol);
}

void RectCollisionComponent::handleRectangleCollisions(
	vector<RectCollisionComponent*>& collidingWith)
{
	// TODO: MULTIPLE COLLISION TESTING
	
	vec3<float> correctionVec;

	// Handle all possible collisions, only using the smallest possible corrections
	for(unsigned int objIndex = 0; objIndex < collidingWith.size(); ++objIndex)
	{
		// For now only handle the first collision
		vec3<float> objectCenter = collidingWith[objIndex]->getParentEntity()->GetPosition();
		rectangle objectRect = collidingWith[objIndex]->getAABB();

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

		// Only add it if it's absolutely greater than our current penetration
		// freakin expensive
		if(fabs(minPen) > fabs(correctionVec.v[minAxis]))
			correctionVec.v[minAxis] = minPen;
	}

	getParentEntity()->SetPosition(getParentEntity()->GetPosition() + correctionVec);
    // refresh our AABB
    CalculateAABB();
}

void RectCollisionComponent::_HandleChildMessages(CompMessage* message)
{
    // Do stuff here if need be.
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string RectCollisionComponent::getComponentName()
{
    return RectCollisionComponent::POINT_COLLISION_COMPONENT_NAME;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////