
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	File Name	:	"PointCollisionComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle behavior of a rectangular collidable object
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "PointCollisionComponent.h"
#include "RectCollisionComponent.h"
#include "Entity.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string PointCollisionComponent::POINT_COLLISION_COMPONENT_NAME("point_collision");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
PointCollisionComponent::PointCollisionComponent(int componentType, int componentID) :
	CollisionComponent(componentType, componentID)
{
}

PointCollisionComponent::~PointCollisionComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void PointCollisionComponent::Update(float deltaTime)
{
	if(isDirty())
        CalculatePoint();
}

bool PointCollisionComponent::LoadComponentAttributes(xml_node& component)
{    
	setLayer(component.attribute("layer").as_int());
	setOffset(vec3<float>(component.attribute("offsetX").as_float(),
		component.attribute("offsetY").as_float(),0.0f));

    return true;
}

bool PointCollisionComponent::CheckCollision(CollisionComponent* other)
{
	switch(other->getComponentType())
	{
	case ENUMS::COMPONENTS::RECT_COLLISION:
		{
			return isPointContained(mPoint, static_cast<RectCollisionComponent*>(other)->getAABB());
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
bool PointCollisionComponent::isPointContained(vec3<float>& point, rectangle& rect)
{
	return ((point.x > rect.Min.x) && (point.x < rect.Max.x) &&
		   (point.y > rect.Min.y) && (point.y < rect.Max.y));
}

void PointCollisionComponent::CalculatePoint()
{
	vec3<float> entPos(getParentEntity()->GetPosition());
	mPoint = entPos + mOffset;
}

void PointCollisionComponent::handleCollisions(CollidingMsg* message)
{	
	// Ease of access to colliding with vector
	vector<CollisionComponent*>& collidingWith = *(message->mCollidingWith);
	// Separate shape types
	vector<PointCollisionComponent*> rectCol;
	for(unsigned int i = 0; i < collidingWith.size(); ++i)
	{
		switch(collidingWith[i]->getComponentType())
		{
		case ENUMS::COMPONENTS::POINT_COLLISION:
			{
				rectCol.push_back(static_cast<PointCollisionComponent*>(collidingWith[i]));
			}
			break;
		case ENUMS::COMPONENTS::CIRCLE_COLLISION:
			{
			}
			break;
		default:
			{
				LOG("A PointCollisionComponent received an unrecognized shape.");					
			}
		}
	}

	// Handle collision based on type
	handlePointangleCollisions(rectCol);
}

void PointCollisionComponent::handlePointangleCollisions(
	vector<PointCollisionComponent*>& collidingWith)
{
	// TODO: MULTIPLE COLLISION TESTING
	
	vec3<float> correctionVec;

	// Handle all possible collisions, only using the smallest possible corrections
	for(unsigned int objIndex = 0; objIndex < collidingWith.size(); ++objIndex)
	{
		// For now only handle the first collision
		vec3<float> objectCenter = collidingWith[objIndex]->getParentEntity()->GetPosition();
		rectangle objectPoint = collidingWith[objIndex]->getAABB();

		// Doing 2D AABB stuff, same as 3D w/o the 3, duhhhhhhhh #STEELRESERVE
		vec3<float> direction = getParentEntity()->GetPosition() - objectCenter;

		//Get extents
		vec3<float> ExtentOne = this->getAABB().Max - getParentEntity()->GetPosition();
		vec3<float> ExtentTwo = objectPoint.Max - objectCenter;

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
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string PointCollisionComponent::getComponentName()
{
    return PointCollisionComponent::POINT_COLLISION_COMPONENT_NAME;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////