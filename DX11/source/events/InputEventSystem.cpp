///////////////////////////////////////////////////////////////////////////
//	File Name	:	"InputEventSystem.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Singleton to quickly process event codes to and from listeners
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "InputEventSystem.h"
#include "IInputEventProcessor.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
InputEventSystem* InputEventSystem::m_instance = nullptr;
const int InputEventSystem::NUM_ALLOWED_PLAYERS(4);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
InputEventSystem::InputEventSystem()
{
	// Add 4 nullptrs to client vector for unconnected controllers
	for(int i = 0; i < NUM_ALLOWED_PLAYERS; ++i)	
		m_clients.push_back(nullptr);	

}

InputEventSystem::~InputEventSystem()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void InputEventSystem::RegisterProcessor(IInputEventProcessor* toRegister)
{
	// Only 4 are allowed currently, add them in order
	for(int i = 0; i < NUM_ALLOWED_PLAYERS; ++i)
		if(m_clients[i] == nullptr)
		{
			m_clients[i] = toRegister;
			break;
		}

}

void InputEventSystem::UnRegisterProcessor(IInputEventProcessor* toUnRegister)
{
	for( vector<IInputEventProcessor*>::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter)
	{
		if((*iter) == toUnRegister)
		{
			*iter = nullptr;
			break;
		}
	}
}

void InputEventSystem::SendEvent(int event,int clientNumber)
{
	m_events.push_back(pair<int,int>(event,clientNumber));
}

void InputEventSystem::SendJoystickEvent(JoystickInfo eventData, int clientNumber)
{
	m_joystickEvents.push_back(pair<JoystickInfo,int>(eventData,clientNumber));
}

void InputEventSystem::ProcessEvents()
{
	// Bail if there's no events
	if(m_events.size() != 0)
	{	
		for( deque<pair<int,int>>::iterator eventIter = m_events.begin(); eventIter != m_events.end(); ++eventIter)	
		{
			if(m_clients[(*eventIter).second])
				m_clients[(*eventIter).second]->ReceiveAndHandleEvent((*eventIter).first);
		}

		// We've sent all of our events, clear the event queue
		m_events.clear();
	}

	if(m_joystickEvents.size() != 0)
	{
		for( deque<pair<JoystickInfo,int> >::iterator joyIter = m_joystickEvents.begin(); joyIter != m_joystickEvents.end(); ++joyIter)
		{
			if(m_clients[(*joyIter).second])
				m_clients[(*joyIter).second]->ReceiveAndHandleJoystickEvent((*joyIter).first);
		}
	}
}

InputEventSystem* InputEventSystem::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new InputEventSystem;

	return m_instance;
}

void InputEventSystem::DeleteInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////