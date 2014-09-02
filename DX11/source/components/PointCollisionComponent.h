///////////////////////////////////////////////////////////////////////////
//	File Name	:	"PointCollisionComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle behavior of a rectangular collidable object
///////////////////////////////////////////////////////////////////////////
#ifndef _POINTCOLLISIONCOMPONENT_H
#define _POINTCOLLISIONCOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CollisionComponent.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class RectCollisionComponent;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class PointCollisionComponent : public CollisionComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	PointCollisionComponent(int componentType, int componentID = -1);
	virtual ~PointCollisionComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual bool AddAttributeAndValue(const ComponentAttribute& attribute);
	virtual bool CheckCollision(CollisionComponent* other);

	/********** Public Accessors ************/
	virtual string getComponentName();
	virtual vec3<float> getPoint() {return mPoint;}
	virtual vec3<float> getOffset() {return mOffset;}

	/********** Public Mutators  ************/
	virtual void setOffset(vec3<float>& offset) {mOffset = offset;}

private:
	/********** Private Members ************/
	static const string POINT_COLLISION_COMPONENT_NAME;

	// Offset of point from entity origin
	vec3<float> mOffset;

	// Absolute position of the point
    vec3<float> mPoint;

    // Is top down collision enabled?
    // Mainly used for mouse to select first collision as only collision (top down)
    bool mTopDown;  
    // Refreshed on update to true to let us know we haven't collided yet this frame
    bool mFirstCollision;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void CalculatePoint();

	virtual void handleCollisions(CollidingMsg* message);

	void handleRectCollisions(vector<RectCollisionComponent*>& collidingWith);	

	/** Check two rectangles against each other for collisions */
	bool isPointContained(vec3<float>& point, rectangle& rect);

    virtual void _HandleChildMessages(CompMessage* message);
};
#endif