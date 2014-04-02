///////////////////////////////////////////////////////////////////////////
//	File Name	:	"StateMainGame.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize new h files
///////////////////////////////////////////////////////////////////////////
#ifndef _STATEMAINGAME_H
#define _STATEMAINGAME_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IGamestate.h"
#include "../core/WorldManager.h"
#include "../core/LevelLoader.h"
#include "../collision/CollisionManager.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////


////////////////////////////////////////
//				MISC
////////////////////////////////////////


class StateMainGame : public IGamestate
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	StateMainGame(std::string levelListFilename);
	~StateMainGame();

	/********** Public Utility Functions ************/
	void Enter();
	void Exit(); 
	void Update(float deltaTime);

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	// Filename of level file
	std::string m_levelListFilename;

	// World Manager for this state's current level
	WorldManager m_worldManager;
	// Level loader that populates world manager's levels
	LevelLoader m_levelLoader;
	// Collision manager handles well...collisions
	CollisionManager m_collisionManager;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	// Don't you copy that
	StateMainGame(StateMainGame& in) {}
};
#endif