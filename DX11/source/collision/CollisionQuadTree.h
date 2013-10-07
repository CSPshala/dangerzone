///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionQuadTree.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize a quadtree data structure for spacial partitioning
//					Also handles collision logic for entities contained
///////////////////////////////////////////////////////////////////////////
#ifndef _COLLISIONQUADTREE_H
#define _COLLISIONQUADTREE_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <queue>
using namespace std;

#include "../messaging/IMessageListener.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class CollisionComponent;
////////////////////////////////////////
//				MISC
////////////////////////////////////////
struct rectangle 
{
	rectangle();
	float left;
	float top;
	float right;
	float bottom;
	float Width();
	float Height();
};


class CollisionQuadTree : public IMessageListener
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/** When created, needs width and height of the level, creates top parent node */
	CollisionQuadTree(const float worldWidth, const float worldHeight);
	~CollisionQuadTree();

	/********** Public Utility Functions ************/
	 void RegisterForMessages();
	 void ReceiveMessage(IMessage* message);
	 void UnRegisterForMessages();
	 
	 /********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Structs ************/
	/** A node contains 4 possible children, bounds of quadrant and entities contained within 
		Deque of entity,int pairs.  Int is used for "timestamping" iterations and checks */
	struct Node
	{
		Node();
		Node* childOne;
		Node* childTwo;
		Node* childThree;
		Node* childFour;
		rectangle AABB;
		deque<pair<CollisionComponent*,int> > contained;
	};

	/********** Private Members ************/
	/** Arbitrary size to add to the size of quadrants to help push objects lower into tree */
	static const float BORDER_SIZE;
	/** Smallest quadrant size to create, otherwise it would be infinite */
	static const float SMALLEST_QUADRANT_SIZE;
	/** Beginning of the quadtree */
	Node* m_RootNode;
	/** Operation stamp used for "timestamping" entities to avoid multiple checks */
	int m_OpStamp;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	/** NOTE: child1 = top left, child2 = top right, child 3 = bottom left, child 4 = bottom right 
			Pass in a node to create its children if children would be less than smallest quadrant size
			it will not create anything and return false*/
	bool createChildren(Node* parent);
	/** Cleans up all nodes recursively*/
	void clearAndCleanupNodes(Node* parent);
	/** Check two rectangles against each other for collisions */
	bool isRectCollision(rectangle& rectOne, rectangle& rectTwo);
	/** Check if a rectangle + offset contains a point */
	bool isPointContained(float posX, float posY, rectangle& rect, float offsetX = 0.0f, float offsetY = 0.0f);
};
#endif