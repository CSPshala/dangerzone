///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ParticleContext.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handle bilboarded particle's render context
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "ParticleContext.h"
#include "../Globals.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
ParticleContext::ParticleContext()
{
	m_vertexBuffer = nullptr;
	m_particleShader = nullptr;
}

ParticleContext::~ParticleContext()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool ParticleContext::Initialize()
{
	bool result;

	result = InitializeBuffers();

	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the particle context.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_particleShader = new ParticleShader(L"billboard",L"colors",L"billboard");
	if(!m_particleShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_particleShader->Initialize(ApplicationSettings::g_Device, WindowGlobals::g_hWnd);
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ParticleContext::Shutdown()
{
	ShutdownBuffers();

	// Release the color shader object.
	if(m_particleShader)
	{
		m_particleShader->Shutdown();
		delete m_particleShader;
		m_particleShader = 0;
	}
}

void ParticleContext::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;

	// Matrices for rendering
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;

	ApplicationSettings::g_Camera->GetViewMatrix(viewMatrix);
	ApplicationSettings::g_D3D->GetWorldMatrix(worldMatrix);
	ApplicationSettings::g_D3D->GetProjectionMatrix(projectionMatrix);

	// Set vertex buffer stride and offset.
	stride = sizeof(ParticleVertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ApplicationSettings::g_DeviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	ApplicationSettings::g_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// Render the model using the color shader.
	m_particleShader->Render(ApplicationSettings::g_DeviceContext, 0, 
		worldMatrix, viewMatrix, projectionMatrix);

	return;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool ParticleContext::InitializeBuffers()
{
	ParticleVertex* vertices;	
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	// Create the vertex array.
	vertices = new ParticleVertex[1];
	// Position
	vertices[0].position = D3DXVECTOR3(-2.0f,0.0f,0.0f);
	vertices[0].color = D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f);
	// Create decl
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * 1;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give subresource the pointer to the data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Make vertex buffer
	ApplicationSettings::g_Device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// Cleanup
	delete[] vertices;	

	return true;
}

void ParticleContext::ShutdownBuffers()
{
	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	
	return;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////