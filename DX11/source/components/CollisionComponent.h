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
	void UnRegisterForMessages();
	virtual bool LoadComponentAttributes(xml_node& component);
	/********** Public Accessors ************/
	virtual string getComponentName();

	/********** Public Mutators  ************/

private:
	/********** Private Members ************/
	static const string COLLISION_COMPONENT_NAME;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif