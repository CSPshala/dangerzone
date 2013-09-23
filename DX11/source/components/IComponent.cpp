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

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////