///////////////////////////////////////////////////////////////////////////
//	File Name	:	"WorldManager.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle operation of a world's entities
///////////////////////////////////////////////////////////////////////////
#ifndef _WORLDMANAGER_H
#define _WORLDMANAGER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <queue>
#include <vector>
#include <set>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IComponent;
class Entity;
class IMessage;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class WorldManager
{
public:
	

	/********** Public Utility Functions ************/
	static WorldManager* GetInstance();
	static void DeleteInstance();
	void Initialize();
	void Update(float deltaTime);
	void Shutdown();
	/********** Public Accessors ************/
	deque<IComponent*>& GetComponentCategory(int componentCategory);

	/********** Public Mutators  ************/	
	void AddEntity(Entity* entity);

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	WorldManager();
	~WorldManager();
	WorldManager(const WorldManager&);
	WorldManager& operator=(const WorldManager&);
	/********** Private Members ************/
	// Singleton instanace
	static WorldManager* m_instance;

	// List of entities
	deque<Entity*> m_entities;
	// Vector of lists of components based on type accessed only by services (rendering / physics)
	vector<deque<IComponent*> > m_componentCategories;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void CleanupEntitiesAndComponents();
	void KillEntity(Entity* entity);
	void KillEntity(int entityId);
};
#endif