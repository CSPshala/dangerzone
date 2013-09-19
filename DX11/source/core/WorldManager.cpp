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
#include "../components/CMessages.h"
#include "../components/Entity.h"
#include "../components/IComponent.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
WorldManager* WorldManager::m_instance(nullptr);

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
void WorldManager::Initialize()
{
}

void WorldManager::Update(float deltaTime)
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
		(*iter)->UpdateComponents(deltaTime);
}

void WorldManager::Shutdown()
{
	CleanupEntitiesAndComponents();
}

WorldManager* WorldManager::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new WorldManager;

	return m_instance;
}

void WorldManager::DeleteInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void WorldManager::CleanupEntitiesAndComponents()
{
	for(deque<Entity*>::iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		(*iter)->Shutdown();
		delete (*iter);
		(*iter) = nullptr;
	}
}

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