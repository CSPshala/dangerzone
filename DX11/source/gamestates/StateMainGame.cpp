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

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
StateMainGame::StateMainGame()
{
}

StateMainGame::~StateMainGame()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void StateMainGame::Enter(FRenderer* theRenderer)
{
	// Set DI
	m_DI = CSGD_DirectInput::GetInstance();
	// Set renderer
	m_Renderer = theRenderer;
	// Set camera
	m_Camera = theRenderer->GetCamera();
	// Move delta cleared out
	m_MoveDelta = D3DXVECTOR3(0,0,0);
	m_MouseDelta = D3DXVECTOR3(0,0,0);
}

void StateMainGame::Exit()
{
	m_DI = nullptr;
	m_Renderer = nullptr;
}

void StateMainGame::Input()
{
	m_MoveDelta = D3DXVECTOR3(0,0,0);
	m_MouseDelta = D3DXVECTOR3(0,0,0);

	if(m_DI->KeyDown(DIK_W)) {
		m_MoveDelta.z += 10.0f; }

	if(m_DI->KeyDown(DIK_S)) {
		m_MoveDelta.z -= 10.0f; }

	if(m_DI->KeyDown(DIK_D)) {
		m_MoveDelta.x += 10.0f; }

	if(m_DI->KeyDown(DIK_A)) {
		m_MoveDelta.x -= 10.0f; }
	
	// Mouselook
	// Yaw (rotate on camera's Y axis, so X mouse movement
	m_MouseDelta.y = static_cast<float>(m_DI->MouseMovementX());
	// Pitch (rotate on camera's X axis, so Y mouse movement (negative cause I'm a weirdo)
	m_MouseDelta.x = static_cast<float>(-m_DI->MouseMovementY());
}

void StateMainGame::Update(float deltaTime)
{
	// Make sure moveDelta is time-based
	D3DXVec3Scale(&m_MoveDelta,&m_MoveDelta,deltaTime);
	// Set move delta for calculation by camera
	m_Camera->SetMoveDelta(m_MoveDelta);

	// Current rotation
	D3DXVECTOR3 currentRot = m_Camera->GetRotation();
	currentRot.x += m_MouseDelta.x * 0.2f;
	currentRot.y += m_MouseDelta.y * 0.2f;
	m_Camera->SetRotation(currentRot);
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