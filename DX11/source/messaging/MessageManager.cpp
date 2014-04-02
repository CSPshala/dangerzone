///////////////////////////////////////////////////////////////////////////
//	File Name	:	"MessageManager.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle routing of component and system messages
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "MessageManager.h"
#include "IMessageListener.h"
#include "CMessages.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
MessageManager* MessageManager::m_instance(nullptr);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
MessageManager::MessageManager()
{
	for(unsigned int i = 0; i < TOTAL_MESSAGE_COUNT; ++i)
		m_subscribers.push_back(deque<IMessageListener*>());	
}

MessageManager::~MessageManager()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void MessageManager::SubscribeForMessageType(IMessageListener* sub, int messageType)
{
	m_subscribers[messageType].push_back(sub);
}

void MessageManager::UnsubscribeForAllMessages(IMessageListener* unsub)
{
	for(unsigned int i = 0; i < TOTAL_MESSAGE_COUNT; ++i)
	{
		deque<IMessageListener*>::iterator iter = m_subscribers[i].begin();
		while(iter != m_subscribers[i].end())
		{
			if((*iter) == unsub)
			{
				m_subscribers[i].erase(iter);
				break;
			}
			++iter;
		};
	}
}

bool MessageManager::Initialize()
{
	return true;
}

bool MessageManager::Update(float deltaTime)
{
	deque<IMessage*>::iterator msgIter = m_messagesToSend.begin();

	for(;msgIter != m_messagesToSend.end(); ++msgIter)
	{
		int index = (*msgIter)->GetType();
		deque<IMessageListener*>::iterator subIter = m_subscribers[index].begin();
		while(subIter != m_subscribers[index].end())
		{
			(*subIter)->ReceiveMessage((*msgIter));
			++subIter;
		}
		// Clean up this message
		delete (*msgIter);
		msgIter = m_messagesToSend.erase(msgIter);

		if(msgIter == m_messagesToSend.end())
			break;
	};

	return true;
}

void MessageManager::Send(IMessage* msg)
{
    m_messagesToSend.push_back(msg);
}


void MessageManager::Shutdown()
{	
	while(m_messagesToSend.size() > 0)
	{		
		delete m_messagesToSend.front();
		m_messagesToSend.pop_front();
	}
}

MessageManager* MessageManager::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new MessageManager;

	return m_instance;
}

void MessageManager::DeleteInstance()
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