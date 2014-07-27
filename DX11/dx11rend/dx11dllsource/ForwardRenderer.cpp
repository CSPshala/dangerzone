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
#include "D3D.h"
#include "Camera.h"
#include "render contexts/ContextManager.h"
#include "TextureManager.h"
#include "render contexts/DiffuseContext.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

FRenderer* FRenderer::m_instance(nullptr);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
FRenderer::FRenderer()
{
	m_D3D = nullptr;
	m_Camera = nullptr;
}

FRenderer::~FRenderer()
{
}
////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool FRenderer::Initialize(HWND hWnd, int resW, int resH, bool vsync, bool fullscreen)
{
	bool result;

	m_resW = resW;
	m_resH = resH;
	m_vsync = vsync;
	m_fullscreen = fullscreen;

	// Save window handle
	m_hWnd = hWnd;

	// Create the Direct3D object.
	m_D3D = new D3D;
	if(!m_D3D)
	{
		return false;
	}

	// Save D3D
	GraphicsGlobals::g_D3D = m_D3D;

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(m_resW, m_resH, m_vsync, m_hWnd, m_fullscreen,
		GraphicsGlobals::g_ScreenFar, GraphicsGlobals::g_ScreenNear);
	if(!result)
	{
		MessageBox(m_hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if(!m_Camera)
	{
		return false;
	}

	// Save camera
	GraphicsGlobals::g_Camera = m_Camera;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create constant buffer that all shaders can use
	if(!CreateConstantShaderBuffer())
	{
		MessageBox(m_hWnd, L"Could not initialize constant shader buffer.", L"Error", MB_OK);
		return false;
	}	

	// Render (it's really update, sigh) camera once and update for view/orth/world mats that 
	// never need to change ever again
	m_Camera->Render();
	UpdateConstantShaderBuffer();

	// Init context manager
	if(ContextManager::GetInstance()->Initialize(m_hWnd))	
	{
		LOG("Renderer initialization successfully completed.");
	}
	else
	{
		LOG("Render init failed...");
		return false;
	}

	return true;
}

void FRenderer::Shutdown()
{	
	LOG("Renderer shutting down.");

	ContextManager::GetInstance()->DeleteInstance();
	TextureManager::GetInstance()->DeleteInstance();

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

#ifdef _DEBUG
	// Write debug log with accumulated stringstream
	std::fstream logFile("DX11RENDERER.LOG", ios::out);
	if(logFile.is_open())
	{
		logFile << DEBUGLOG::G_DEBUGLOGSTREAM.str();
	}
	logFile.close();
#endif

	return;
}

void FRenderer::RenderQueue()
{
	// If we're not rendering anything, don't render
	if(m_renderQueue.size() == 0)
		return;

	ContextManager::GetInstance()->PrepareContexts(m_renderQueue);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.2f, 0.2f, 0.0f, 1.0f);

	ContextManager::GetInstance()->RenderContexts();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	// Get rid of old priority queue
	m_renderQueue = LayerQueue();
}

FRenderer* FRenderer::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new FRenderer;

	return m_instance;
}

void FRenderer::DeleteInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
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
	result = GraphicsGlobals::g_Device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Save constant buffer
	GraphicsGlobals::g_constantShaderBuffer = m_matrixBuffer;

	return true;
}

bool FRenderer::UpdateConstantShaderBuffer()
{
	MatrixBufferType* dataPtr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result;
	unsigned int bufferNumber;

	// Matrices for rendering
	D3DXMATRIX viewMatrix, orthoMatrix, worldMatrix;

	GraphicsGlobals::g_Camera->GetViewMatrix(viewMatrix);
	GraphicsGlobals::g_D3D->GetWorldMatrix(worldMatrix);
	GraphicsGlobals::g_D3D->GetOrthoMatrix(orthoMatrix);

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&orthoMatrix, &orthoMatrix);

	// Lock the constant buffer so it can be written to.
	result = GraphicsGlobals::g_DeviceContext->Map(m_matrixBuffer, 0, 
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
	dataPtr->ortho = orthoMatrix;
	dataPtr->camPos = D3DXVECTOR4(GraphicsGlobals::g_Camera->GetPosition(),1.0f);

	// Unlock the constant buffer.
	GraphicsGlobals::g_DeviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	GraphicsGlobals::g_DeviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);	

	// Save matrix buffer setting
	GraphicsGlobals::g_constantShaderBuffer = m_matrixBuffer;

	return true;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
void FRenderer::AddRenderComponentToFrame(RenderComponentData* component)
{
	m_renderQueue.push(component);
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
}