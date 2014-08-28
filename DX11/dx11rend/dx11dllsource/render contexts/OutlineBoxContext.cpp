///////////////////////////////////////////////////////////////////////////
//	File Name	:	"OutlineBoxContext.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles rendering of a sprite
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../defines.h"
#include "OutlineBoxContext.h"
#include "../ForwardRenderer.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

const int OutlineBoxContext::LINE_VERT_COUNT(5);
const unsigned int OutlineBoxContext::OUTLINEBOXCONTEXTTYPE(1);
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
OutlineBoxContext::OutlineBoxContext() : m_vertexInfo(nullptr), m_colorShade(nullptr)
{
	m_vertexInfo = new lineVertex[LINE_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents];	
}

OutlineBoxContext::~OutlineBoxContext()
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
bool OutlineBoxContext::Initialize(HWND hWnd)
{
	bool result;

	result = InitializeBuffers();
	if(!result)
	{
		MessageBox(hWnd, L"Could not initialize an outline box context.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_colorShade = new ColorShader("colors","colors");
	if(!m_colorShade)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_colorShade->Initialize(GraphicsGlobals::g_Device, hWnd);
	if(!result)
	{
		MessageBox(hWnd, L"Could not initialize the colors shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void OutlineBoxContext::PrepareBuffers(LayerQueue& renderQueue)
{
	// Add components to buffer in order based on layer but bounce if we run into another context
	// on the same layer, we'll come back.
	unsigned int size = renderQueue.size();
	// save the layer and what index it's at
	unsigned int layer = renderQueue.top()->getLayer();

	// Save what layers we have entities on
	m_activeOnLayers.push_back(layer);

	// The Texture and count of how many in a row and what layer
	colorLayerAndCount tlc;
	tlc.layer = layer;
	tlc.count = 1;
	
	for(unsigned int i = 0; i < size && 
		renderQueue.top()->getShader() == GetContextType() && 
		renderQueue.top()->getLayer() == layer; ++i)
	{		
		// Add it
		GetShader()->AddColorLayerAndCount(tlc);
		AddRenderCompToCurrentRenderBuffer(renderQueue.top());

		renderQueue.pop();
	}	
}

void OutlineBoxContext::Shutdown()
{
	if(m_vertexInfo)
	{
		delete [] m_vertexInfo;
		m_vertexInfo = nullptr;
	}

	// Release the color shader object.
	if(m_colorShade)
	{
		m_colorShade->Shutdown();
		delete m_colorShade;
		m_colorShade = nullptr;
	}

	IRenderContext::Shutdown();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool OutlineBoxContext::InitializeBuffers()
{
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	indices = new unsigned long[LINE_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents];
	if(!indices)
		return false;

	// Set verts to 0
	memset(m_vertexInfo,0,(sizeof(lineVertex) * LINE_VERT_COUNT)  * GraphicsGlobals::g_MaxRenderComponents);

	// Load index array
	for(int i = 0; i < LINE_VERT_COUNT * GraphicsGlobals::g_MaxRenderComponents; ++i)
		indices[i] = i;

	// Create vertex desc (buffer needs to be dynamic for overwriting verticies on movement)
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = (sizeof(lineVertex) * LINE_VERT_COUNT) * GraphicsGlobals::g_MaxRenderComponents;
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
	indexBufferDesc.ByteWidth = (sizeof(unsigned long) * LINE_VERT_COUNT) * GraphicsGlobals::g_MaxRenderComponents;
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

bool OutlineBoxContext::UpdateBuffers()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	lineVertex* verticesPtr;	

	// Lock buffer and write to it
	if(FAILED(GraphicsGlobals::g_DeviceContext->Map(m_vertexBuffer,0, D3D11_MAP_WRITE_DISCARD,0,&mappedResource)))
		return false;

	verticesPtr = static_cast<lineVertex*>(mappedResource.pData);

	memcpy(verticesPtr,m_vertexInfo,(sizeof(lineVertex) * LINE_VERT_COUNT) * m_entityCount);

	GraphicsGlobals::g_DeviceContext->Unmap(m_vertexBuffer,0);

	return true;
}

void OutlineBoxContext::RenderBuffers(unsigned int layer)
{
	if(m_activeOnLayers.front() != layer)
		return;
	else
		m_activeOnLayers.pop_front();

	unsigned int stride = sizeof(lineVertex);
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
	GraphicsGlobals::g_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	m_colorShade->Render(layer);
	
	m_entityCount = 0;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
ColorShader* OutlineBoxContext::GetShader()
{
	return m_colorShade;
}

unsigned int OutlineBoxContext::GetContextType()
{
	return OUTLINEBOXCONTEXTTYPE;
}

void OutlineBoxContext::AddRenderCompToCurrentRenderBuffer(RenderComponentData* component)
{
	float left,right,top,bottom;
    float posX = component->getPosX();
	float posY = component->getPosY();
	// Create our RECT in screen coords
	left = static_cast<float>((FRenderer::GetInstance()->getResW() / 2) * -1) + posX;
	right = left + static_cast<float>(component->getWidth());
    top = static_cast<float>((FRenderer::GetInstance()->getResH() / 2)) - posY;
	bottom = top - static_cast<float>(component->getHeight());

	int index = m_entityCount * LINE_VERT_COUNT;
	
	// Load the array with verts and tex coords
	m_vertexInfo[index].position = D3DXVECTOR3(left,top,0.0f); // Top left
	m_vertexInfo[index].color = D3DXVECTOR3(1.0f,0.0f,0.0f); // Set vert color red

	m_vertexInfo[index + 1].position = D3DXVECTOR3(right,top,0.0f); // Top right
	m_vertexInfo[index + 1].color = D3DXVECTOR3(1.0f,0.0f,0.0f); // Set vert color red
	
	m_vertexInfo[index + 2].position = D3DXVECTOR3(right,bottom,0.0f); // Bot right
	m_vertexInfo[index + 2].color = D3DXVECTOR3(1.0f,0.0f,0.0f); // Set vert color red
	
	m_vertexInfo[index + 3].position = D3DXVECTOR3(left,bottom,0.0f); // Bot left
	m_vertexInfo[index + 3].color = D3DXVECTOR3(1.0f,0.0f,0.0f); // Set vert color red

	m_vertexInfo[index + 4].position = D3DXVECTOR3(left,top,0.0f); // Top left to close it
	m_vertexInfo[index + 4].color = D3DXVECTOR3(1.0f,0.0f,0.0f); // Set vert color red

	m_entityCount++;
}

}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////