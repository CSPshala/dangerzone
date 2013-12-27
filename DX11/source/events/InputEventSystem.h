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
		JoystickInfo();
		short mLeftStickX;
		short mLeftStickY;
		short mRightStickX;
		short mRightStickY;
	};

	struct MouseInfo
	{
		MouseInfo();
		int mDeltaX;
		int mDeltaY;
		bool mMouse1;
		bool mMouse2;
		bool mMouse3;
	};

	/********** Public Utility Functions ************/
	static InputEventSystem* GetInstance();
	static void DeleteInstance();

	void RegisterProcessor(IInputEventProcessor* toRegister);
	void RegisterMouseProcessor(IInputEventProcessor* toRegister);
	void UnRegisterProcessor(IInputEventProcessor* toUnRegister);
	void UnRegisterMouseProcessor(IInputEventProcessor* toUnRegister);
	void SendEvent(int event, int clientNumber = 0);
	void SendJoystickEvent(JoystickInfo& eventData, int clientNumber = 0);
	void SendMouseEvent(MouseInfo& eventData, int clientNumber = 0);

	bool ProcessEvents();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

	/********** Public Event Enum *****************/
	enum Events {INVALID = 0, UP ,DOWN,LEFT,RIGHT,JUMP,ATTACK,QUIT,LAST_EVENT};
	
	static const int NUM_ALLOWED_PLAYERS;	
	static const int NUM_ALLOWED_MICE;

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
	// Queue of mouse event processors (separate so we can have pointers and players if need be)
	vector<IInputEventProcessor*> m_mouseClients;
	// Queue of events to send
	deque<pair<int,int> > m_events;
	// Queue of joystick events to send
	deque<pair<JoystickInfo,int> > m_joystickEvents;
	// Queue of mouse events to send
	deque<pair<MouseInfo,int> > m_mouseEvents;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif