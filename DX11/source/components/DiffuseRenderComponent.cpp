///////////////////////////////////////////////////////////////////////////
//	File Name	:	"DiffuseRenderComponent.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles Diffuse rendering specific data
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "DiffuseRenderComponent.h"
#include "Entity.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
DiffuseRenderComponent::DiffuseRenderComponent(int componentType, int componentID) :
	RenderComponent(GetShaderType(), componentType, componentID)
{	
}

DiffuseRenderComponent::~DiffuseRenderComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
string DiffuseRenderComponent::getComponentName()
{
	return string("DiffuseRender");
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
unsigned int DiffuseRenderComponent::GetShaderType()
{
	return 0;
}

bool DiffuseRenderComponent::AddAttributeAndValue(const ComponentAttribute& attribute)
{	
	if(attribute.name == "texture")
	{
		if(attribute.valueString != "")
		{
			m_renderData.setTexture(Rendering::GetTexture(attribute.valueString.c_str()));
			m_renderData.setWidth(Rendering::GetTextureWidth(m_renderData.getTexture()));
			m_renderData.setHeight(Rendering::GetTextureHeight(m_renderData.getTexture()));
			getParentEntity()->SetWidth(m_renderData.getWidth());
			getParentEntity()->SetHeight(m_renderData.getHeight());
		}

		return true;
	}
	else
	{
		LOG("Something tried to register an invalid attribute to a RenderComponent.");
		return false;
	}	
}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
unsigned int DiffuseRenderComponent::getTexture() const
{
	return m_renderData.getTexture();
}

unsigned int DiffuseRenderComponent::getTexture()
{
	return m_renderData.getTexture();
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////