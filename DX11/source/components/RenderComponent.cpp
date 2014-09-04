///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RenderComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Component to handle an entity's rendering
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "RenderComponent.h"
#include "../messaging/CMessages.h"
#include "../components/Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RenderComponent::RenderComponent(int shaderType, int componentType, int componentID): 
	IComponent(componentType,componentID)
{	
	m_renderData.setShader(shaderType);
}

RenderComponent::~RenderComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void RenderComponent::Update(float deltaTime)
{	
	
}

void RenderComponent::RegisterForMessages()
{
}

void RenderComponent::ReceiveMessage(IMessage* message)
{
}

void RenderComponent::RegisterForLocalMessages()
{
	m_messageSubs.push_back(ENTITY_RENDER);
}

void RenderComponent::UnRegisterForMessages()
{
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void RenderComponent::_ReceiveLocalMessage(CompMessage* message)
{
	switch(message->GetType())
	{
	case ENTITY_RENDER:
		{
			RenderEntity();
		}
		break;
	}

}

void RenderComponent::RenderEntity()
{
	// Update render data and send to renderer to queue up
	m_renderData.setPosX(getParentEntity()->GetPosition().x);
	m_renderData.setPosY(getParentEntity()->GetPosition().y);	
	m_renderData.setWidth(getParentEntity()->GetWidth());
	m_renderData.setHeight(getParentEntity()->GetHeight());
	m_renderData.setLayer(getParentEntity()->GetLayer());
	Rendering::AddRenderComponentToFrame(&m_renderData);
}


////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
int RenderComponent::getLayer()
{
	return m_renderData.getLayer();
}

int RenderComponent::getLayer() const
{
	return m_renderData.getLayer();
}

void RenderComponent::setLayer(int layer)
{
	m_renderData.setLayer(layer);
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////