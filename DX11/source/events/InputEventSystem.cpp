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
const int InputEventSystem::NUM_ALLOWED_PLAYERS(5); // Change this, it's really how many HIDs are here
const int InputEventSystem::NUM_ALLOWED_MICE(1);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
InputEventSystem::InputEventSystem()
{
	// Add 4 nullptrs to client vector for unconnected controllers
	for(int i = 0; i < NUM_ALLOWED_PLAYERS; ++i)	
		m_clients.push_back(nullptr);

	// Add 1 nullptr to mouse client vector for unconnected mice
	for(int i = 0; i < NUM_ALLOWED_MICE; ++i)
		m_mouseClients.push_back(nullptr);	
}

InputEventSystem::~InputEventSystem()
{	
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void InputEventSystem::RegisterProcessor(IInputEventProcessor* toRegister)
{
	// Only 4 are allowed currently, add based on player number
	if(m_clients[toRegister->getPlayerNumber() - 1] == nullptr)	
	{
		m_clients[toRegister->getPlayerNumber() - 1] = toRegister;	
	}
	else
	{
		LOG("InputEventSystem tried to register an InputEventProcessor with an existing player# :" << toRegister->getPlayerNumber() );
	}

}

void InputEventSystem::RegisterMouseProcessor(IInputEventProcessor* toRegister)
{
	if(m_mouseClients[toRegister->getPlayerNumber() - 1] == nullptr)
	{
		m_mouseClients[toRegister->getPlayerNumber() - 1] = toRegister;
	}
	else
	{
		LOG("InputEventSystem tried to register an InputEventProcessor (MOUSE) with an existing player# :" << toRegister->getPlayerNumber() );
	}

	//HAX: Also registers the processor for generic events using mouse (player) number + 3 (for a "5th" player or device)
	if(m_clients[toRegister->getPlayerNumber() + 3] == nullptr)
	{
		m_clients[toRegister->getPlayerNumber() + 3] = toRegister;
	}
	else
	{
		LOG("InputEventSystem tried to register an InputEventProcessor (MOUSE BUTTONS) with an existing player# :" << toRegister->getPlayerNumber() );
	}
}

void InputEventSystem::UnRegisterProcessor(IInputEventProcessor* toUnRegister)
{
	// Only 4 are allowed currently, remove based on player number
	if(m_clients[toUnRegister->getPlayerNumber() - 1] != nullptr)	
	{
		if(m_clients[toUnRegister->getPlayerNumber() - 1] == toUnRegister)
		{
			m_clients[toUnRegister->getPlayerNumber() - 1] = nullptr;	
		}
		else
		{
			LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor with a Registered player# :" << toUnRegister->getPlayerNumber() );
		}
	}
	else
	{
		LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor with player# :" << toUnRegister->getPlayerNumber() );
	}
}

void InputEventSystem::UnRegisterMouseProcessor(IInputEventProcessor* toUnRegister)
{
	// Only 1 is allowed currently, remove based on player number
	if(m_mouseClients[toUnRegister->getPlayerNumber() - 1] != nullptr)
	{
		if(m_mouseClients[toUnRegister->getPlayerNumber() - 1] == toUnRegister)
		{
			m_mouseClients[toUnRegister->getPlayerNumber() - 1] = nullptr;	
		}
		else
		{
			LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor (MOUSE) with a Registered player# :" << toUnRegister->getPlayerNumber() );
		}
	}
	else
	{
		LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor (MOUSE) with player# :" << toUnRegister->getPlayerNumber() );
	}

	// Only 4 are allowed currently, remove based on player number
	if(m_clients[toUnRegister->getPlayerNumber() + 3] != nullptr)	
	{
		if(m_clients[toUnRegister->getPlayerNumber() + 3] == toUnRegister)
		{
			m_clients[toUnRegister->getPlayerNumber() + 3] = nullptr;	
		}
		else
		{
			LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor (MOUSE BUTTONS) with a Registered player# :" << toUnRegister->getPlayerNumber() );
		}
	}
	else
	{
		LOG("InputEventSystem tried to UnRegister an UnRegistered InputEventProcessor (MOUSE BUTTONS) with player# :" << toUnRegister->getPlayerNumber() );
	}
}

void InputEventSystem::SendEvent(int event,int clientNumber)
{
	m_events.push_back(pair<int,int>(event,clientNumber));
}

void InputEventSystem::SendJoystickEvent(JoystickInfo& eventData, int clientNumber)
{
	m_joystickEvents.push_back(pair<JoystickInfo,int>(eventData,clientNumber));
}

void InputEventSystem::SendMouseEvent(MouseInfo& eventData, int clientNumber)
{
	m_mouseEvents.push_back(pair<MouseInfo,int>(eventData,clientNumber));
}

bool InputEventSystem::ProcessEvents()
{	
	// Joystick and mouse events are done before generic events so they can
	// utilize generic event sending themselves (eg mice can send "attack" events on mouse 1)

	if(m_joystickEvents.size() != 0)
	{
		for( deque<pair<JoystickInfo,int> >::iterator joyIter = m_joystickEvents.begin(); joyIter != m_joystickEvents.end(); ++joyIter)
		{
			if(m_clients[(*joyIter).second])
				m_clients[(*joyIter).second]->ReceiveAndHandleJoystickEvent((*joyIter).first);
		}

		m_joystickEvents.clear();
	}

	if(m_mouseEvents.size() != 0)
	{
		for( deque<pair<MouseInfo,int> >::iterator mouseIter = m_mouseEvents.begin(); mouseIter != m_mouseEvents.end(); ++mouseIter)
		{
			if(m_mouseClients[(*mouseIter).second])
				m_mouseClients[(*mouseIter).second]->ReceiveAndHandleMouseEvent((*mouseIter).first);
		}

		m_mouseEvents.clear();
	}

	// Bail if there's no events
	if(m_events.size() != 0)
	{	
		for( deque<pair<int,int>>::iterator eventIter = m_events.begin(); eventIter != m_events.end(); ++eventIter)	
		{
			if((*eventIter).first == InputEventSystem::QUIT)
				return false;

			if(m_clients[(*eventIter).second])
				m_clients[(*eventIter).second]->ReceiveAndHandleEvent((*eventIter).first);
		}

		// We've sent all of our events, clear the event queue
		m_events.clear();
	}

	return true;
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

InputEventSystem::JoystickInfo::JoystickInfo() : mLeftStickX(0), mLeftStickY(0),
	mRightStickX(0), mRightStickY(0)
{
}

InputEventSystem::MouseInfo::MouseInfo() : mDeltaX(0), mDeltaY(0), mMouse1(false),
	mMouse2(false), mMouse3(false)
{
}