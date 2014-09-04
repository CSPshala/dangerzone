///////////////////////////////////////////////////////////////////////////
//	File Name	:	"DiffuseRenderComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles Diffuse rendering specific data
///////////////////////////////////////////////////////////////////////////
#ifndef _DIFFUSERENDERCOMPONENT_H
#define _DIFFUSERENDERCOMPONENT_H

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


class DiffuseRenderComponent : public RenderComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	DiffuseRenderComponent(int componentType, int componentID = -1);
	~DiffuseRenderComponent();
	/********** Public Utility Functions ************/
	virtual bool AddAttributeAndValue(const ComponentAttribute& attribute);

	/********** Public Accessors ************/
	string getComponentName();	

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/
	unsigned int getTexture();
	unsigned int getTexture() const;

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	unsigned int GetShaderType();
};
#endif