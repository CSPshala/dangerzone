///////////////////////////////////////////////////////////////////////////
//	File Name	:	"QuadTree.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize a quadtree data structure for spacial partitioning
//					Also handles collision logic for entities contained
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "CollisionQuadTree.h"
#include "../components/Entity.h"
#include "../messaging/MessageManager.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
const float CollisionQuadTree::BORDER_SIZE(5.0f);
const float CollisionQuadTree::SMALLEST_QUADRANT_SIZE(128);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
CollisionQuadTree::CollisionQuadTree(const float worldWidth, const float worldHeight) : m_RootNode(nullptr), m_OpStamp(0)
{
	m_RootNode = new Node;
	m_RootNode->AABB.left = 0;
	m_RootNode->AABB.right = worldWidth;
	m_RootNode->AABB.top = 0;
	m_RootNode->AABB.bottom = worldHeight;
}

CollisionQuadTree::~CollisionQuadTree()
{
	// Clean up tree memory
	clearAndCleanupNodes(m_RootNode);
}

CollisionQuadTree::Node::Node() : childOne(nullptr), childTwo(nullptr), childThree(nullptr), childFour(nullptr)
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionQuadTree::RegisterForMessages()
{
	MessageManager::GetInstance()->SubscribeForMessageType(this,REGISTER_FOR_COLLISION);
	MessageManager::GetInstance()->SubscribeForMessageType(this,UNREGISTER_FOR_COLLISION);
}

void CollisionQuadTree::ReceiveMessage(IMessage* message)
{
}

void CollisionQuadTree::UnRegisterForMessages()
{
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool CollisionQuadTree::createChildren(Node* parent)
{
	// Verify we're eligible to split this quadrant
	if( parent->AABB.Width() * 0.5f < SMALLEST_QUADRANT_SIZE 
		&& parent->AABB.Height() * -0.5f < SMALLEST_QUADRANT_SIZE )
	{
		return false;
	}

	// Get positions of splitting axis
	float halfWidth = parent->AABB.left + (parent->AABB.Width() * 0.5f);
	float halfHeight = parent->AABB.top + (parent->AABB.Height() * 0.5f);		

	parent->childOne = new Node;
	parent->childOne->AABB.left = parent->AABB.left;
	parent->childOne->AABB.right = halfWidth;
	parent->childOne->AABB.top = parent->AABB.top;
	parent->childOne->AABB.bottom = halfHeight;
	

	parent->childTwo = new Node;
	parent->childTwo->AABB.left = halfWidth;
	parent->childTwo->AABB.right = parent->AABB.right;
	parent->childTwo->AABB.top = parent->AABB.top;
	parent->childTwo->AABB.bottom = halfHeight;
	
	parent->childThree = new Node;
	parent->childThree->AABB.left = parent->AABB.left;
	parent->childThree->AABB.right = halfWidth;
	parent->childThree->AABB.top = halfHeight;
	parent->childThree->AABB.bottom = parent->AABB.bottom;
		
	parent->childThree = new Node;
	parent->childThree->AABB.left = halfWidth;
	parent->childThree->AABB.right = parent->AABB.right;
	parent->childThree->AABB.top = halfHeight;
	parent->childThree->AABB.bottom = parent->AABB.bottom;	

	return true;
}

void CollisionQuadTree::clearAndCleanupNodes(Node* parent)
{
	if(parent)
	{
		if(parent->childOne)
		{
			clearAndCleanupNodes(parent->childOne);
			delete parent->childOne;
			parent->childOne = nullptr;
		}
		if(parent->childTwo)
		{
			clearAndCleanupNodes(parent->childTwo);
			delete parent->childTwo;
			parent->childTwo = nullptr;
		}
		if(parent->childThree)
		{
			clearAndCleanupNodes(parent->childThree);
			delete parent->childThree;
			parent->childThree = nullptr;
		}
		if(parent->childFour)
		{
			clearAndCleanupNodes(parent->childFour);
			delete parent->childFour;
			parent->childFour = nullptr;
		}
	}
}

bool CollisionQuadTree::isRectCollision(rectangle& rectOne, rectangle& rectTwo)
{
	return (rectOne.bottom > rectTwo.top) && (rectOne.top < rectTwo.bottom) &&
		(rectOne.left < rectTwo.right) && (rectOne.right > rectTwo.left);
}

bool CollisionQuadTree::isPointContained(float posX, float posY, rectangle& rect, float offsetX, float offsetY)
{
	return (posX < (rect.right + offsetX) && posX > (rect.left - offsetX) && 
		posY < (rect.bottom + offsetY) && posY > (rect.top - offsetY));
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////