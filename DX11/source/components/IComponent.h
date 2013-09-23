///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for a component 
///////////////////////////////////////////////////////////////////////////
#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <string>
#include "../xml/pugixml.hpp"
using namespace std;
using namespace pugi;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IMessage;
class Entity;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

class IComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IComponent(int componentType, int componentID = -1);
	~IComponent();

	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime) = 0;
	virtual void ReceiveMessage(IMessage* message) = 0;
	virtual bool LoadComponentAttributes(xml_node& component) = 0;

	/********** Public Accessors ************/	
	virtual string getComponentName() = 0;
	int getComponentType();
	int getComponentID();
	Entity* getParentEntity();

	/********** Public Mutators  ************/		
	void setComponentID(int id);
	void setParentEntity(Entity* entity);	
private:
	/********** Private Members ************/
	// Entity that this component is part of
	Entity* m_parentEntity;
	// ID unique to this component's entity
	int	m_componentID;
	// Integer expressing the type of this component
	int	m_componentType;
	
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif