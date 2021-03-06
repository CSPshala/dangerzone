///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Rendercomponentdata.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Class used to pass data between render DLL and EXE
///////////////////////////////////////////////////////////////////////////
#ifndef _RENDERCOMPONENTDATA_H
#define _RENDERCOMPONENTDATA_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../DXRenderExports.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

class RENDER_API RenderComponentData
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
    RenderComponentData();

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/

	unsigned int getTexture() const;
	unsigned int getShader() const;
	int getLayer() const;
    int getWidth() const;
    int getHeight() const;
    float getPosX() const;
    float getPosY() const;

	/********** Public Mutators  ************/	
    void setTexture(unsigned int texture);
	void setShader(unsigned int shader);
    void setLayer(int layer);
    void setWidth(int width);
    void setHeight(int height);
    void setPosX(float x);
    void setPosY(float y);

private:
	/********** Private Members ************/
    unsigned int m_texture;
	unsigned int m_shader;
	int   m_layer;
    int   m_width, m_height;
    float m_posX, m_posY;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};

}
#endif