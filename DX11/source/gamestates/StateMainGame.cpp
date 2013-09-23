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
#include "../rendering/ForwardRenderer.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
StateMainGame::StateMainGame(std::string levelListFilename) : m_Camera(nullptr),
	m_levelListFilename(levelListFilename)
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
	// Set camera
	m_Camera = FRenderer::GetInstance()->GetCamera();
	// Move delta cleared out
	m_MoveDelta = D3DXVECTOR3(0,0,0);
	m_MouseDelta = D3DXVECTOR3(0,0,0);
	//Start up worldmanager then loader to populate it
	m_worldManager.Initialize();
	m_levelLoader.Initialize(m_levelListFilename,&m_worldManager);
	m_levelLoader.NextLevel();	
}

void StateMainGame::Exit()
{	
	m_levelLoader.Shutdown();
	m_worldManager.Shutdown();
}

void StateMainGame::Input()
{

}

void StateMainGame::Update(float deltaTime)
{
	m_worldManager.Update(deltaTime);	

	m_Camera->Render();
}

void StateMainGame::Render()
{	
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