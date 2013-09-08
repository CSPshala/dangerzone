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
#include "DiffuseContext.h"
#include "../../Globals.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
DiffuseContext::DiffuseContext() : m_vertexBuffer(nullptr), m_indexBuffer(nullptr),	m_vertexCount(-1),
	m_indexCount(-1), m_bitmapWidth(-1), m_bitmapHeight(-1), m_prevPosX(0), m_prevPosY(0),
	m_diffuseShade(nullptr)
{
}

DiffuseContext::~DiffuseContext()
{
}


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool DiffuseContext::Initialize(wchar_t* textureFilename, int bitmapWidth, int bitmapHeight)
{
	bool result;

	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	// Init vert and index buffers
	if(!InitializeBuffers())
		return false;

	result = InitializeBuffers();
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize a sprite context.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_diffuseShade = new DiffuseShader(L"diffuse",L"diffuse",textureFilename);
	if(!m_diffuseShade)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_diffuseShade->Initialize(ApplicationSettings::g_Device, WindowGlobals::g_hWnd);
	if(!result)
	{
		MessageBox(WindowGlobals::g_hWnd, L"Could not initialize the diffuse shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool DiffuseContext::Update(float posX, float posY)
{
	if(!UpdateBuffers(posX,posY))
		return false;

	return true;
}

void DiffuseContext::Render()
{
	RenderBuffers();
}

void DiffuseContext::Shutdown()
{
	ShutdownBuffers();

	// Release the color shader object.
	if(m_diffuseShade)
	{
		m_diffuseShade->Shutdown();
		delete m_diffuseShade;
		m_diffuseShade = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool DiffuseContext::InitializeBuffers()
{
	bitmapVertex* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	
	// Quad, so two polys, same indices
	m_vertexCount = m_indexCount = 6;

	vertices = new bitmapVertex[m_vertexCount];
	if(!vertices)
		return false;

	indices = new unsigned long[m_indexCount];
	if(!indices)
		return false;

	// Set verts to 0
	memset(vertices,0,sizeof(bitmapVertex) * m_vertexCount);

	// Load index array
	for(int i = 0; i < m_indexCount; ++i)
		indices[i] = i;

	// Create vertex desc (buffer needs to be dynamic for overwriting verticies on movement)
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(bitmapVertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the buffer
	if(FAILED(ApplicationSettings::g_Device->CreateBuffer(&vertexBufferDesc,&vertexData,&m_vertexBuffer)))
		return false;

	// Create index buffer desc (no need to be dynamic for obvious reasons)
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the buffer
	if(FAILED(ApplicationSettings::g_Device->CreateBuffer(&indexBufferDesc,&indexData,&m_indexBuffer)))
		return false;

	// Kill the memory
	delete[] vertices;
	delete[] indices;

	// G2G
	return true;
}

bool DiffuseContext::UpdateBuffers(float posX, float posY)
{
	// If we've not really moved much, don't update
	//if(G_FLOAT_EPSILON(posX,m_prevPosX) && G_FLOAT_EPSILON(posY,m_prevPosY))
		//return true;

	float left,right,top,bottom;
	bitmapVertex* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	bitmapVertex* verticesPtr;

	// Update prev pos
	m_prevPosX = posX;
	m_prevPosY = posY;

	// Create our RECT in screen coords
	left = static_cast<float>((ApplicationSettings::g_ResolutionW / 2) * -1) + posX;
	right = left + static_cast<float>(m_bitmapWidth);
	top = static_cast<float>((ApplicationSettings::g_ResolutionH / 2)) - posY;
	bottom = top - static_cast<float>(m_bitmapHeight);

	// DEBUG - make a square in center of screen
	/*left = 0.0f;
	right = 64.0f;
	top = 0.0f;
	bottom = -64.0f;*/
	
	// Create a new vertex array
	vertices = new bitmapVertex[m_vertexCount];
	if(!vertices)
		return false;

	// Load the array with verts and tex coords
	vertices[0].position = D3DXVECTOR3(left,top,0.0f); // Top left
	vertices[0].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[1].position = D3DXVECTOR3(right,bottom,0.0f); // Bot right
	vertices[1].texture = D3DXVECTOR2(1.0f,1.0f);
	vertices[2].position = D3DXVECTOR3(left,bottom,0.0f); // Bot left
	vertices[2].texture = D3DXVECTOR2(0.0f,1.0f);

	vertices[3].position = D3DXVECTOR3(left,top,0.0f); // Top left
	vertices[3].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[4].position = D3DXVECTOR3(right,top,0.0f); // Top right
	vertices[4].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[5].position = D3DXVECTOR3(right,bottom,0.0f); // Bot right
	vertices[5].texture = D3DXVECTOR2(1.0f,1.0f);

	// Lock buffer and write to it
	if(FAILED(ApplicationSettings::g_DeviceContext->Map(m_vertexBuffer,0, D3D11_MAP_WRITE_DISCARD,0,&mappedResource)))
		return false;

	verticesPtr = static_cast<bitmapVertex*>(mappedResource.pData);

	memcpy(verticesPtr,static_cast<void*>(vertices),sizeof(bitmapVertex) * m_vertexCount);

	ApplicationSettings::g_DeviceContext->Unmap(m_vertexBuffer,0);

	// Cleanup
	delete [] vertices;

	return true;
}

void DiffuseContext::RenderBuffers()
{
	unsigned int stride = sizeof(bitmapVertex);
	unsigned int offset = 0;

	// Matrices for rendering
	D3DXMATRIX viewMatrix, orthoMatrix, worldMatrix;

	ApplicationSettings::g_Camera->GetViewMatrix(viewMatrix);
	ApplicationSettings::g_D3D->GetWorldMatrix(worldMatrix);
	ApplicationSettings::g_D3D->GetOrthoMatrix(orthoMatrix);

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ApplicationSettings::g_DeviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	ApplicationSettings::g_DeviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	ApplicationSettings::g_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_diffuseShade->Render(m_indexCount);
}

void DiffuseContext::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}

	return;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
int DiffuseContext::GetIndexCount()
{
	return m_indexCount;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////