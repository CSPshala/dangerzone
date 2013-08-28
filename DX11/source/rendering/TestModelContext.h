///////////////////////////////////////////////////////////////////////////
//	File Name	:	"TestModelContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Render context for hardcoded test model
///////////////////////////////////////////////////////////////////////////
#ifndef _TESTMODELCONTEXT_H
#define _TESTMODELCONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"
#include "FlatShader.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class TestModelContext : public IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	TestModelContext();
	~TestModelContext();

	/********** Public Utility Functions ************/
	bool Initialize();	
	void Shutdown();	
	void RenderBuffers();	

	/********** Public Accessors ************/
	int GetIndexCount();

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	// Shaders
	FlatShader* m_FlatShade;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
	void ShutdownBuffers();
	
};
#endif