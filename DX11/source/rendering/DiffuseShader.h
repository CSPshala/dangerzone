///////////////////////////////////////////////////////////////////////////
//	File Name	:	"DiffuseShader.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle shader particulars for diffuse textured objects
///////////////////////////////////////////////////////////////////////////
#ifndef _DIFFUSESHADER_H_
#define _DIFFUSESHADER_H_

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IShader.h"
#include "Texture.h"
#include <string>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class DiffuseShader : public IShader
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	DiffuseShader(wchar_t* vertexShaderName, wchar_t* pixelShaderName, wchar_t* textureFilename);
	~DiffuseShader();

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/
	ID3D11ShaderResourceView* GetTexture();

	/********** Public Mutators  ************/	

private:


	/********** Private Members ************/
	ID3D11SamplerState* m_sampleState;
	Texture* m_texture;
	wstring  m_textureFileName;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsFilename, const WCHAR* psFilename, const WCHAR* gsFilename = nullptr);
	virtual void ShutdownShader();	
	virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
					   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix);
	virtual void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
	bool LoadTexture(const wchar_t* textureFilename);
	void ReleaseTexture();
};
#endif