
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
    mOffset(0.0f,0.0f,0.0f), mPoint(0.0f,0.0f,0.0f), mTopDown(false), mFirstCollision(true),
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
    {
        CalculatePoint();
        mFirstCollision = true;
    }
}

bool PointCollisionComponent::LoadComponentAttributes(xml_node& component)
{    
	setLayer(component.attribute("layer").as_int());
	setOffset(vec3<float>(component.attribute("offsetX").as_float(),
		component.attribute("offsetY").as_float(),0.0f));

    try
    {
        setIgnoreLayer(component.attribute("ignoreLayer").as_bool());
    }
    catch(std::exception e)
    {
        LOG("No 'ignoreLayer' attribute present on this point collision component.");
    }

    try
    {
        mTopDown = component.attribute("topDownCollide").as_bool();
        // if topdown is true, then it needs to ignore layer
        if(mTopDown)
        {
            setIgnoreLayer(true);
        }
    }
    catch(std::exception e)
    {
        LOG("No 'topDownCollide' attribute present on this point collision component.");
    }

    return true;
}

bool PointCollisionComponent::CheckCollision(CollisionComponent* other)
{
    // Skip if top down is activated and we've already collided
    if(mTopDown && !mFirstCollision)         
        return false;   
    

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
	mPoint = entPos + mOffset;
}

void PointCollisionComponent::handleCollisions(CollidingMsg* message)
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
				LOG("A PointCollisionComponent received an unrecognized shape.");					
			}
		}
	}

	// Handle collision based on type
	handleRectCollisions(rectCol);
}

void PointCollisionComponent::handleRectCollisions(
    vector<RectCollisionComponent*>& collidingWith)
{
    mFirstCollision = false;

	// TODO: Send a message to light up entity that is pointed at
   cout << "CONTAINED...";
}

void PointCollisionComponent::_HandleChildMessages(CompMessage* message)
{
    // Do stuff here if need be.
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