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
	// Timer operations
	theTimer.Reset();
	theTimer.Start();
	m_t = 0.0f;
	m_dt = 1.0f / 60.0f;
	m_dt *= 1000;
	m_frameDeltaTime = 0.0f;

	// Rendering
	m_Renderer.Initialize();

	// Input
	//m_DI = CSGD_DirectInput::GetInstance();
	//m_DI->InitDirectInput(WindowGlobals::g_hWnd,WindowGlobals::g_hInstance,DI_KEYBOARD | DI_MOUSE, DI_MOUSE);
	
	// States
	m_CurrentState = nullptr;

	m_MainGame = new StateMainGame();
	ChangeState(m_MainGame);

	// Events
	m_InputEventSystem = InputEventSystem::GetInstance();

	// Pop the timer once
	//theTimer.GetElapsedTime();

	return true;
}

bool Game::Main()
{
	Input();
	Update();
	Render();

	return true;
}

bool Game::Shutdown()
{
	m_Renderer.Shutdown();
	//m_DI->ShutdownDirectInput();

	return true;
}


////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void Game::Input()
{
	// Get info about our device states
	//m_DI->ReadDevices();

	// Current state input
	m_CurrentState->Input();

}

void Game::Update()
{
	// Process any events
	m_InputEventSystem->ProcessEvents();

	// MIGHT need Semi-fixed timestamp updates for game physics later removed some code here
	// that WAS trying to utilize this, but it was too early and dumb rite now
	// REF: http://gafferongames.com/game-physics/fix-your-timestep/
	m_frameDeltaTime = theTimer.GetElapsedTime();

	// Current state update
	m_CurrentState->Update(m_frameDeltaTime);
}

void Game::Render()
{
	// Current state render
	m_CurrentState->Render();
}

void Game::ChangeState(IGamestate* in)
{
	//TODO: Stack based states

	if(m_CurrentState) {
		m_CurrentState->Exit(); }

	m_CurrentState = in;

	if(m_CurrentState) {
		m_CurrentState->Enter(&m_Renderer); }		
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////

