///////////////////////////////////////////////////////////////////////////
//	File Name	:	"EventSystem.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Singleton to quickly process event codes to and from listeners
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "EventSystem.h"
#include "IEventProcessor.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
EventSystem* EventSystem::m_instance = nullptr;

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void EventSystem::RegisterProcessor(IEventProcessor* toRegister)
{
	m_clients.push_back(toRegister);
}

void EventSystem::UnRegisterProcessor(IEventProcessor* toUnRegister)
{
	for( deque<IEventProcessor*>::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter)
	{
		if((*iter) == toUnRegister)
		{
			iter = m_clients.erase(iter);
			break;
		}
	}
}

void EventSystem::SendEvent(int event)
{
	m_events.push_back(event);
}

void EventSystem::ProcessEvents()
{
	// Bail if there's no events
	if(m_events.size() == 0)
		return;

	for( deque<int>::iterator eventIter = m_events.begin(); eventIter != m_events.end(); ++eventIter)	
		for( deque<IEventProcessor*>::iterator processIter = m_clients.begin(); processIter != m_clients.end(); ++processIter)
			(*processIter)->ReceiveAndHandleEvent(*eventIter);	

	// We've sent all of our events, clear the event queue
	m_events.clear();
}

EventSystem* EventSystem::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new EventSystem;

	return m_instance;
}

void EventSystem::DeleteInstance()
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