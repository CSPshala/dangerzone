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
	mMouseSens(1.0), mButtonFlags(0), IComponent(componentType,componentID), IInputEventProcessor()
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
	mLastPos = getParentEntity()->GetPosition();

	vec3<float> newPos(mLastPos.x + mDelta.x, mLastPos.y + mDelta.y, 0.0f);
	
	getParentEntity()->SetPosition(newPos);

	// Uncomment to see values realtime, mainly to tweak dead zones for stuff
	//std::cout << "DeltaX: " << mDeltaX << '\n';
	//std::cout << "DeltaY: " << mDeltaY << '\n';

	mDelta.make_zero();
}

void MouseControllerComponent::RegisterForMessages()
{	
}

void MouseControllerComponent::ReceiveMessage(IMessage* message)
{
}

void MouseControllerComponent::RegisterForLocalMessages()
{
}

void MouseControllerComponent::UnRegisterForMessages()
{
}

void MouseControllerComponent::ReceiveAndHandleEvent(int event)
{
	switch(event)
	{
	case InputEventSystem::CLICK1:
		{
			cout << "Clicked MOUSE1\n";
		}
		break;
	case InputEventSystem::CLICK2:
		{
			cout << "Clicked MOUSE2\n";
		}
		break;
	case InputEventSystem::CLICK3:
		{
			cout << "Clicked MOUSE3\n";
		}
		break;
	case InputEventSystem::CLICK4:
		{
			cout << "Clicked MOUSE4\n";
		}
		break;
	case InputEventSystem::CLICK5:
		{
			cout << "Clicked MOUSE5\n";
		}
		break;
	}
}

void MouseControllerComponent::ReceiveAndHandleMouseEvent(InputEventSystem::MouseInfo& event)
{
	mDelta.x = static_cast<float>(event.mDeltaX);
	mDelta.y = static_cast<float>(event.mDeltaY);
}

bool MouseControllerComponent::AddAttributeAndValue(const ComponentAttribute& attribute)
{
	if(attribute.name == "mouseNumber")
	{
		m_playerNumber = attribute.valueI;

		if(m_playerNumber <= 0 || m_playerNumber > InputEventSystem::NUM_ALLOWED_MICE)
		{
			LOG("A player controller tried to register an invalid mouse#: " << m_playerNumber);
			return false;
		}

		// Register for mouse move and generic events
		InputEventSystem::GetInstance()->RegisterMouseProcessor(this);

		return true;
	}
	else
	{
		LOG("Something tried to register an invalid attribute to a MouseControllerComponent.");

		return false;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void MouseControllerComponent::_ReceiveLocalMessage(CompMessage* message)
{
}

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