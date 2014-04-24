///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle an entity's collision
///////////////////////////////////////////////////////////////////////////
#ifndef _COLLISIONCOMPONENT_H
#define _COLLISIONCOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "IComponent.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
class CollisionComponent : public IComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
    /** Component typbe MUST be set at construction 
	    based on data driven component type ID from LevelLoader */
	CollisionComponent(int componentType, int componentID = -1);
	virtual ~CollisionComponent();
	/********** Public Utility Functions ************/
	void RegisterForMessages();
	void ReceiveMessage(IMessage* message);
	void UnRegisterForMessages();
	virtual bool CheckCollision(CollisionComponent* other) = 0;

	/********** Public Accessors ************/
	int getLayer() {return m_layer;}
    bool getIsIgnoringLayer() {return m_ignoreLayer;}
    /** Returns if this entity is dirty this frame (has moved) **/
    bool isDirty() {return m_dirty;}

	/********** Public Mutators  ************/
	void setLayer(int layer) {m_layer = layer;}
    void setIgnoreLayer(bool ignore) {m_ignoreLayer = ignore;}
    /** Overload to set if entity is dirty **/
    void isDirty(bool dirty) {m_dirty = dirty;}

private:
	/********** Private Members ************/
    // dirty flag to let our quadtree know this entity needs updating
    bool m_dirty;
    // If this is set, component ignores layer for collisions 
    // Effectively it collides w/ any collidable on any layer
    bool m_ignoreLayer;
    // Layer we're on (might split collisions based on this)
	int m_layer;   

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
    
	void RegisterForLocalMessages();
	void _ReceiveLocalMessage(CompMessage* message);
    // This is for collision components to handle any messages specific to themselves
    virtual void _HandleChildMessages(CompMessage* message) = 0;

	virtual void handleCollisions(CollidingMsg* message) = 0;
};
#endif