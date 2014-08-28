///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ColorShader.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle shader particulars for single solid color objects
///////////////////////////////////////////////////////////////////////////
#ifndef _COLORSHADER_H_
#define _COLORSHADER_H_

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IShader.h"
#include "../defines.h"
#include <string>
#include <vector>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

class ColorShader : public IShader
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	ColorShader(char* vertexShaderName,char* pixelShaderName);
	~ColorShader();

	/********** Public Utility Functions ************/
	void AddColorLayerAndCount(colorLayerAndCount add);

	/********** Public Accessors ************/	

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	ID3D11SamplerState* m_sampleState;
	// Textures and # of entities
	deque<colorLayerAndCount> m_ColorAndCountPairs;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const char* vsFilename, const char* psFilename, const char* gsFilename = nullptr);
	virtual void ShutdownShader();	
	virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
					   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix);
	virtual void RenderShader(const unsigned int layer);
};

}
#endif