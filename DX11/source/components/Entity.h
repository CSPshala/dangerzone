///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Entity.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organise an object's components
///////////////////////////////////////////////////////////////////////////
#ifndef _ENTITY_H
#define _ENTITY_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <queue>
using namespace std;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IComponent;
class IMessage;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Entity
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Entity(int ID);
	~Entity();

	/********** Public Utility Functions ************/
		// Destructor handles component cleanup
	void AttachComponent(IComponent* component);
	void RemoveComponent(IComponent* component);
	void UpdateComponents(float deltaTime);
	void ReceiveAndDeliverMessage(IMessage* msg);

	void Shutdown();
	/********** Public Accessors ************/
	IComponent* GetComponent(int componentType);
	int			GetEntityID();

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
		// List of components
	deque<IComponent*> m_components;
		// Unique entity ID
	int m_ID;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif