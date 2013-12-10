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
#include "../rendering/ForwardRenderer.h"
#include "../rendering/TextureManager.h"
#include "../rendering/Texture.h"
#include "../components/Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string RenderComponent::RENDERING_COMPONENT_NAME("rendering");
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RenderComponent::RenderComponent(int componentType, int componentID): m_texture(-1), m_layer(0),
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
	FRenderer::GetInstance()->AddRenderComponentToFrame(this);
}

void RenderComponent::RegisterForMessages()
{
}

void RenderComponent::ReceiveMessage(IMessage* message)
{
}

void RenderComponent::RecieveComponentMessage(CompMessage* message)
{
}

void RenderComponent::UnRegisterForMessages()
{
}

bool RenderComponent::LoadComponentAttributes(xml_node& component)
{
    // TODO: DLL Interface will have gettexture but will return uINT
	m_texture = TextureManager::GetInstance()->GetTexture(component.attribute("texture").as_string());
	m_layer = component.attribute("layer").as_int();

    //TODO: Texture manager can return this in DLL
	getParentEntity()->SetWidth(m_texture->GetWidth());
	getParentEntity()->SetHeight(m_texture->GetHeight());
	
	return true;
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string RenderComponent::getComponentName()
{
	return RENDERING_COMPONENT_NAME;
}

unsigned int RenderComponent::getTexture() const
{
	return m_texture;
}

unsigned int RenderComponent::getTexture()
{
	return m_texture;
}

int RenderComponent::getLayer()
{
	return m_layer;
}

int RenderComponent::getLayer() const
{
	return m_layer;
}

void RenderComponent::setLayer(int layer)
{
	m_layer = layer;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////