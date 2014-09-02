///////////////////////////////////////////////////////////////////////////
//	File Name	:	"PlayerControllerComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Component to handle an entity's input from players
///////////////////////////////////////////////////////////////////////////
#ifndef _PLAYERCONTROLLERCOMPONENT_H
#define _PLAYERCONTROLLERCOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IComponent.h"
#include "../events/IInputEventProcessor.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class PlayerControllerComponent : public IComponent, public IInputEventProcessor
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	/** Component typbe MUST be set at construction 
	    based on data driven component type ID from LevelLoader */
	PlayerControllerComponent(int componentType, int componentID = -1);
	~PlayerControllerComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual void RegisterForMessages();
	virtual void ReceiveMessage(IMessage* message);
	virtual void UnRegisterForMessages();
	virtual bool AddAttributeAndValue(const ComponentAttribute& attribute);
	virtual void ReceiveAndHandleEvent(int event);
	virtual void ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo& event);
	virtual void ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event) {};
	/********** Public Accessors ************/
	virtual string getComponentName();	

	/********** Public Mutators  ************/	

	/********** Public Enum ****************/
	enum InputFlags{UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8, JUMP = 16, ATTACK = 32};

private:
	/********** Private Members ************/
	static const string PLAYER_CONTROLLER_COMPONENT_NAME;
	static const float  PLAYER_MOVEMENT_VELOCITY;	

	// Input specific flags and values
	float m_LSXMod, m_RSXMod;
	float m_LSYMod, m_RSYMod;
	bool  m_keyMove; // Toggles joystick movement off if keyboard input is detected

	int  m_inputFlags; // Each bit corresponds to  forwards or backwards velocity

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual void RegisterForLocalMessages();
	virtual void _ReceiveLocalMessage(CompMessage* message);
};
#endif