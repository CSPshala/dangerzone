///////////////////////////////////////////////////////////////////////////
//	File Name	:	"MouseControllerComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles mouse input on entity
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "MouseControllerComponent.h"
#include "Entity.h"
#include "../messaging/MessageManager.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string MouseControllerComponent::MOUSE_CONTROLLER_COMPONENT_NAME("mouse_controller");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
MouseControllerComponent::MouseControllerComponent(int componentType, int componentID): 
	mLastPosX(0.0f), mLastPosY(0.0f), mDeltaX(0), mDeltaY(0), mMouseSens(1.0),
	IComponent(componentType,componentID), IInputEventProcessor()
{
}

MouseControllerComponent::~MouseControllerComponent()
{
	InputEventSystem::GetInstance()->UnRegisterMouseProcessor(this);
}


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void MouseControllerComponent::Update(float deltaTime)
{
	mLastPosX = getParentEntity()->GetPositionX();
	mLastPosY = getParentEntity()->GetPositionY();

	getParentEntity()->SetPositionX(mLastPosX + mDeltaX);
	getParentEntity()->SetPositionY(mLastPosY + mDeltaY);

	mDeltaX = mDeltaY = 0;
}

void MouseControllerComponent::RegisterForMessages()
{	
}

void MouseControllerComponent::ReceiveMessage(IMessage* message)
{
}

void MouseControllerComponent::RecieveComponentMessage(CompMessage* message)
{
}

void MouseControllerComponent::UnRegisterForMessages()
{
}

void MouseControllerComponent::ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event)
{
	mDeltaX = event.mDeltaX;
	mDeltaY = event.mDeltaY;
}

bool MouseControllerComponent::LoadComponentAttributes(xml_node& component)
{
	// Currently no attributes to assign
	m_playerNumber = component.attribute("mouseNumber").as_int();

	if(m_playerNumber <= 0 || m_playerNumber > InputEventSystem::NUM_ALLOWED_MICE)
	{
		LOG("A player controller tried to register an invalid mouse#: " << m_playerNumber);
		return false;
	}

	// Register for mouse events
	InputEventSystem::GetInstance()->RegisterMouseProcessor(this);

	return true;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string MouseControllerComponent::getComponentName()
{
	return MOUSE_CONTROLLER_COMPONENT_NAME;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////