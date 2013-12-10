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

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class RenderComponentData
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/
    unsigned int getTexture();
	unsigned int getTexture() const;
	int getLayer();
	int getLayer() const;
    int getWidth();
    int getWidth() const;
    int getHeight();
    int getHeight() const;

	/********** Public Mutators  ************/	
    void setTexture(unsigned int texture);
    void setLayer(int layer);
    void setWidth(int width);
    void setHeight(int height);

private:
	/********** Private Members ************/
    unsigned int m_texture;
	int m_layer;
    int   m_width, m_height;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif