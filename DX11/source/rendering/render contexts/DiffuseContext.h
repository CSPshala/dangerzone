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
#include "../shaders/DiffuseShader.h"
#include "../Texture.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class RenderComponent;
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
	bool Initialize(char* textureFilename = '\0', int bitmapWidth = -1, int bitmapHeight = -1);
	bool UpdateBuffers();
	void RenderBuffers(unsigned int bufferIndex = 0,unsigned int numberToRender = 1);
	void Shutdown();

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/
	void AddRenderCompToCurrentRenderBuffer(RenderComponent* component);

private:
	/********** Private Members ************/
	struct bitmapVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	static const int QUAD_VERT_COUNT;

	bitmapVertex* m_vertexInfo;

	int m_nextVertexInfoIndex;
	int m_bitmapWidth, m_bitmapHeight;
	float m_prevPosX, m_prevPosY;

	// Shaders
	DiffuseShader* m_diffuseShade;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
};
#endif