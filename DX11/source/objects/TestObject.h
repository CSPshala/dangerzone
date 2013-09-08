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
#include "../rendering/DiffuseContext.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class TestObject
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	TestObject();
	~TestObject();
	/********** Public Utility Functions ************/
	void Update(float deltaTime);
	void Render();
	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	float mPosX, mPosY;
	float mVelX, mVelY;

	// Rendering
	DiffuseContext m_diffuseContext;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif