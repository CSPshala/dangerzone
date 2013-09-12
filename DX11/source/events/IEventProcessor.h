///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IEventProcessor.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for an event processor recieve events
///////////////////////////////////////////////////////////////////////////
#ifndef _IEVENTPROCESSOR_H
#define _IEVENTPROCESSOR_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "EventSystem.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IEventProcessor
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