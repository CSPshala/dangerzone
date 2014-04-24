///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionManager.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles telling collision components when they're colliding
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CollisionManager.h"
#include "../components/CollisionComponent.h"
#include "../messaging/MessageManager.h"
#include "../messaging/CMessages.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionManager::RegisterForMessages()
{
	MessageManager::GetInstance()->SubscribeForMessageType(this, REGISTER_FOR_COLLISION);
	MessageManager::GetInstance()->SubscribeForMessageType(this, UNREGISTER_FOR_COLLISION);
}

void CollisionManager::ReceiveMessage(IMessage* message)
{
	switch(message->GetType())
	{
	case REGISTER_FOR_COLLISION:
		{			
			AddComponentToLayer(static_cast<RegisterForCollisionMsg*>(message)->mRegister);
		}
		break;
	case UNREGISTER_FOR_COLLISION:
		{
			RemoveComponentFromLayer(static_cast<UnregisterForCollisionMsg*>(message)->mUnregister);
		}
	}
}

void CollisionManager::UnRegisterForMessages()
{
	MessageManager::GetInstance()->UnsubscribeForAllMessages(this);
}

void CollisionManager::Initialize()
{
	RegisterForMessages();
}

void CollisionManager::Update(float deltaTime)
{
	// Gonna be gross for now

	// Go through layers and handle their collisions from highest to lowest layer
    vector<deque<CollisionComponent*> >::reverse_iterator iter = mLayeredCollidables.rbegin();
    for(; iter != mLayeredCollidables.rend(); ++iter)
        CheckLayerForCollisions(*iter);
}

void CollisionManager::Shutdown()
{
	UnRegisterForMessages();
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionManager::AddComponentToLayer(CollisionComponent* comp)
{
    // If ignores layer than it's an omni collision object
    if(comp->getIsIgnoringLayer())
    {
        mOmniCollidables.push_back(comp);
        return;
    }

	unsigned int layer = comp->getLayer();
	// See if our layer exists, if not add layers till it does
	if(layer >= mLayeredCollidables.size())
	{
		for(unsigned int i = mLayeredCollidables.size(); i <= layer; ++i)
			mLayeredCollidables.push_back(deque<CollisionComponent*>());
	}

	// Add it
	mLayeredCollidables[layer].push_back(comp);
}

void CollisionManager::RemoveComponentFromLayer(CollisionComponent* comp)
{
    // TODO: Removal of OMNIs

	unsigned int layer = comp->getLayer();
	// Remove it, if it blows up, that's a problem that needs fixing
	deque<CollisionComponent*>::iterator iter = mLayeredCollidables[layer].begin();
	for(; iter != mLayeredCollidables[layer].end(); ++iter)
	{
		if((*iter) == comp)
		{
			mLayeredCollidables[layer].erase(iter);
			return;
		}
	}

	// If we made it here, there was no component to find, that's wrong
	LOG("Tried to remove a collision component from layer: " << layer << " but was NOT found...");
}

void CollisionManager::CheckLayerForCollisions(deque<CollisionComponent*>& layer)
{
	// Check each thing in layer against other things in layer
	// increments and never checks the same pairs twice
	deque<CollisionComponent*>::iterator checker = layer.begin();
	for(; checker != layer.end(); ++checker)
	{
        // Check object for omni collisions
        CheckForOmniCollision(*checker);

        vector<CollisionComponent*> collidingWith;

		deque<CollisionComponent*>::iterator checkee = checker + 1;
		for(; checkee != layer.end(); ++checkee)
		{
			if((*checker)->CheckCollision((*checkee)))
			{
				collidingWith.push_back(*checkee);
			}
		}

		if(collidingWith.size() > 0)
		{
			// Done checking this object, send it a component message and have it correct itself
			CollidingMsg toSend;
			toSend.mCollidingWith = &collidingWith;
			(*checker)->ReceiveLocalMessage(&toSend);
		}
	}

}

void CollisionManager::CheckForOmniCollision(CollisionComponent* comp)
{    
    unsigned int size = mOmniCollidables.size();
    vector<CollisionComponent*> collidingWith;
    for(unsigned int i = 0; i < size; ++i)
    {
        if(mOmniCollidables[i]->CheckCollision(comp))
        {
            CollidingMsg toSend;
            vector<CollisionComponent*> temp;
            temp.push_back(comp);
            toSend.mCollidingWith = &temp;
            mOmniCollidables[i]->ReceiveLocalMessage(&toSend);
        }
    }
}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////