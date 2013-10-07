///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CMessages.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Defines component messages
///////////////////////////////////////////////////////////////////////////
#ifndef _CMESSAGES_H
#define _CMESSAGES_H

// FWD DECL
class CollisionComponent;

enum MESSAGE_TYPE{ REGISTER_FOR_COLLISION = 0, UNREGISTER_FOR_COLLISION , TOTAL_MESSAGE_COUNT};

//*******MESSAGE INTERFACE*********/
class IMessage
{
public:
	virtual int GetType() = 0;
};

class RegisterForCollisionMsg : public IMessage
{
public:
	int GetType();
	CollisionComponent* m_Register;
};

class UnregisterForCollisionMsg : public IMessage
{
public:
	int GetType();
	CollisionComponent* m_Unregister;
};

#endif