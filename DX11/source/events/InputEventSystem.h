///////////////////////////////////////////////////////////////////////////
//	File Name	:	"InputEventSystem.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Singleton to quickly process event codes to and from listeners
///////////////////////////////////////////////////////////////////////////
#ifndef _InputEventSystem_H
#define _InputEventSystem_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <deque>
#include <vector>
#include <string>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IInputEventProcessor;

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class InputEventSystem
{
public:	
	/********** Public Utility Functions ************/
	static InputEventSystem* GetInstance();
	static void DeleteInstance();

	void RegisterProcessor(IInputEventProcessor* toRegister);
	void UnRegisterProcessor(IInputEventProcessor* toUnRegister);
	void SendEvent(int event);

	void ProcessEvents();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

	/********** Public Event Enum *****************/
	enum Events {ATTACKOFF = -6, JUMPOFF, RIGHTOFF, LEFTOFF, DOWNOFF, UPOFF,
		INVALID, UP ,DOWN,LEFT,RIGHT,JUMP,ATTACK};
	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	InputEventSystem();
	~InputEventSystem();
	InputEventSystem(const InputEventSystem&);
	InputEventSystem& operator=(const InputEventSystem&);

	/********** Private Members ************/	
	// Singleton Instance
	static InputEventSystem* m_instance;
	// Queue of event processors
	deque<IInputEventProcessor*> m_clients;
	// Queue of events to send
	deque<int> m_events;
	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif