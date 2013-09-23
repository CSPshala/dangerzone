///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Game.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Game class
///////////////////////////////////////////////////////////////////////////
#ifndef _GAME_H
#define _GAME_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CTimer.h"
#include "../Globals.h"
#include "../rendering/ForwardRenderer.h"
#include "../gamestates/StateMainGame.h"
#include "../events/InputEventSystem.h"
#include "../input/RawInputParser.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Game
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Game();
	~Game();

	/********** Public Utility Functions ************/
	bool Initialize();
	bool Main();
	bool Shutdown();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	
		// Semi-Fixed timestep stuff
		CTimer theTimer;	
		float m_t;
		float m_dt;
		float m_frameDeltaTime;

		// Rendering
		FRenderer* m_Renderer;

		// States
		IGamestate*	   m_CurrentState;
		StateMainGame* m_MainGame;

		// Events
		InputEventSystem*	m_InputEventSystem;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool Input();
	void Update();
	void Render();

	void ChangeState(IGamestate* in);

};
#endif