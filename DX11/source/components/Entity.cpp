///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Entity.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organise an object's components
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "Entity.h"
#include "IComponent.h"
#include "CMessages.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Entity::Entity(int ID) : m_ID(ID)
{
}

Entity::~Entity()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void Entity::AttachComponent(IComponent* component)
{
	m_components.push_back(component);
}

void Entity::RemoveComponent(IComponent* component)
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
		if((*iter) == component)
		{
			iter = m_components.erase(iter);
			break;
		}
}

void Entity::UpdateComponents(float deltaTime)
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
		(*iter)->Update(deltaTime);	
}

void Entity::ReceiveAndDeliverMessage(IMessage* msg)
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
		(*iter)->ReceiveMessage(msg);
}

void Entity::Shutdown()
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
	{
		delete (*iter);
		(*iter) = nullptr;
	}
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
IComponent* Entity::GetComponent(int componentType)
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
		if((*iter)->getComponentType() == componentType)
			return (*iter);	

	return nullptr;
}

int Entity::GetEntityID()
{
	return m_ID;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////