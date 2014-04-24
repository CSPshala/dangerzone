///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionManager.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles telling collision components when they're colliding
///////////////////////////////////////////////////////////////////////////
#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../messaging/IMessageListener.h"
#include <deque>
#include <vector>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IMessage;
class CollisionComponent;
////////////////////////////////////////
//				MISC
////////////////////////////////////////

//TODO: When components register for collision, add them to management
//      when coliding send them a local component message with relevant info to fix themselves

//TODO: This is gonna be gross for now, going to use queues. In the future QUADTREES

class CollisionManager : public IMessageListener
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	CollisionManager();
	~CollisionManager();

	/********** Public Utility Functions ************/
	void RegisterForMessages();
	void ReceiveMessage(IMessage* message);
	void UnRegisterForMessages();

	void Initialize();
	void Update(float deltaTime);
	void Shutdown();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// Vector of queues for layers
	vector<deque<CollisionComponent* > > mLayeredCollidables;

    // These components are outside the bounds of layers and get checked against all
    vector<CollisionComponent*> mOmniCollidables;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void AddComponentToLayer(CollisionComponent* comp);
	void RemoveComponentFromLayer(CollisionComponent* comp);
	void CheckLayerForCollisions(deque<CollisionComponent*>& layer);
    // Checks for collisions w/ omni objects. Omni object will handle collision
    void CheckForOmniCollision(CollisionComponent* comp);
};
#endif