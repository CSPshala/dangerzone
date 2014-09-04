///////////////////////////////////////////////////////////////////////////
//	File Name	:	"OutlineBoxRenderComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles OutlineBox rendering specific data
///////////////////////////////////////////////////////////////////////////
#ifndef _OUTLINEBOXRENDERCOMPONENT_H
#define _OUTLINEBOXRENDERCOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "RenderComponent.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class OutlineBoxRenderComponent : public RenderComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	OutlineBoxRenderComponent(int componentType, int componentID = -1);
	~OutlineBoxRenderComponent();
	/********** Public Utility Functions ************/
	virtual bool AddAttributeAndValue(const ComponentAttribute* attribute);

	/********** Public Accessors ************/
	string getComponentName();
	
	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	unsigned int GetShaderType();
};
#endif