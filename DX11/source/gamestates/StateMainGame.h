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
#include "../objects/TestObject.h"

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
	StateMainGame();
	~StateMainGame();

	/********** Public Utility Functions ************/
	void Enter(FRenderer* theRenderer);
	void Exit(); 

	void Input();
	void Update(float deltaTime);
	void Render();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	
	// Ease of access to renderer
	FRenderer*	m_Renderer;
	// Ease of access to camera
	Camera*		m_Camera;
	// Test sprite
	TestObject  m_testSprite;

	// Movement delta
	D3DXVECTOR3 m_MoveDelta;
	D3DXVECTOR3 m_MouseDelta;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	// Don't you copy that
	StateMainGame(StateMainGame& in) {}
};
#endif