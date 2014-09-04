///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle an entity's collision
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CollisionComponent.h"
#include "../messaging/MessageManager.h"
#include "Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
CollisionComponent::CollisionComponent(int componentType, int componentID) : IComponent(componentType, componentID),
    m_dirty(true), m_ignoreLayer(false)
{    
}

CollisionComponent::~CollisionComponent()
{    
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::RegisterForMessages()
{    
    // Register ourself with the CollisionQuadTree
    RegisterForCollisionMsg* newMsg = new RegisterForCollisionMsg;
    newMsg->mRegister = this;
    MessageManager::GetInstance()->Send(newMsg);   
}

void CollisionComponent::ReceiveMessage(IMessage* message)
{
}

void CollisionComponent::RegisterForLocalMessages()
{
}

void CollisionComponent::UnRegisterForMessages()
{
    // Tell collision system we're unregistered
    UnregisterForCollisionMsg* newMsg = new UnregisterForCollisionMsg;
    newMsg->mUnregister = this;
    MessageManager::GetInstance()->Send(newMsg);
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::_ReceiveLocalMessage(CompMessage* message)
{
    switch(message->GetType())
	{
	case ENTITY_DIRTY:
		{
			m_dirty = true;
		}
		break;
	case ENTITY_COLLIDING:
		{
			handleCollisions(static_cast<CollidingMsg*>(message));
		}
		break;
	}
}



////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
int CollisionComponent::getLayer()
{
	return getParentEntity()->GetLayer();
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////