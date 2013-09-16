///////////////////////////////////////////////////////////////////////////
//	File Name	:	"TestObject.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Object to test 2d rendering
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "TestObject.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
TestObject::TestObject() : mPosX(0.0f), mPosY(0.0f), mVelX(0.0f), mVelY(0.0f), mInputFlags(0),
	mLSXMod(0.0f), mRSXMod(0.0f), mLSYMod(0.0f), mRSYMod(0.0f), mKeyMove(true)
{
	m_diffuseContext.Initialize(L"paperbowser.png",64,64);
	RegisterForEvents();
}

TestObject::~TestObject()
{
	m_diffuseContext.Shutdown();
	UnRegisterForEvents();
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void TestObject::Update(float deltaTime)
{	
	// Update velocities then add to position
	if(mKeyMove)
	{
		mVelY = 500.0f  * ((mInputFlags & DOWN) > 1);
		mVelY -= 500.0f * (mInputFlags & UP);
		mVelX = 500.0f  * ((mInputFlags & RIGHT) > 3);
		mVelX -= 500.0f * ((mInputFlags & LEFT) > 2);
	}
	else
	{
		// Joystick movement
		mVelY = 500.0f  * mLSYMod;		 
		mVelX = 500.0f  * mLSXMod;
	}

	mPosY += mVelY * deltaTime;
	mPosX += mVelX * deltaTime;

	m_diffuseContext.Update(mPosX,mPosY);
}

void TestObject::Render()
{
	m_diffuseContext.Render();
}

void TestObject::ReceiveAndHandleEvent(int event)
{
	switch(event)
	{
	case InputEventSystem::UP:
		{
			LOG("UP * ");
			mInputFlags ^= UP;
		}
		break;
	case InputEventSystem::DOWN:
		{
			LOG("DOWN * ");
			mInputFlags ^= DOWN;
		}
		break;
	case InputEventSystem::LEFT:
		{
			LOG("LEFT * ");
			mInputFlags ^= LEFT;
		}
		break;
	case InputEventSystem::RIGHT:
		{
			LOG("RIGHT * ");
			mInputFlags ^= RIGHT;
		}
		break;
	case InputEventSystem::JUMP:
		{
			mInputFlags ^= JUMP;
		}
		break;
	case InputEventSystem::ATTACK:
		{
			mInputFlags ^= ATTACK;
		}
		break;
	};

	// If we make it here, then keyboard input is going on
	mKeyMove = true;
}

void TestObject::ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo event)
{
	mLSXMod = static_cast<float>(event.mLeftStickX) / 32768.0f;
	mLSYMod = -static_cast<float>(event.mLeftStickY) / 32768.0f;
	mRSXMod = static_cast<float>(event.mRightStickX) / 32768.0f;
	mRSYMod = static_cast<float>(event.mRightStickY) / 32768.0f;

	// Clamp
	if(G_FLOAT_EPSILON(mLSXMod,1.0f))
		mLSXMod = 1.0f;
	if(G_FLOAT_EPSILON(mLSYMod,1.0f))
		mLSYMod = 1.0f;
	if(G_FLOAT_EPSILON(mRSXMod,1.0f))
		mRSXMod = 1.0f;
	if(G_FLOAT_EPSILON(mRSYMod,1.0f))
		mRSYMod = 1.0f;

	mKeyMove = false;

	if(!(mLSXMod || mLSYMod || mRSXMod || mRSYMod))
		mKeyMove = true;		
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