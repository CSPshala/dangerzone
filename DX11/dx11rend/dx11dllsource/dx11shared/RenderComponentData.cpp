///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RenderComponentDatadata.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Class used to pass data between render DLL and EXE
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "RenderComponentData.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RenderComponentData::RenderComponentData() : m_texture(0), m_layer(-1), m_width(0), m_height(0),
    m_posX(0.0f), m_posY(0.0f)
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
unsigned int RenderComponentData::getTexture() const
{
	return m_texture;
}

unsigned int RenderComponentData::getShader() const
{
	return m_shader;
}

int RenderComponentData::getLayer() const
{
	return m_layer;
}

int RenderComponentData::getWidth() const
{
    return m_width;
}

int RenderComponentData::getHeight() const
{
    return m_height;
}

float RenderComponentData::getPosX() const
{
    return m_posX;
}

float RenderComponentData::getPosY() const
{
    return m_posY;
}

void RenderComponentData::setPosX(float x)
{
    m_posX = x;
}

void RenderComponentData::setPosY(float y)
{
    m_posY = y;
}

void RenderComponentData::setTexture(unsigned int texture)
{
    m_texture = texture;
}

void RenderComponentData::setShader(unsigned int shader)
{
	m_shader = shader;
}

void RenderComponentData::setLayer(int layer)
{
	m_layer = layer;
}

void RenderComponentData::setWidth(int width)
{
	m_width = width;
}

void RenderComponentData::setHeight(int height)
{
	m_height = height;
}


////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
}