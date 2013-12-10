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
#include "../Texture.h"
#include <string>
#include <vector>
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
	DiffuseShader(char* vertexShaderName,char* pixelShaderName);
	~DiffuseShader();

	/********** Public Utility Functions ************/
	void AddTextureAndCountPair(pair<Texture*,int> add);

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	ID3D11SamplerState* m_sampleState;
	// Textures and # of entities
	vector<pair<Texture*,int> > m_TextureAndCountPairs;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const char* vsFilename, const char* psFilename, const char* gsFilename = nullptr);
	virtual void ShutdownShader();	
	virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
					   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix);
	virtual void RenderShader();
};
#endif