///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RenderComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Component to handle an entity's rendering
///////////////////////////////////////////////////////////////////////////
#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IComponent.h"
#include "../../dx11rend/dx11rendexp.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Texture;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class RenderComponent : public IComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	/** Component typbe MUST be set at construction 
	    based on data driven component type ID from LevelLoader */
	RenderComponent(int shaderType, int componentType, int componentID = -1);
	~RenderComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual void RegisterForMessages();
	virtual void ReceiveMessage(IMessage* message);	
	virtual void UnRegisterForMessages();
	/********** Public Accessors ************/
	virtual string getComponentName() = 0;
	
	int getLayer();
	int getLayer() const;
	/********** Public Mutators  ************/
	void setLayer(int layer);
protected:
	/** Shared DLL class from renderer, holding relevant info */
	Renderer::RenderComponentData m_renderData;

private:
	/********** Private Members ************/	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual void RegisterForLocalMessages();
	virtual void _ReceiveLocalMessage(CompMessage* message);
	virtual unsigned int GetShaderType() = 0;
	void RenderEntity();
};
#endif