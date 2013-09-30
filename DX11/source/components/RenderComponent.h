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
	virtual void ReceiveMessage(IMessage* message);	
	virtual bool LoadComponentAttributes(xml_node& component);
	/********** Public Accessors ************/
	virtual string getComponentName();
	Texture* getTexture();
	Texture* getTexture() const;
	int getLayer();
	int getLayer() const;
	/********** Public Mutators  ************/
	void setLayer(int layer);

private:
	/********** Private Members ************/
	static const string RENDERING_COMPONENT_NAME;
	Texture* m_texture;
	int m_layer;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif