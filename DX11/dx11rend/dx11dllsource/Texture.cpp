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
#include "defines.h"
#include "Texture.h"
#include <string>
using namespace std;


////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
Texture::Texture() : m_texture(nullptr), m_width(0), m_height(0)
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
bool Texture::Initialize(const char* fileName)
{
	// Add path to filename
	string filePath = "resource/sprites/";
	filePath += fileName;

	// Load the texture in.
    if(FAILED(D3DX11CreateShaderResourceViewFromFileA(GraphicsGlobals::g_Device, filePath.c_str(), NULL, NULL, &m_texture, NULL)))
		return false;

	D3DX11_IMAGE_INFO texDesc;
	if(FAILED(D3DX11GetImageInfoFromFileA(filePath.c_str(),NULL,&texDesc,NULL)))
		return false;
	
	m_width = texDesc.Width;
	m_height = texDesc.Height;

	return true;
}

void Texture::Shutdown()
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;
}

int Texture::GetHeight()
{
	return m_height;
}

int Texture::GetWidth()
{
	return m_width;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
}