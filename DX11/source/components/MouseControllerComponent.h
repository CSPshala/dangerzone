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
#include "../math/vec3.h"
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
	virtual void UnRegisterForMessages();
	virtual bool AddAttributeAndValue(const ComponentAttribute& attribute);
	virtual void ReceiveAndHandleEvent(int event);
	virtual void ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo& event) {};
	virtual void ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event);
	/********** Public Accessors ************/
	virtual string getComponentName();	
	/********** Public Utility Functions ************/

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

	/********** Public Enum ****************/
	enum InputFlags{MB1 = 1, MB2 = 2, MB3 = 4, MB4 = 8, MB5 = 16, MB6 = 32};

private:
	/********** Private Members ************/
	static const string MOUSE_CONTROLLER_COMPONENT_NAME;	
	
	vec3<float> mLastPos;
	vec3<float> mDelta;
	float mMouseSens;
	// Vector for mouse button states
	int mButtonFlags;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual void RegisterForLocalMessages();
	virtual void _ReceiveLocalMessage(CompMessage* message);
};
#endif