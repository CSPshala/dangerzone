///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Texture.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles a 2D texture 
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "Texture.h"
#include "../Globals.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Texture::Texture() : m_texture(NULL)
{
}

Texture::Texture(const Texture& copy)
{
	m_texture = copy.m_texture;
}

Texture::~Texture()
{	
}
////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool Texture::Initialize(wchar_t* fileName)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(ApplicationSettings::g_Device, fileName, NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////