///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CMessages.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Defines IMessages (system messages) and CompMessages (internal component msgs)
///////////////////////////////////////////////////////////////////////////
#ifndef _CMESSAGES_H
#define _CMESSAGES_H

// FWD DECL
class CollisionComponent;

enum MESSAGE_TYPE{ REGISTER_FOR_COLLISION = 0, UNREGISTER_FOR_COLLISION, TOTAL_MESSAGE_COUNT};
enum COMPONENT_MESSAGE_TYPE{ ENTITY_DIRTY = 0, TOTAL_COMPONENT_MESSAGES };

//*******MESSAGE INTERFACE*********/
class IMessage
{
public:
	virtual int GetType() = 0;    
};

class CompMessage
{
public:
    virtual int GetType() = 0;
};

// Message used to register a collision component for collisions
class RegisterForCollisionMsg : public IMessage
{
public:
    int GetType() {return REGISTER_FOR_COLLISION;}    
	CollisionComponent* m_Register;
};

// Message used to unregister a collision component for collisions
class UnregisterForCollisionMsg : public IMessage
{
public:
    int GetType() {return UNREGISTER_FOR_COLLISION;}    
	CollisionComponent* m_Unregister;
};

class EntityDirtyMsg : public CompMessage
{
public:
    int GetType() {return ENTITY_DIRTY;}
};

#endif