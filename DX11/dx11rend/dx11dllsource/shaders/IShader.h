///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IShader.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Shader class interface
///////////////////////////////////////////////////////////////////////////
#ifndef _ISHADER_H
#define _ISHADER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <string>
using namespace std;

namespace Renderer
{

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Texture;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IShader
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IShader();
	IShader(char* vertexShaderName, char* pixelShaderName, char* geometryShaderName = nullptr);
	~IShader();

	/********** Public Utility Functions ************/
	bool Initialize(ID3D11Device* device, HWND hWnd);
	void Shutdown();
	/** number of indicies to render, offset into buffer, optional voidptr **/
	bool Render();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

	

protected:
	/********** Private Members ************/
	string		m_PixelShaderPath;
	string		m_VertexShaderPath;
	string		m_GeometryShaderPath;
	
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11InputLayout* m_layout;	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

		// Pure virtual
		virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const char* vsFilename, const char* psFilename, const char* gsFilename = nullptr) = 0;		
		virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
						   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix) = 0;
		virtual void RenderShader() = 0;
		virtual void ShutdownShader();
		void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const char* shaderFilename);
};

}
#endif