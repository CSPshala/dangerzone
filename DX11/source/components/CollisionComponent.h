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
	~CollisionComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	void RegisterForMessages();
	void ReceiveMessage(IMessage* message);
    void ReceiveLocalMessage(CompMessage* message);
	void UnRegisterForMessages();
	virtual bool LoadComponentAttributes(xml_node& component);
	/********** Public Accessors ************/
	virtual string getComponentName();
    virtual rectangle getAABB() {return m_AABB;}
    /** Returns if this entity is dirty this frame (has moved) **/
    bool isDirty() {return m_dirty;}

	/********** Public Mutators  ************/
    /** Overload to set if entity is dirty **/
    void isDirty(bool dirty) {m_dirty = dirty;}

private:
	/********** Private Members ************/
	static const string COLLISION_COMPONENT_NAME;

    // Rectangle for this entity's hit box (until multibox is implemented)
    rectangle m_AABB;
    // dirty flag to let our quadtree know this entity needs updating
    bool m_dirty;
    // Layer we're on (might split collisions based on this)
	int m_layer;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
    void CalculateAABB();
	void RegisterForLocalMessages();
};
#endif