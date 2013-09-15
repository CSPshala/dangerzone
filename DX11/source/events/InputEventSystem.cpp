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

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
InputEventSystem::InputEventSystem()
{
}

InputEventSystem::~InputEventSystem()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void InputEventSystem::RegisterProcessor(IInputEventProcessor* toRegister)
{
	m_clients.push_back(toRegister);
}

void InputEventSystem::UnRegisterProcessor(IInputEventProcessor* toUnRegister)
{
	for( deque<IInputEventProcessor*>::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter)
	{
		if((*iter) == toUnRegister)
		{
			iter = m_clients.erase(iter);
			break;
		}
	}
}

void InputEventSystem::SendEvent(int event)
{
	m_events.push_back(event);
}

void InputEventSystem::ProcessEvents()
{
	// Bail if there's no events
	if(m_events.size() == 0)
		return;

	
	for( deque<int>::iterator eventIter = m_events.begin(); eventIter != m_events.end(); ++eventIter)	
		for( deque<IInputEventProcessor*>::iterator processIter = m_clients.begin(); processIter != m_clients.end(); ++processIter)
			(*processIter)->ReceiveAndHandleEvent(*eventIter);	

	// We've sent all of our events, clear the event queue
	m_events.clear();
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