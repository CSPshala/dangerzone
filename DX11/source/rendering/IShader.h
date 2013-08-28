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

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IShader
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IShader();
	IShader(wchar_t* vertexShaderName, wchar_t* pixelShaderName, wchar_t* geometryShaderName = nullptr);
	~IShader();

	/********** Public Utility Functions ************/
	bool Initialize(ID3D11Device* device, HWND hWnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX& worldMatrix, 
		D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix);

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

	

protected:
	/********** Private Members ************/
	wstring		m_PixelShaderPath;
	wstring		m_VertexShaderPath;
	wstring		m_GeometryShaderPath;
	
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11InputLayout* m_layout;	

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

		// Pure virtual
		virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* vsFilename, const WCHAR* psFilename, const WCHAR* gsFilename = nullptr) = 0;		
		virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
						   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix) = 0;
		virtual void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount) = 0;

		// Virtual 
		virtual void ShutdownShader();

		// Standard
		void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const WCHAR* shaderFilename);
};
#endif