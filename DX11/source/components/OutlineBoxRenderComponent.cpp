///////////////////////////////////////////////////////////////////////////
//	File Name	:	"OutlineBoxRenderComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles OutlineBox rendering specific data
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "OutlineBoxRenderComponent.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
OutlineBoxRenderComponent::OutlineBoxRenderComponent(int componentType, int componentID) :
	RenderComponent(GetShaderType(), componentType, componentID)
{
}

OutlineBoxRenderComponent::~OutlineBoxRenderComponent()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
string OutlineBoxRenderComponent::getComponentName()
{
	return string("OutlineBoxRender");
}

bool OutlineBoxRenderComponent::AddAttributeAndValue(const ComponentAttribute* attribute)
{		
	LOG("Something tried to register an invalid attribute to a RenderComponent.");
	return false;	
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
unsigned int OutlineBoxRenderComponent::GetShaderType()
{
	return 1;
}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////