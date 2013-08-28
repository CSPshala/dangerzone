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
#include "CSGD_DirectInput.h"
#include "../gamestates/StateMainGame.h"
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
		FRenderer m_Renderer;

		// Input
		CSGD_DirectInput* m_DI;

		// States
		IGamestate*	   m_CurrentState;
		StateMainGame* m_MainGame;


	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void Input();
	void Update();
	void Render();

	void ChangeState(IGamestate* in);

};
#endif