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
	IInputEventProcessor();

	/********** Public Utility Functions ************/
	/** Use to register this processor to start receiving input events
		NOTE: Entities are entirely responsible for registering **/
	void RegisterForEvents();
	/** Use to unregister this processor to stop receiving input events
		NOTE: Entities are entirely responsible for unregistering **/
	void UnRegisterForEvents();
	virtual void ReceiveAndHandleEvent(int event) = 0;
	virtual void ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo& event) = 0;
	virtual void ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event) = 0;
	/********** Public Accessors ************/
	int	getPlayerNumber();
	/********** Public Mutators  ************/	
protected:
	// Player number (1-4)
	int m_playerNumber;
	
private:
	/********** Private Members ************/
	
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif