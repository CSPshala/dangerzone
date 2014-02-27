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
	// Register component's local messages	
	m_components.push_back(component);
	// Tell component to register itself.
	component->ReceiveLocalMessage(&RegisterForLocalMsgs());
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

void Entity::RegisterForLocalMessage(COMPONENT_MESSAGE_TYPE type, IComponent* component)
{
	// Try to find the message type first
	map<COMPONENT_MESSAGE_TYPE, deque<IComponent*> >::iterator findIter = m_localSubs.find(type);
	if(findIter != m_localSubs.end())
	{
		// Check vector to make sure component dosen't exist
		deque<IComponent*>::iterator subscIter = findIter->second.begin();
		for(;subscIter != findIter->second.end(); ++subscIter)
		{
			if(*subscIter == component)
			{
				// Log then return, duplicate sub request
				LOG("Component tried to register a second time for LOCAL message: " << type);
				return;
			}
		}

		// Add the component to the list of subscribers if we reach here, not a dupe sub
		findIter->second.push_back(component);
	}
	else
	{
		// Add the msg type and the subscriber, msg does not exist yet in subs
		deque<IComponent*> toAdd;
		toAdd.push_back(component);
		m_localSubs[type] = toAdd;
	}
}

void Entity::UnRegisterForAllLocalMessages(IComponent* component)
{
	map<COMPONENT_MESSAGE_TYPE, deque<IComponent*> >::iterator mapIter = m_localSubs.begin();
	for(;mapIter != m_localSubs.end(); ++mapIter)
	{
		deque<IComponent*>::iterator subscIter = mapIter->second.begin();
		for(;subscIter != mapIter->second.end(); ++subscIter)
		{
			if((*subscIter) == component)
			{
				// Found it, remove it, continue to next subbed message type
				mapIter->second.erase(subscIter);
				break;
			}
		}
	}
}

void Entity::UnRegisterForMessage(COMPONENT_MESSAGE_TYPE type, IComponent* component)
{
	// Try to find the message type first
	map<COMPONENT_MESSAGE_TYPE, deque<IComponent*> >::iterator findIter = m_localSubs.find(type);
	if(findIter != m_localSubs.end())
	{
		// Remove the subscriber from this msg sub	
		deque<IComponent*>::iterator subscIter = findIter->second.begin();
		for(;subscIter != findIter->second.end(); ++subscIter)
		{
			if((*subscIter) == component)
			{
				// Found it, remove it, beat it
				findIter->second.erase(subscIter);
				return;
			}
		}

		LOG("Component tried to unregister for a LOCAL message of type: " << type << " w/o subscribing.");
	}
	else
	{
		LOG("Component tried to unregister for a LOCAL message of type: " << type << " that dosen't exist.");
	}
}

void Entity::SendLocalMessage(CompMessage* msg)
{
	// Get the vector of subscribers
	map<COMPONENT_MESSAGE_TYPE, deque<IComponent*> >::iterator findIter = m_localSubs.find(msg->GetType());
	if(findIter != m_localSubs.end())
	{
		// Send it to all the subs		
		deque<IComponent*>::iterator subscIter = findIter->second.begin();
		for(;subscIter != findIter->second.end(); ++subscIter)
		{
			(*subscIter)->ReceiveLocalMessage(msg);
		}
	}
	else
	{
		// No component is subbed to this msg type, you're an asshole.
		LOG("Component tried to send a LOCAL message of type: " << msg->GetType() << " with no subscribers.");
	}
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