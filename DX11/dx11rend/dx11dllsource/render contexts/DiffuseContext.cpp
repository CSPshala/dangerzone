///////////////////////////////////////////////////////////////////////////
//	File Name	:	"DiffuseContext.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles rendering of a sprite
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../defines.h"
#include "../../../source/Globals.h"
#include "DiffuseContext.h"
#include "../../components/IComponent.h"
#include "../../components/RenderComponent.h"
#include "../../components/Entity.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
const int DiffuseContext::QUAD_VERT_COUNT(6);
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
DiffuseContext::DiffuseContext() : m_vertexInfo(nullptr), m_diffuseShade(nullptr)
{
	m_vertexInfo = new bitmapVertex[QUAD_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents];	
}

DiffuseContext::~DiffuseContext()
{
	if(m_vertexInfo)
	{
		delete[] m_vertexInfo;
		m_vertexInfo = nullptr;
	}
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool DiffuseContext::Initialize()
{
	bool result;

	result = InitializeBuffers();
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize a sprite context.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_diffuseShade = new DiffuseShader("diffuse","diffuse");
	if(!m_diffuseShade)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_diffuseShade->Initialize(GraphicsGlobals::g_Device, WindowGlobals::g_hWnd);
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the diffuse shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void DiffuseContext::Shutdown()
{
	if(m_vertexInfo)
	{
		delete [] m_vertexInfo;
		m_vertexInfo = nullptr;
	}

	// Release the color shader object.
	if(m_diffuseShade)
	{
		m_diffuseShade->Shutdown();
		delete m_diffuseShade;
		m_diffuseShade = nullptr;
	}

	IRenderContext::Shutdown();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool DiffuseContext::InitializeBuffers()
{
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	indices = new unsigned long[QUAD_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents];
	if(!indices)
		return false;

	// Set verts to 0
	memset(m_vertexInfo,0,(sizeof(bitmapVertex) * QUAD_VERT_COUNT)  * GraphicsGlobals::g_MaxRenderComponents);

	// Load index array
	for(int i = 0; i < QUAD_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents; ++i)
		indices[i] = i;

	// Create vertex desc (buffer needs to be dynamic for overwriting verticies on movement)
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = (sizeof(bitmapVertex) * QUAD_VERT_COUNT) * GraphicsGlobals::g_MaxRenderComponents;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = m_vertexInfo;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the buffer
	if(FAILED(GraphicsGlobals::g_Device->CreateBuffer(&vertexBufferDesc,&vertexData,&m_vertexBuffer)))
		return false;

	// Create index buffer desc (no need to be dynamic for obvious reasons)
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = (sizeof(unsigned long) * QUAD_VERT_COUNT) * GraphicsGlobals::g_MaxRenderComponents;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the buffer
	if(FAILED(GraphicsGlobals::g_Device->CreateBuffer(&indexBufferDesc,&indexData,&m_indexBuffer)))
		return false;

	// Kill the memory
	delete[] indices;

	// G2G
	return true;
}

bool DiffuseContext::UpdateBuffers()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	bitmapVertex* verticesPtr;	

	// Lock buffer and write to it
	if(FAILED(GraphicsGlobals::g_DeviceContext->Map(m_vertexBuffer,0, D3D11_MAP_WRITE_DISCARD,0,&mappedResource)))
		return false;

	verticesPtr = static_cast<bitmapVertex*>(mappedResource.pData);

	memcpy(verticesPtr,m_vertexInfo,(sizeof(bitmapVertex) * QUAD_VERT_COUNT) * m_entityCount);

	GraphicsGlobals::g_DeviceContext->Unmap(m_vertexBuffer,0);

	return true;
}

void DiffuseContext::RenderBuffers()
{
	unsigned int stride = sizeof(bitmapVertex);
	unsigned int offset = 0;

	// Matrices for rendering
	D3DXMATRIX viewMatrix, orthoMatrix, worldMatrix;

	GraphicsGlobals::g_Camera->GetViewMatrix(viewMatrix);
	GraphicsGlobals::g_D3D->GetWorldMatrix(worldMatrix);
	GraphicsGlobals::g_D3D->GetOrthoMatrix(orthoMatrix);

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	GraphicsGlobals::g_DeviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	GraphicsGlobals::g_DeviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	GraphicsGlobals::g_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_diffuseShade->Render();

	m_entityCount = 0;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
DiffuseShader* DiffuseContext::GetShader()
{
	return m_diffuseShade;
}

void DiffuseContext::AddRenderCompToCurrentRenderBuffer(RenderComponent* component)
{
	float left,right,top,bottom;
	float posX = component->getParentEntity()->GetPositionX();
	float posY = component->getParentEntity()->GetPositionY();
	// Create our RECT in screen coords
	left = static_cast<float>((ApplicationSettings::g_ResolutionW / 2) * -1) + posX;
	right = left + static_cast<float>(component->getParentEntity()->GetWidth());
	top = static_cast<float>((ApplicationSettings::g_ResolutionH / 2)) - posY;
	bottom = top - static_cast<float>(component->getParentEntity()->GetHeight());

	int index = m_entityCount * QUAD_VERT_COUNT;
	
	// Load the array with verts and tex coords
	m_vertexInfo[index].position = D3DXVECTOR3(left,top,0.0f); // Top left
	m_vertexInfo[index].texture = D3DXVECTOR2(0.0f,0.0f);
	m_vertexInfo[index + 1].position = D3DXVECTOR3(right,bottom,0.0f); // Bot right
	m_vertexInfo[index + 1].texture = D3DXVECTOR2(1.0f,1.0f);
	m_vertexInfo[index + 2].position = D3DXVECTOR3(left,bottom,0.0f); // Bot left
	m_vertexInfo[index + 2].texture = D3DXVECTOR2(0.0f,1.0f);
				 
	m_vertexInfo[index + 3].position = D3DXVECTOR3(left,top,0.0f); // Top left
	m_vertexInfo[index + 3].texture = D3DXVECTOR2(0.0f,0.0f);
	m_vertexInfo[index + 4].position = D3DXVECTOR3(right,top,0.0f); // Top right
	m_vertexInfo[index + 4].texture = D3DXVECTOR2(1.0f,0.0f);
	m_vertexInfo[index + 5].position = D3DXVECTOR3(right,bottom,0.0f); // Bot right
	m_vertexInfo[index + 5].texture = D3DXVECTOR2(1.0f,1.0f);

	m_entityCount++;
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////