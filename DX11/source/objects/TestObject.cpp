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
	mVelY = 25.0f * (mInputFlags & UP);
	mVelY -= 25.0f * (mInputFlags & DOWN);
	mVelX = 25.0f * (mInputFlags & RIGHT);
	mVelX -= 25.0f * (mInputFlags & LEFT);

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
	case EventSystem::UP:
		{
			mInputFlags ^= UP;
		}
		break;
	case EventSystem::DOWN:
		{
			mInputFlags ^= DOWN;
		}
		break;
	case EventSystem::LEFT:
		{
			mInputFlags ^= LEFT;
		}
		break;
	case EventSystem::RIGHT:
		{
			mInputFlags ^= RIGHT;
		}
		break;
	case EventSystem::JUMP:
		{
			mInputFlags ^= JUMP;
		}
		break;
	case EventSystem::ATTACK:
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