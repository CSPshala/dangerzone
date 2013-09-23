///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Game.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Main game loops and stuffs
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "Game.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Game::Game()
{
}

Game::~Game()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool Game::Initialize()
{
	bool result = true;

	// Events
	m_InputEventSystem = InputEventSystem::GetInstance();
	m_Renderer = FRenderer::GetInstance();
	
	// Timer operations
	theTimer.Reset();
	theTimer.Start();
	m_t = 0.0f;
	m_dt = 1.0f / 60.0f;
	m_dt *= 1000;
	m_frameDeltaTime = 0.0f;
	// Rendering
	m_Renderer->Initialize();
	
	// States
	m_CurrentState = nullptr;

	m_MainGame = new StateMainGame("levellist");
	ChangeState(m_MainGame);	

	return result;
}

bool Game::Main()
{
	if(!Input())
		return false;
	Update();
	Render();

	return true;
}

bool Game::Shutdown()
{
	ChangeState(nullptr);
	delete m_MainGame;

	// Shut down all game level singletons
	m_Renderer->Shutdown();
	m_Renderer->DeleteInstance();
	m_InputEventSystem->DeleteInstance();

	return true;
}


////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool Game::Input()
{
	// Process any input events
	if(!m_InputEventSystem->ProcessEvents())
		return false;

	return true;
}

void Game::Update()
{
	// MIGHT need Semi-fixed timestamp updates for game physics later removed some code here
	// that WAS trying to utilize this, but it was too early and dumb rite now
	// REF: http://gafferongames.com/game-physics/fix-your-timestep/
	m_frameDeltaTime = theTimer.GetElapsedTime();

	// Current state update
	m_CurrentState->Update(m_frameDeltaTime);
}

void Game::Render()
{
	m_Renderer->RenderQueue();
}

void Game::ChangeState(IGamestate* in)
{
	//TODO: Stack based states

	if(m_CurrentState) {
		m_CurrentState->Exit(); }

	m_CurrentState = in;

	if(m_CurrentState) {
		m_CurrentState->Enter(); }		
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////

