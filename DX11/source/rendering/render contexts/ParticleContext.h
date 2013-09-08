///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ParticleContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle bilboarded particle's render context
///////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLECONTEXT_H
#define _PARTICLECONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"
#include "../shaders/ParticleShader.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class ParticleContext : public IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	ParticleContext();
	~ParticleContext();

	/********** Public Utility Functions ************/

	bool Initialize(wchar_t* textureFilename = '\0', int bitmapWidth = -1, int bitmapHeight = -1);
	void Shutdown();
	void RenderBuffers();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// Vertex struct
	struct ParticleVertex {
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	// DX11 Stuff
	ID3D11Buffer*   m_vertexBuffer;
	// Shader
	ParticleShader* m_particleShader;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
	void ShutdownBuffers();
};
#endif