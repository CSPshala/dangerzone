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


class Texture
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Texture();
	Texture(const Texture& copy);
	~Texture();

	/********** Public Utility Functions ************/
	bool Initialize(const wchar_t* fileName);
	void Shutdown();

	/********** Public Accessors ************/
	ID3D11ShaderResourceView* GetTexture();

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	ID3D11ShaderResourceView* mTexture;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif