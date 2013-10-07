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
#include "../messaging/CMessages.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Entity::Entity(int ID,string entityName) : m_ID(ID), m_entityName(entityName), 
	m_hp(-1), m_velX(0.0f), m_velY(0.0f), m_posX(0.0f), m_posY(0.0f), m_width(0), m_height(0)
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

void Entity::Update(float deltaTime)
{
	if(!m_active)
		return;

	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
		(*iter)->Update(deltaTime);	
}

void Entity::SendLocalMessage(IMessage* msg)
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
		(*iter)->ReceiveMessage(msg);
}

void Entity::Shutdown()
{
	for(deque<IComponent*>::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)		
	{
		if(*iter)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
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

float Entity::GetVelocityX()
{
	return m_velX;
}

float Entity::GetVelocityY()
{
	return m_velY;
}

float Entity::GetPositionX()
{
	return m_posX;
}

float Entity::GetPositionY()
{
	return m_posY;
}

int Entity::GetWidth()
{
	return m_width;
}

int Entity::GetHeight()
{
	return m_height;
}

bool  Entity::IsActive()
{
	return m_active;
}

void Entity::SetHP(int in)
{
}

void Entity::SetVelocityX(float in)
{
	m_velX = in;
}

void Entity::SetVelocityY(float in)
{
	m_velY = in;
}

void Entity::SetPositionX(float in)
{
	m_posX = in;
}

void Entity::SetPositionY(float in)
{
	m_posY = in;
}

void Entity::SetWidth(int width)
{
	m_width = width;
}

void Entity::SetHeight(int height)
{
	m_height = height;
}

void Entity::IsActive(bool active)
{
	m_active = active;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////