///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Texture.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle a 2D texture
///////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURE_H
#define _TEXTURE_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <d3d11.h>
#include <D3DX11tex.h>

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

class Texture
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Texture();
	Texture(const Texture& copy);
	~Texture();

	/********** Public Utility Functions ************/
	bool Initialize(const char* fileName);
	void Shutdown();

	/********** Public Accessors ************/
	ID3D11ShaderResourceView* GetTexture();
	int	GetWidth();
	int GetHeight();

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	ID3D11ShaderResourceView* m_texture;
	int m_width;
	int m_height;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};

}
#endif