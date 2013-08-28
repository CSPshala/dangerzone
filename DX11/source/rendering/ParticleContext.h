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
#include "ParticleShader.h"
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

	bool Initialize();
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