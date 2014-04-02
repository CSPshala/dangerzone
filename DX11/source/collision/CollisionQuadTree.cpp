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
	m_RootNode->AABB.Min.x = 0.0f;
	m_RootNode->AABB.Max.x = worldWidth;
	m_RootNode->AABB.Min.y = 0.0f;
	m_RootNode->AABB.Max.y = worldHeight;
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
	float halfWidth = parent->AABB.Min.x + (parent->AABB.Width() * 0.5f);
	float halfHeight = parent->AABB.Min.y + (parent->AABB.Height() * 0.5f);		

	parent->childOne = new Node;
	parent->childOne->AABB.Min.x = parent->AABB.Min.x;
	parent->childOne->AABB.Max.x = halfWidth;
	parent->childOne->AABB.Min.y = parent->AABB.Min.y;
	parent->childOne->AABB.Max.y = halfHeight;
	

	parent->childTwo = new Node;
	parent->childTwo->AABB.Min.x = halfWidth;
	parent->childTwo->AABB.Max.x = parent->AABB.Max.x;
	parent->childTwo->AABB.Min.y = parent->AABB.Min.y;
	parent->childTwo->AABB.Max.y = halfHeight;
	
	parent->childThree = new Node;
	parent->childThree->AABB.Min.x = parent->AABB.Min.x;
	parent->childThree->AABB.Max.x = halfWidth;
	parent->childThree->AABB.Min.y = halfHeight;
	parent->childThree->AABB.Max.y = parent->AABB.Max.y;
		
	parent->childThree = new Node;
	parent->childThree->AABB.Min.x = halfWidth;
	parent->childThree->AABB.Max.x = parent->AABB.Max.x;
	parent->childThree->AABB.Min.y = halfHeight;
	parent->childThree->AABB.Max.y = parent->AABB.Max.y;	

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
	return (rectOne.Max.y > rectTwo.Min.y) && (rectOne.Min.y < rectTwo.Max.y) &&
		(rectOne.Min.x < rectTwo.Max.x) && (rectOne.Max.x > rectTwo.Min.x);
}

bool CollisionQuadTree::isPointContained(float posX, float posY, rectangle& rect, float offsetX, float offsetY)
{
	return (posX < (rect.Max.x + offsetX) && posX > (rect.Min.x - offsetX) && 
		posY < (rect.Max.y + offsetY) && posY > (rect.Min.y - offsetY));
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////