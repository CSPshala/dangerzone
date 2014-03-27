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
	RenderComponent(int componentType, int componentID = -1);
	~RenderComponent();
	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime);
	virtual void RegisterForMessages();
	virtual void ReceiveMessage(IMessage* message);	
	virtual void UnRegisterForMessages();
	virtual bool LoadComponentAttributes(xml_node& component);
	/********** Public Accessors ************/
	virtual string getComponentName();
	unsigned int getTexture();
	unsigned int getTexture() const;
	int getLayer();
	int getLayer() const;
	/********** Public Mutators  ************/
	void setLayer(int layer);

private:
	/********** Private Members ************/
	static const string RENDERING_COMPONENT_NAME;
	/** Shared DLL class from renderer, holding relevant info */
	Renderer::RenderComponentData m_renderData;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual void RegisterForLocalMessages();
	virtual void _ReceiveLocalMessage(CompMessage* message);
};
#endif