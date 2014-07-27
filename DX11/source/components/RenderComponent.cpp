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
const string RenderComponent::RENDERING_COMPONENT_NAME("rendering");
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RenderComponent::RenderComponent(int componentType, int componentID): 
	IComponent(componentType,componentID)
{
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

bool RenderComponent::LoadComponentAttributes(xml_node& component)
{
    // TODO: DLL Interface will have gettexture but will return uINT
	m_renderData.setTexture(Rendering::GetTexture((char*)(component.attribute("texture").as_string())));
	m_renderData.setLayer(component.attribute("layer").as_int());
	m_renderData.setShader(GetShaderType(component.attribute("shader").as_string()));

    //TODO: Texture manager can return this in DLL
	m_renderData.setWidth(Rendering::GetTextureWidth(m_renderData.getTexture()));
	m_renderData.setHeight(Rendering::GetTextureHeight(m_renderData.getTexture()));
	getParentEntity()->SetWidth(m_renderData.getWidth());
	getParentEntity()->SetHeight(m_renderData.getHeight());
	
	return true;
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
	Rendering::AddRenderComponentToFrame(&m_renderData);
}

unsigned int RenderComponent::GetShaderType(std::string typeName)
{
	// Returns the shader type (matches up with shaderTypes.xml cause I love magic numbers)
	if(typeName == "diffuse")
	{
		return 0;
	}
	else if(typeName == "outlineBox")
	{
		return 1;
	}

	return 0;
}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string RenderComponent::getComponentName()
{
	return RENDERING_COMPONENT_NAME;
}

unsigned int RenderComponent::getTexture() const
{
	return m_renderData.getTexture();
}

unsigned int RenderComponent::getTexture()
{
	return m_renderData.getTexture();
}

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