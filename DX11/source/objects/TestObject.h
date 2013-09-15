///////////////////////////////////////////////////////////////////////////
//	File Name	:	"TestObject.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Object to test 2d rendering
///////////////////////////////////////////////////////////////////////////
#ifndef _TESTOBJECT_H
#define _TESTOBJECT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../rendering/render contexts/DiffuseContext.h"
#include "../events/IInputEventProcessor.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class TestObject : public IInputEventProcessor
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	TestObject();
	~TestObject();
	/********** Public Utility Functions ************/
	void Update(float deltaTime);
	void Render();
	void ReceiveAndHandleEvent(int event);
	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

	/********** Public Enum ****************/
	enum InputFlags{UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8, JUMP = 16, ATTACK = 32};

private:
	/********** Private Members ************/
	float mPosX, mPosY;
	float mVelX, mVelY;
	int  mInputFlags; // Each bit corresponds to  forwards or backwards velocity

	// Rendering
	DiffuseContext m_diffuseContext;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif