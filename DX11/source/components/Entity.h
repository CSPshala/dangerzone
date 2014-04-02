///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Entity.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organise an object's components
///////////////////////////////////////////////////////////////////////////
#ifndef _ENTITY_H
#define _ENTITY_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <queue>
#include <map>
using namespace std;
#include "../messaging/CMessages.h"
#include "../math/vec3.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IComponent;
class IMessage;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Entity
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Entity(int ID, string entityName);
	~Entity();

	/********** Public Utility Functions ************/
		// Destructor handles component cleanup
	void AttachComponent(IComponent* component);
	void RemoveComponent(IComponent* component);
	void Update(float deltaTime);
	void RegisterForLocalMessage(COMPONENT_MESSAGE_TYPE type, IComponent* component);
	// Can be expensive, don't use too often
	void UnRegisterForAllLocalMessages(IComponent* component);
	void UnRegisterForMessage(COMPONENT_MESSAGE_TYPE type, IComponent* component);
	void SendLocalMessage(CompMessage* msg);

	void Shutdown();
	/********** Public Accessors ************/
	IComponent* GetComponent(int componentType);
	int			GetEntityID();

	// Vitals
	int GetHP();
	vec3<float> GetVelocity();
	vec3<float> GetPosition();
	int   GetWidth();
	int   GetHeight();
	bool  IsActive();

	/********** Public Mutators  ************/	
	// Vitals
	void SetHP(int in);
    void SetVelocity(vec3<float> vel);
    void SetPosition(vec3<float> pos);
	void SetWidth(int width);
	void SetHeight(int height);
	void IsActive(bool active);

private:
	/********** Private Members ************/
		// List of components
	deque<IComponent*> m_components;
		// Map of LOCAL message types, and what components are registered to receive them
	map<COMPONENT_MESSAGE_TYPE, deque<IComponent*> > m_localSubs;
		// Unique entity ID
	int m_ID;
		// Entity name
	string m_entityName;
		// Active entity or not
	bool   m_active;
		// Entity Vital Stats
	int m_hp;
	vec3<float> mVel;
	vec3<float> mPos;
	int   m_width, m_height;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif