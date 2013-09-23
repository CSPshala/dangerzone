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
class LevelLoader;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class WorldManager
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	WorldManager();
	~WorldManager();
	/********** Public Utility Functions ************/
	bool Initialize();
	void Update(float deltaTime);
	void Shutdown();
	/** WARNING do not call this unless you want ALL objects in world gone **/
	void CleanupEntities();
	/********** Public Accessors ************/
	deque<IComponent*>& GetComponentCategory(int componentCategory);

	/********** Public Mutators  ************/	
	void AddEntity(Entity* entity);	

private:
	/********** Private Members ************/	

	// List of entities
	deque<Entity*> m_entities;
	// Vector of lists of components based on type accessed only by services (rendering / physics)
	vector<deque<IComponent*> > m_componentCategories;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/	
	void KillEntity(Entity* entity);
	void KillEntity(int entityId);
};
#endif