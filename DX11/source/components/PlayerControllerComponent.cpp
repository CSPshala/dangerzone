///////////////////////////////////////////////////////////////////////////
//	File Name	:	"PlayerControllerComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Component to handle an entity's input from players
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "PlayerControllerComponent.h"
#include "Entity.h"
#include "../messaging/MessageManager.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string PlayerControllerComponent::PLAYER_CONTROLLER_COMPONENT_NAME("player_controller");
const float  PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY(500.0f);
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
PlayerControllerComponent::PlayerControllerComponent(int componentType, int componentID):
	m_LSXMod(0.0f), m_RSXMod(0.0f), m_LSYMod(0.0f), m_RSYMod(0.0f),	m_keyMove(true), m_inputFlags(0), 
	IComponent(componentType,componentID), IInputEventProcessor()
{
}

PlayerControllerComponent::~PlayerControllerComponent()
{
	UnRegisterForEvents();
}


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void PlayerControllerComponent::Update(float deltaTime)
{	
	float velX, velY;
	float posX = getParentEntity()->GetPositionX();
	float posY = getParentEntity()->GetPositionY();

	// Update velocities then add to position
	if(m_keyMove)
	{
		velY =  PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  * ((m_inputFlags & DOWN) > 1);
		velY -= PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  *  (m_inputFlags & UP);
		velX =  PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  * ((m_inputFlags & RIGHT) > 3);
		velX -= PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  * ((m_inputFlags & LEFT) > 2);
	}
	else
	{
		// Joystick movement
		velY = PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  * m_LSYMod;		 
		velX = PlayerControllerComponent::PLAYER_MOVEMENT_VELOCITY  * m_LSXMod;
	}

	getParentEntity()->SetVelocityX(velX);
	getParentEntity()->SetVelocityY(velY);	

	getParentEntity()->SetPositionX(posX + velX * deltaTime);
	getParentEntity()->SetPositionY(posY + velY * deltaTime);
}

void PlayerControllerComponent::RegisterForMessages()
{	
}

void PlayerControllerComponent::ReceiveMessage(IMessage* message)
{
}

void PlayerControllerComponent::RegisterForLocalMessages()
{
}

void PlayerControllerComponent::UnRegisterForMessages()
{
}


bool PlayerControllerComponent::LoadComponentAttributes(xml_node& component)
{
	// Currently no attributes to assign
	m_playerNumber = component.attribute("playerNumber").as_int();

	if(m_playerNumber <= 0 || m_playerNumber > InputEventSystem::NUM_ALLOWED_PLAYERS)
	{
		LOG("A player controller tried to register an invalid player#: " << m_playerNumber);
		return false;
	}

	RegisterForEvents();

	return true;
}

void PlayerControllerComponent::ReceiveAndHandleEvent(int event)
{
	switch(event)
	{
	case InputEventSystem::UP:
		{
			//7cout << "UP\n";
			m_inputFlags ^= UP;
		}
		break;
	case InputEventSystem::DOWN:
		{
			//cout << "DOWN\n";
			m_inputFlags ^= DOWN;
		}
		break;
	case InputEventSystem::LEFT:
		{
			//cout << "LEFT\n";
			m_inputFlags ^= LEFT;
		}
		break;
	case InputEventSystem::RIGHT:
		{
			//cout << "RIGHT\n";
			m_inputFlags ^= RIGHT;
		}
		break;
	case InputEventSystem::JUMP:
		{
			m_inputFlags ^= JUMP;
		}
		break;
	case InputEventSystem::ATTACK:
		{
			m_inputFlags ^= ATTACK;
		}
		break;
	};

	// If we make it here, then keyboard input is going on
	m_keyMove = true;
}

void PlayerControllerComponent::ReceiveAndHandleJoystickEvent(InputEventSystem::JoystickInfo& event)
{
	m_LSXMod = static_cast<float>(event.mLeftStickX) / 32768.0f;
	m_LSYMod = -static_cast<float>(event.mLeftStickY) / 32768.0f;
	m_RSXMod = static_cast<float>(event.mRightStickX) / 32768.0f;
	m_RSYMod = static_cast<float>(event.mRightStickY) / 32768.0f;

	// Clamp
	if(G_FLOAT_EPSILON(m_LSXMod,1.0f))
		m_LSXMod = 1.0f;
	if(G_FLOAT_EPSILON(m_LSYMod,1.0f))
		m_LSYMod = 1.0f;
	if(G_FLOAT_EPSILON(m_RSXMod,1.0f))
		m_RSXMod = 1.0f;
	if(G_FLOAT_EPSILON(m_RSYMod,1.0f))
		m_RSYMod = 1.0f;

	m_keyMove = false;

	if(!(m_LSXMod || m_LSYMod || m_RSXMod || m_RSYMod))
		m_keyMove = true;		
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void PlayerControllerComponent::_ReceiveLocalMessage(CompMessage* message)
{
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string PlayerControllerComponent::getComponentName()
{
	return PLAYER_CONTROLLER_COMPONENT_NAME;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////