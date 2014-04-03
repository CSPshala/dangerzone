///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IGamestate.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize new cpp files
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "StateMainGame.h"
#include "../messaging/MessageManager.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
StateMainGame::StateMainGame(std::string levelListFilename) : m_levelListFilename(levelListFilename)
{
}

StateMainGame::~StateMainGame()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void StateMainGame::Enter()
{	
	//Start up worldmanager then loader to populate it
	MessageManager::GetInstance()->Initialize();
	m_collisionManager.Initialize();
	m_worldManager.Initialize();
	m_levelLoader.Initialize(m_levelListFilename,&m_worldManager);
	m_levelLoader.NextLevel();	
}

void StateMainGame::Exit()
{	
	m_levelLoader.Shutdown();
	m_worldManager.Shutdown();
	m_collisionManager.Shutdown();
	MessageManager::GetInstance()->Shutdown();
}

void StateMainGame::Update(float deltaTime)
{
	MessageManager::GetInstance()->Update(deltaTime);	
	m_worldManager.Update(deltaTime);		
	m_collisionManager.Update(deltaTime);
	m_worldManager.RenderEntities();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////