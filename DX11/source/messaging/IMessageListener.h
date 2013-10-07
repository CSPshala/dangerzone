///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IMessageListener.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Defines an interface for message listeners to recieve messages
///////////////////////////////////////////////////////////////////////////
#ifndef _IMESSAGELISTENER_H
#define _IMESSAGELISTENER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IMessage;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IMessageListener
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/
	virtual void RegisterForMessages() = 0;
	virtual void ReceiveMessage(IMessage* message) = 0;
	virtual void UnRegisterForMessages() = 0;

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif
