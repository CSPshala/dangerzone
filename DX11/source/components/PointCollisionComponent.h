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
	virtual bool LoadComponentAttributes(xml_node& component);
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

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void CalculatePoint();

	virtual void handleCollisions(CollidingMsg* message);

	void handleRectangleCollisions(vector<PointCollisionComponent*>& collidingWith);
	

	/** Check two rectangles against each other for collisions */
	bool isPointContained(vec3<float>& point, rectangle& rect);
};
#endif