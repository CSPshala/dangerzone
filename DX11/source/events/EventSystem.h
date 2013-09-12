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
#include <vector>
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
	void SendEvent(int event);

	void ProcessEvents();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

	/********** Public Event Enum *****************/
	enum Events {UP = 1,DOWN,LEFT,RIGHT,JUMP,ATTACK};
	

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
	deque<int> m_events;
	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif