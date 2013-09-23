///////////////////////////////////////////////////////////////////////////
//	File Name	:	"XboxController.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Encapsulate a single xbox controller's input
///////////////////////////////////////////////////////////////////////////
#ifndef _XBOXCONTROLLER_H
#define _XBOXCONTROLLER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include <XInput.h>
#pragma comment(lib,"XInput.lib")

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class XboxController
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	XboxController(int controllerNumber = -1);
	~XboxController();
	/********** Public Utility Functions ************/
	int GetState(XINPUT_STATE& state);	
	void Vibrate(int leftVal = 0, int rightVal = 0);

	/********** Public Accessors ************/
	int GetControllerNumber();

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	XINPUT_STATE m_state;
	int m_controllerNumber;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif