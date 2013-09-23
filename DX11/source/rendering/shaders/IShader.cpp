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
#include "../../Globals.h"
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

IShader::IShader(char* vertexShaderName, char* pixelShaderName, char* geometryShaderName)
{
	m_geometryShader = nullptr;
	m_pixelShader = nullptr;
	m_vertexShader = nullptr;

	string shaderPath = "resource/shaders/";

	m_VertexShaderPath = shaderPath + vertexShaderName + ".vs";
	m_PixelShaderPath  = shaderPath + pixelShaderName + ".ps";

	if(geometryShaderName)
	{
		m_GeometryShaderPath = shaderPath + geometryShaderName + ".gs";
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

bool IShader::Render(int indexCount,int offset)
{
	// Set the shader parameters that it will use for rendering.
	// TODO: Implement
	// bool result;
	/*result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}*/

	// Now render the prepared buffers with the shader.
	RenderShader(indexCount,offset);

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

void IShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const char* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	string output = shaderFilename;
	output += "-error.txt";

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

	string msgTxt = "Error compiling shader.  Check " + output + " for message.";

	LOG(msgTxt);
	return;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////