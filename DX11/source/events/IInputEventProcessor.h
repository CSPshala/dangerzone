///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IInputEventProcessor.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for an event processor recieve events
///////////////////////////////////////////////////////////////////////////
#ifndef _IInputEventProcessor_H
#define _IInputEventProcessor_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "InputEventSystem.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IInputEventProcessor
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/
	void RegisterForEvents();
	void UnRegisterForEvents();
	virtual void ReceiveAndHandleEvent(int event) = 0;
	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif