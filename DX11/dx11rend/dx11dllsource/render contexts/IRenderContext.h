///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IRenderContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for render contexts
///////////////////////////////////////////////////////////////////////////
#ifndef _IRENDERCONTEXT_H
#define _IRENDERCONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include "../defines.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
namespace Renderer
{

class RenderComponentData;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IRenderContext();
	~IRenderContext();
	/********** Public Utility Functions ************/
	virtual bool Initialize(HWND hWnd) = 0;	
	virtual void Shutdown();		
	virtual void RenderBuffers(unsigned int layer) = 0;
	virtual void PrepareBuffers(LayerQueue& renderQueue) = 0;
	virtual bool UpdateBuffers() = 0;
	/********** Public Accessors ************/
	bool AreLayersToRender();

	/********** Public Mutators  ************/
	

protected:
	int m_entityCount;
	// the last end index, to save between layers
	std::deque<unsigned int> m_activeOnLayers;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

private:
	/********** Private Members ************/

	/********** Private Accessors ************/
	virtual unsigned int GetContextType() = 0;	

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/	
	virtual bool InitializeBuffers() = 0;		
	virtual void AddRenderCompToCurrentRenderBuffer(RenderComponentData* component) = 0;
	void ShutdownBuffers();
};

}
#endif  