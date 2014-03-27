///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for a component 
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "IComponent.h"
#include "Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
IComponent::IComponent(int componentType, int componentID) : 
	m_componentType(componentType), m_componentID(componentID), m_parentEntity(nullptr)
{	
}

IComponent::~IComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void IComponent::ReceiveLocalMessage(CompMessage* message)
{
	// Handles registration, everything else falls thru to child receieve
	switch(message->GetType())
	{
	case ENTITY_REGISTER_LOCAL_MSGS:
		{
			for(unsigned int i = 0; i < m_messageSubs.size(); ++i)
				m_parentEntity->RegisterForLocalMessage(m_messageSubs[i],this);		
		}
		break;
	case ENTITY_UNREGISTER_LOCAL_MSGS:
		{
			m_parentEntity->UnRegisterForAllLocalMessages(this);
		}
		break;
	default:
		{
			_ReceiveLocalMessage(message);
		}
		break;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
int IComponent::getComponentType()
{
	return m_componentType;
}

int IComponent::getComponentID()
{
	return m_componentID;
}

Entity* IComponent::getParentEntity()
{
	return m_parentEntity;
}

void IComponent::setComponentID(int id)
{
	m_componentID = id;
}

void IComponent::setParentEntity(Entity* entity)
{
	m_parentEntity = entity;
}

void IComponent::setLocalMessagesToReceieve(vector<COMPONENT_MESSAGE_TYPE>& messages)
{
	m_messageSubs = messages;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////