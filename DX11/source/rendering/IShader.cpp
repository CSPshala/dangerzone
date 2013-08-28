///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IShader.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Shader class interface
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IShader.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
IShader::IShader()
{
}

IShader::IShader(wchar_t* vertexShaderName, wchar_t* pixelShaderName, wchar_t* geometryShaderName)
{
	m_geometryShader = nullptr;
	m_pixelShader = nullptr;
	m_vertexShader = nullptr;

	wstring shaderPath = L"resource/shaders/";

	m_VertexShaderPath = shaderPath + vertexShaderName + L".vs";
	m_PixelShaderPath  = shaderPath + pixelShaderName + L".ps";

	if(geometryShaderName)
	{
		m_GeometryShaderPath = shaderPath + geometryShaderName + L".gs";
	}
}

IShader::~IShader()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool IShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, m_VertexShaderPath.c_str(), m_PixelShaderPath.c_str(),m_GeometryShaderPath.c_str());
	if(!result)
	{
		return false;
	}

	return true;
}

void IShader::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

bool IShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX& worldMatrix, 
		D3DXMATRIX& viewMatrix, D3DXMATRIX& projectionMatrix)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

void IShader::ShutdownShader()
{
	// Release the layout.
	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader.
	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// Release the vertex shader.
	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	if(m_geometryShader)
	{
		m_geometryShader->Release();
		m_geometryShader = 0;
	}

	return;
}

void IShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	wstring output = shaderFilename;
	output += L"-error.txt";

	// Open a file to write the error message to.
	fout.open(output);

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	wstring msgTxt = L"Error compiling shader.  Check " + output + L" for message.";

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd,msgTxt.c_str(), shaderFilename, MB_OK);

	return;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////