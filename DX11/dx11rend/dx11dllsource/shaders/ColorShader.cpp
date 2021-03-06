///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ColorShader.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle shader particulars for single solid color objects
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "ColorShader.h"
#include "../TextureManager.h"
#include "../defines.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
ColorShader::ColorShader(char* vertexShaderName, char* pixelShaderName) : IShader(vertexShaderName,pixelShaderName),
	m_sampleState(nullptr)
{
}

ColorShader::~ColorShader()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void ColorShader::AddColorLayerAndCount(colorLayerAndCount add)
{
	m_ColorAndCountPairs.push_back(add);
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool ColorShader::InitializeShader(ID3D11Device* device, HWND hwnd, const char* vsFilename, const char* psFilename,  const char* gsFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code.
	result = D3DX11CompileFromFileA(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			LOG("Missing shader file: " << vsFilename);
		}

		return false;
	}

	// Compile the pixel shader code.
	result = D3DX11CompileFromFileA(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
		{
			LOG("Missing shader file: " << psFilename);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		return false;
	}

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;
	
	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;	
		

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
					   vertexShaderBuffer->GetBufferSize(), &m_layout);
	if(FAILED(result))
	{
		return false;
	}

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;	

	// Geometry shader should be null.
	m_geometryShader = nullptr;

	return true;
}

void ColorShader::ShutdownShader()
{
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = nullptr;
	}

	IShader::ShutdownShader();
}

bool ColorShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX& worldMatrix, 
					   D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix)
{
	return true;		
}

void ColorShader::RenderShader(const unsigned int layer)
{
	// Set the vertex input layout.
	GraphicsGlobals::g_DeviceContext->IASetInputLayout(m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	GraphicsGlobals::g_DeviceContext->VSSetShader(m_vertexShader, NULL, 0);
	GraphicsGlobals::g_DeviceContext->PSSetShader(m_pixelShader, NULL, 0);
	GraphicsGlobals::g_DeviceContext->PSSetSamplers(0,1,&m_sampleState);	

	int renderCount = 0;
	int lastIndex = m_LastIndex;
	unsigned int count = m_ColorAndCountPairs.size();
	for(unsigned int i = 0; i < count && m_ColorAndCountPairs.front().layer == layer; ++i)
	{
		renderCount = m_ColorAndCountPairs.front().count * 5;

		// Render the sprite
		GraphicsGlobals::g_DeviceContext->DrawIndexed( renderCount, lastIndex, 0);

		lastIndex += renderCount;

		m_ColorAndCountPairs.pop_front();
	}

	if(m_ColorAndCountPairs.size() == 0)
		m_LastIndex = 0;
	else
		m_LastIndex = lastIndex;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
}