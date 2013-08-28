///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ParticleShader.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle shading of particles
///////////////////////////////////////////////////////////////////////////
#ifndef _CHANGEME_
#define _CHANGEME_

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IShader.h"
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class ParticleShader : public IShader
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	ParticleShader(wchar_t* vertexShaderName, wchar_t* pixelShaderName, wchar_t* geometryShaderName = nullptr);
	~ParticleShader();

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:

	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsFilename, const WCHAR* psFilename,  const WCHAR* gsFilename = nullptr);
	virtual void ShutdownShader();	
	virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
					   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix);
	virtual void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
};
#endif