///////////////////////////////////////////////////////////////////////////
//	File Name	:	"CollisionComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle an entity's collision
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "CollisionComponent.h"
#include "../messaging/MessageManager.h"
#include "Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string CollisionComponent::COLLISION_COMPONENT_NAME("collision");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
CollisionComponent::CollisionComponent(int componentType, int componentID) : IComponent(componentType, componentID),
    m_dirty(true)
{    
}

CollisionComponent::~CollisionComponent()
{    
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::Update(float deltaTime)
{
    if(m_dirty)
        CalculateAABB();
}

void CollisionComponent::RegisterForMessages()
{    
    // Register ourself with the CollisionQuadTree
    RegisterForCollisionMsg* newMsg = new RegisterForCollisionMsg;
    newMsg->m_Register = this;
    MessageManager::GetInstance()->Send(newMsg);   
}

void CollisionComponent::ReceiveMessage(IMessage* message)
{
}

void CollisionComponent::RegisterForLocalMessages()
{
}

void CollisionComponent::ReceiveLocalMessage(CompMessage* message)
{
    if(message->GetType() == ENTITY_DIRTY)
        m_dirty = true;
}

void CollisionComponent::UnRegisterForMessages()
{
    // Tell collision system we're unregistered
    UnregisterForCollisionMsg* newMsg = new UnregisterForCollisionMsg;
    newMsg->m_Unregister = this;
    MessageManager::GetInstance()->Send(newMsg);
}

bool CollisionComponent::LoadComponentAttributes(xml_node& component)
{    
	m_layer = component.attribute("layer").as_int();
    return true;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void CollisionComponent::CalculateAABB()
{
    float halfHeight = static_cast<float>(getParentEntity()->GetHeight()) * 0.5f;
    float halfWidth  = static_cast<float>(getParentEntity()->GetWidth()) * 0.5f;

    m_AABB.top = getParentEntity()->GetPositionY() - halfHeight;
    m_AABB.bottom = getParentEntity()->GetPositionY() + halfHeight;
    m_AABB.left = getParentEntity()->GetPositionX() - halfWidth;
    m_AABB.right = getParentEntity()->GetPositionX() + halfWidth;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string CollisionComponent::getComponentName()
{
    return CollisionComponent::COLLISION_COMPONENT_NAME;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////