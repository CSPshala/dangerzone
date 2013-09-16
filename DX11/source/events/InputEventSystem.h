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

	struct JoystickInfo
	{
		short mLeftStickX;
		short mLeftStickY;
		short mRightStickX;
		short mRightStickY;
	};

	/********** Public Utility Functions ************/
	static InputEventSystem* GetInstance();
	static void DeleteInstance();

	void RegisterProcessor(IInputEventProcessor* toRegister);
	void UnRegisterProcessor(IInputEventProcessor* toUnRegister);
	void SendEvent(int event, int clientNumber = 0);
	void SendJoystickEvent(JoystickInfo eventData, int clientNumber = 0);

	void ProcessEvents();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

	/********** Public Event Enum *****************/
	enum Events {ATTACKOFF = -6, JUMPOFF, RIGHTOFF, LEFTOFF, DOWNOFF, UPOFF,
		INVALID, UP ,DOWN,LEFT,RIGHT,JUMP,ATTACK};
	
	static const int NUM_ALLOWED_PLAYERS;	

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
	vector<IInputEventProcessor*> m_clients;
	// Queue of events to send
	deque<pair<int,int> > m_events;
	// Queue of joystick events to send
	deque<pair<JoystickInfo,int> > m_joystickEvents;
	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif