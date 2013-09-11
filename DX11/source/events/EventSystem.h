///////////////////////////////////////////////////////////////////////////
//	File Name	:	"EventSystem.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Singleton to quickly process event codes to and from listeners
///////////////////////////////////////////////////////////////////////////
#ifndef _EVENTSYSTEM_H
#define _EVENTSYSTEM_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <deque>
#include <string>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IEventProcessor;

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class EventSystem
{
public:	
	/********** Public Utility Functions ************/
	static EventSystem* GetInstance();
	static void DeleteInstance();

	void RegisterProcessor(IEventProcessor* toRegister);
	void UnRegisterProcessor(IEventProcessor* toUnRegister);
	void SendEvent(string event);

	void ProcessEvents();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	EventSystem();
	~EventSystem();
	EventSystem(const EventSystem&);
	EventSystem& operator=(const EventSystem&);

	/********** Private Members ************/	
	// Singleton Instance
	static EventSystem* m_instance;
	// Queue of event processors
	deque<IEventProcessor*> m_clients;
	// Queue of events to send
	deque<string> m_events;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif