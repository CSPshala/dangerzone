
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
#include "../messaging/MessageManager.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string PointCollisionComponent::POINT_COLLISION_COMPONENT_NAME("point_collision");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
PointCollisionComponent::PointCollisionComponent(int componentType, int componentID) :
	mOffset(0.0f,0.0f,0.0f), mPoint(0.0f,0.0f,0.0f), mTopDown(false), mFirstCollision(true), mLastColID(-1),
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

		// We've made it a whole round w/o colliding
		// Let object know
		if(mFirstCollision == true && mLastColID != -1)
		{
			MouseStopHover* msg(new MouseStopHover);
			msg->SetEntityID(mLastColID);
			MessageManager::GetInstance()->Send(msg);

			mLastColID = -1;
		}

        mFirstCollision = true;
    }
}

bool PointCollisionComponent::AddAttributeAndValue(const ComponentAttribute* attribute)
{    
	if(attribute->name == "offsetX")
	{
		mOffset.x = attribute->valueF;
		return true;
	}
	else if(attribute->name == "offsetY")
	{
		mOffset.y = attribute->valueF;
		return true;
	}
	else if(attribute->name == "topDownCollide")
	{
		mTopDown = attribute->valueB;
		setIgnoreLayer(attribute->valueB);
		return true;
	}
	else
	{
		LOG("Something tried to register an invalid attribute to a PointCollisionComponent.");
		return false;
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
	case ENUMS::RECT_COLLISION:
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
	mPoint = getParentEntity()->GetPosition() + mOffset;
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
		case ENUMS::RECT_COLLISION:
			{
				rectCol.push_back(static_cast<RectCollisionComponent*>(collidingWith[i]));
			}
			break;
		case ENUMS::CIRCLE_COLLISION:
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
	// Means we collided last frame w/ this object, bail
	// only want to handle this once on entry

	int possibleNewID(collidingWith.front()->getParentEntity()->GetEntityID());

	mFirstCollision = false;

	if(mLastColID == possibleNewID)
	{
		return;
	}
	else if(mLastColID != -1) 
	{
		// Possible case where objects over lap and we don't just
		// hop from colliding to not colliding, but with a new object
		MouseStopHover* msg(new MouseStopHover);
		msg->SetEntityID(mLastColID);
		MessageManager::GetInstance()->Send(msg);
	}	
    
	mLastColID = possibleNewID;

	// TODO: Send a message to light up entity that is pointed at
	MouseHover* msg(new MouseHover);
	msg->SetEntityID(mLastColID);
	MessageManager::GetInstance()->Send(msg);
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