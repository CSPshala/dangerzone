///////////////////////////////////////////////////////////////////////////
//	File Name	:	"SpriteContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles rendering of a sprite
///////////////////////////////////////////////////////////////////////////
#ifndef _DIFFUSECONTEXT_H
#define _DIFFUSECONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"
#include "DiffuseShader.h"
#include "Texture.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class DiffuseContext : public IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	DiffuseContext();
	~DiffuseContext();

	/********** Public Utility Functions ************/
	bool Initialize(wchar_t* textureFilename = '\0', int bitmapWidth = -1, int bitmapHeight = -1);	
	void Shutdown();		
	/** Positions should be time based before passed to update */
	bool Update(float posX, float posY);
	void Render();

	/********** Public Accessors ************/
	int GetIndexCount();	

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	struct bitmapVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	int m_bitmapWidth, m_bitmapHeight;
	float m_prevPosX, m_prevPosY;	

	// Shaders
	DiffuseShader* m_diffuseShade;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
	bool UpdateBuffers(float posX, float posY);
	void RenderBuffers();	
	void ShutdownBuffers();
	bool LoadTexture(WCHAR* textureFilename);
	void ReleaseTexture();
};
#endif