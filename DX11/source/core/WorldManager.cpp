///////////////////////////////////////////////////////////////////////////
//	File Name	:	"WorldManager.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle operation of a world's entities
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "WorldManager.h"
#include "../messaging/CMessages.h"
#include "../components/Entity.h"
#include "../components/IComponent.h"
#include "LevelLoader.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////


///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
WorldManager::WorldManager()
{	
	for(int i = 0; i < ENUMS::COMPONENTS::INVALID_COMPONENT; ++i)
		m_componentCategories.push_back(deque<IComponent*>());
}

WorldManager::~WorldManager()
{	
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool WorldManager::Initialize()
{	
	return true;
}

void WorldManager::Update(float deltaTime)
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		(*iter)->Update(deltaTime);
}

void WorldManager::RenderEntities()
{
	// Render message
	RenderMsg msg;

	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		(*iter)->SendLocalMessage(&msg);
}

void WorldManager::Shutdown()
{	
	CleanupEntities();
}

void WorldManager::CleanupEntities()
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		(*iter)->Shutdown();
		delete (*iter);
		(*iter) = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void WorldManager::KillEntity(Entity* entity)
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		if((*iter) == entity)
		{
			(*iter)->Shutdown();
			delete (*iter);
			m_entities.erase(iter);
			return;
		}
}

void WorldManager::KillEntity(int entityId)
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		if((*iter)->GetEntityID() == entityId)
		{
			(*iter)->Shutdown();
			delete (*iter);
			m_entities.erase(iter);
			return;
		}
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
deque<IComponent*>& WorldManager::GetComponentCategory(int componentCategory)
{
	return m_componentCategories[componentCategory];
}

void WorldManager::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
	
	for(unsigned int i = 0; i < ENUMS::COMPONENTS::INVALID_COMPONENT; ++i)
	{
		IComponent* toAdd = entity->GetComponent(i);
		if(toAdd)
			m_componentCategories[i].push_back(toAdd);	
	}
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////