///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RectCollisionComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle behavior of a rectangular collidable object
///////////////////////////////////////////////////////////////////////////
#ifndef _RECTCOLLISIONCOMPONENT_H
#define _RECTCOLLISIONCOMPONENT_H

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


class RectCollisionComponent : public CollisionComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	RectCollisionComponent(int componentType, int componentID = -1);
	virtual ~RectCollisionComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual bool AddAttributeAndValue(const ComponentAttribute* attribute);
	virtual bool CheckCollision(CollisionComponent* other);

	/********** Public Accessors ************/
	virtual string getComponentName();
	virtual rectangle getAABB() {return m_AABB;}

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	static const string POINT_COLLISION_COMPONENT_NAME;

	// Rectangle for this entity's hit box (until multibox is implemented)
    rectangle m_AABB;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void CalculateAABB();

	virtual void handleCollisions(CollidingMsg* message);

	void handleRectangleCollisions(vector<RectCollisionComponent*>& collidingWith);
	

	/** Check two rectangles against each other for collisions */
	bool isRectCollision(rectangle& rectOne, rectangle& rectTwo);

    virtual void _HandleChildMessages(CompMessage* message);
};
#endif