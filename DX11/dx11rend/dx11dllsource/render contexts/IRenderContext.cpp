///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IRenderContext.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for render contexts
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
IRenderContext::IRenderContext() : m_entityCount(0),
	m_vertexBuffer(nullptr), m_indexBuffer(nullptr)
{
}

IRenderContext::~IRenderContext()
{
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void IRenderContext::Shutdown()
{
	ShutdownBuffers();
}
////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void IRenderContext::ShutdownBuffers()
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

bool IRenderContext::AreLayersToRender()
{
	return (m_activeOnLayers.size() > 0);
}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////


////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////

}