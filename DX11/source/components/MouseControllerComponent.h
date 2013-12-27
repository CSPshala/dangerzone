///////////////////////////////////////////////////////////////////////////
//	File Name	:	"MouseControllerComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles mouse input on an entity
///////////////////////////////////////////////////////////////////////////
#ifndef _MOUSECONTROLLERCOMPONENT_H
#define _MOUSECONTROLLERCOMPONENT_H

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


class MouseControllerComponent : public IComponent, public IInputEventProcessor
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	MouseControllerComponent(int componentType, int componentID = -1);
	~MouseControllerComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual void RegisterForMessages();
	virtual void ReceiveMessage(IMessage* message);
    virtual void RecieveComponentMessage(CompMessage* message);
	virtual void UnRegisterForMessages();
	virtual bool LoadComponentAttributes(xml_node& component);
	virtual void ReceiveAndHandleEvent(int event) {};
	virtual void ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo& event) {};
	virtual void ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event);
	/********** Public Accessors ************/
	virtual string getComponentName();	
	/********** Public Utility Functions ************/

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	static const string MOUSE_CONTROLLER_COMPONENT_NAME;
	
	float mLastPosX, mLastPosY;
	int mDeltaX, mDeltaY;
	float mMouseSens;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif