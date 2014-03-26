///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for a component, very little implementation 
//					should take place here
///////////////////////////////////////////////////////////////////////////
#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <string>
#include <vector>
#include "../xml/pugixml.hpp"
using namespace std;
using namespace pugi;

#include "../messaging/IMessageListener.h"
#include "../messaging/CMessages.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Entity;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

class IComponent : public IMessageListener
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IComponent(int componentType, int componentID = -1);
	~IComponent();

	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime) = 0;	
	// Register and all that is set to pure because I want all components
	// to know and handle every message they need EXPLICITLY. Not by base class at all.
	virtual void RegisterForMessages() = 0;
	virtual void ReceiveMessage(IMessage* message) = 0;	
    virtual void ReceiveLocalMessage(CompMessage* message) = 0;
	virtual void UnRegisterForMessages() = 0;
	virtual bool LoadComponentAttributes(xml_node& component) = 0;

	/********** Public Accessors ************/	
	virtual string getComponentName() = 0;
	int getComponentType();
	int getComponentID();
	Entity* getParentEntity();

	/********** Public Mutators  ************/		
	void setComponentID(int id);
	void setParentEntity(Entity* entity);	

protected:
	// Vector of messages to subscribe to upon receipt of ENTITY_REGISTER_LOCAL_MSG
	vector<COMPONENT_MESSAGE_TYPE> m_messageSubs;

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
	virtual void RegisterForLocalMessages() = 0;

};
#endif