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

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IComponent;
class RenderComponent;
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
	virtual bool Initialize(char* textureFilename = '\0', int bitmapWidth = -1, int bitmapHeight = -1) = 0;	
	virtual bool UpdateBuffers() = 0;
	virtual void Shutdown();		
	virtual void RenderBuffers(unsigned int bufferIndex = 0,unsigned int numberToRender = 1) = 0;
	/********** Public Accessors ************/

	/********** Public Mutators  ************/
	virtual void AddRenderCompToCurrentRenderBuffer(RenderComponent* component) = 0;

protected:
	int m_entityCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/	
	virtual bool InitializeBuffers() = 0;	
	void ShutdownBuffers();
};
#endif  