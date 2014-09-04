///////////////////////////////////////////////////////////////////////////
//	File Name	:	"MessageManager.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle routing of component and system messages
///////////////////////////////////////////////////////////////////////////
#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <queue>
#include <vector>
using namespace std;

#include "CMessages.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IMessageListener;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class MessageManager
{
public:
	/********** Public Utility Functions ************/
	static MessageManager* GetInstance();
	static void DeleteInstance();

	void SubscribeForMessageType(IMessageListener* sub, int messageType);
	void UnsubscribeForAllMessages(IMessageListener* unsub);

	void SubscribeForBroadcastMessages(IMessageListener* sub);
	void UnsubscribeForBroadcastMessages(IMessageListener* unsub);

	bool Initialize();
	bool Update(float deltaTime);
	void Shutdown();

    // TODO: Create message factory to handle creation/deletion of msgs
    void Send(IMessage* msg);
	/********** Public Accessors ************/
	

	/********** Public Mutators  ************/	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	MessageManager();
	MessageManager(const MessageManager&);
	~MessageManager();
	MessageManager& operator=(const MessageManager&);
	/********** Private Members ************/
	static MessageManager* m_instance;

	// vector of subscribers based on message type (follows message type enum for [] access)
	vector< deque<IMessageListener*> > m_subscribers;
	// deque of broadcast subscribers
	deque<IMessageListener*> m_broadcastSubscribers;
	// deque of subscribed messages
	deque<IMessage*> m_messagesToSend;
	// deque of broadcast messages
	deque<IMessage*> m_broadcastMessages;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif