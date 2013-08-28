///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ForwardRenderer.cpp"
//	
//	Author Name	:	JC Ricks copy pastaing from: http://www.rastertek.com/dx11tut03.html
//	
//	Purpose		:	Handles forward DX11 rendering
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "ForwardRenderer.h"
#include "../Globals.h"
#include "D3D.h"
#include "Camera.h"
#include "Model.h"
#include "../particles/Emitter.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
FRenderer::FRenderer()
{
	m_D3D = nullptr;
	m_Camera = nullptr;
	m_Model = nullptr;	
	m_Emitter = nullptr;
}

FRenderer::FRenderer(const FRenderer& in)
{
}

FRenderer::~FRenderer()
{
}


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool FRenderer::Initialize()
{
	bool result;

		
	// Create the Direct3D object.
	m_D3D = new D3D;
	if(!m_D3D)
	{
		return false;
	}

	// Save D3D
	ApplicationSettings::g_D3D = m_D3D;

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(ApplicationSettings::g_ResolutionW, ApplicationSettings::g_ResolutionH,
		ApplicationSettings::g_VSync, WindowGlobals::g_hWnd, ApplicationSettings::g_FullScreen, 
		ApplicationSettings::g_ScreenFar, ApplicationSettings::g_ScreenNear);
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if(!m_Camera)
	{
		return false;
	}

	// Save camera
	ApplicationSettings::g_Camera = m_Camera;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create constant buffer that all shaders can use
	if(!CreateConstantShaderBuffer())
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize constant shader buffer.", L"Error", MB_OK);
		return false;
	}	
	
	// Create the model object.
	m_Model = new Model;
	if(!m_Model)
	{
		return false;
	}
	
	// Initialize the model object.
	result = m_Model->Initialize();
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}	

	m_Emitter = new Emitter();
	if(!m_Emitter)
	{
		return false;
	}

	result = m_Emitter->Initialize();
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the emitter object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void FRenderer::Shutdown()
{
	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if(m_Emitter)
	{
		m_Emitter->Shutdown();
		delete m_Emitter;
		m_Emitter = 0;
	}

	// Release the matrix constant buffer.
	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool FRenderer::Render()
{
	bool result;


	// Render the graphics scene.
	result = _render();
	if(!result)
	{
		return false;
	}

	return true;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool FRenderer::_render()
{
	UpdateConstantShaderBuffer();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.	
	m_Emitter->Render();

	m_Model->Render();	
	
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool FRenderer::CreateConstantShaderBuffer()
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	HRESULT result;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = ApplicationSettings::g_Device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Save constant buffer
	ApplicationSettings::g_constantShaderBuffer = m_matrixBuffer;

	return true;
}

bool FRenderer::UpdateConstantShaderBuffer()
{
	MatrixBufferType* dataPtr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result;
	unsigned int bufferNumber;

	// Matrices for rendering
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;

	ApplicationSettings::g_Camera->GetViewMatrix(viewMatrix);
	ApplicationSettings::g_D3D->GetWorldMatrix(worldMatrix);
	ApplicationSettings::g_D3D->GetProjectionMatrix(projectionMatrix);

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = ApplicationSettings::g_DeviceContext->Map(m_matrixBuffer, 0, 
		D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	dataPtr->camPos = D3DXVECTOR4(ApplicationSettings::g_Camera->GetPosition(),1.0f);

	// Unlock the constant buffer.
	ApplicationSettings::g_DeviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	ApplicationSettings::g_DeviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	ApplicationSettings::g_DeviceContext->GSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Save matrix buffer setting
	ApplicationSettings::g_constantShaderBuffer = m_matrixBuffer;

	return true;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////