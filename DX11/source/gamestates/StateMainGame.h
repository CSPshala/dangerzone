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

	void Input();
	void Update(float deltaTime);
	void Render();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// Ease of access to camera
	Camera*		m_Camera;

	// Filename of level file
	std::string m_levelListFilename;

	// Movement delta
	D3DXVECTOR3 m_MoveDelta;
	D3DXVECTOR3 m_MouseDelta;

	// World Manager for this state's current level
	WorldManager m_worldManager;
	// Level loader that populates world manager's levels
	LevelLoader m_levelLoader;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	// Don't you copy that
	StateMainGame(StateMainGame& in) {}
};
#endif