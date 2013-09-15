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
TestObject::TestObject() : mPosX(0.0f), mPosY(0.0f), mVelX(0.0f), mVelY(0.0f), mInputFlags(0)
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
	mVelY = 500.0f  * ((mInputFlags & DOWN) > 1);
	mVelY -= 500.0f * (mInputFlags & UP);
	mVelX = 500.0f  * ((mInputFlags & RIGHT) > 3);
	mVelX -= 500.0f * ((mInputFlags & LEFT) > 2);

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
			mInputFlags ^= UP;
		}
		break;
	case InputEventSystem::DOWN:
		{
			mInputFlags ^= DOWN;
		}
		break;
	case InputEventSystem::LEFT:
		{
			mInputFlags ^= LEFT;
		}
		break;
	case InputEventSystem::RIGHT:
		{
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