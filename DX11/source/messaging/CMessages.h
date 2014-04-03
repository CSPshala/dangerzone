///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CMessages.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Defines IMessages (system messages) and CompMessages (internal component msgs)
///////////////////////////////////////////////////////////////////////////
#ifndef _CMESSAGES_H
#define _CMESSAGES_H

#include <vector>
using namespace std;

// FWD DECL
class CollisionComponent;

enum MESSAGE_TYPE{ REGISTER_FOR_COLLISION = 0, UNREGISTER_FOR_COLLISION, TOTAL_MESSAGE_COUNT};
enum COMPONENT_MESSAGE_TYPE{ ENTITY_REGISTER_LOCAL_MSGS = 0, ENTITY_UNREGISTER_LOCAL_MSGS, 
	ENTITY_DIRTY, ENTITY_RESIZE, ENTITY_COLLIDING, ENTITY_RENDER, TOTAL_COMPONENT_MESSAGES };

//*******MESSAGE INTERFACE*********/
class IMessage
{
public:
	virtual int GetType() = 0;    
};

class CompMessage
{
public:
	CompMessage() {}
	~CompMessage() {}
	virtual COMPONENT_MESSAGE_TYPE GetType() = 0;
};

// Message used to register a collision component for collisions
class RegisterForCollisionMsg : public IMessage
{
public:
    int GetType() {return REGISTER_FOR_COLLISION;}    
	CollisionComponent* mRegister;
};

// Message used to unregister a collision component for collisions
class UnregisterForCollisionMsg : public IMessage
{
public:
    int GetType() {return UNREGISTER_FOR_COLLISION;}    
	CollisionComponent* mUnregister;
};

class EntityDirtyMsg : public CompMessage
{
public:
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_DIRTY;}
};

class EntityResizeMsg : public CompMessage
{
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_RESIZE;}
};

// Messages used to tell a component to register / unregister for local msgs
class RegisterForLocalMsgs : public CompMessage
{
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_REGISTER_LOCAL_MSGS;}
};

class UnRegisterForLocalMsgs : public CompMessage
{
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_UNREGISTER_LOCAL_MSGS;}
};

class CollidingMsg : public CompMessage
{
public:
	CollidingMsg() {}
	~CollidingMsg() {}
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_COLLIDING;}
	vector<CollisionComponent*>* mCollidingWith;
};

class RenderMsg : public CompMessage
{
public:
	COMPONENT_MESSAGE_TYPE GetType() {return ENTITY_RENDER;}
};

#endif