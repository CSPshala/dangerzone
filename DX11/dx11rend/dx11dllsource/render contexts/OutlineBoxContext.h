///////////////////////////////////////////////////////////////////////////
//	File Name	:	"OutlineBoxContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles rendering of a selection box
///////////////////////////////////////////////////////////////////////////
#ifndef _OUTLINEBOXCONTEXT_H
#define _OUTLINEBOXCONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"
#include "../shaders/ColorShader.h"
#include "../Texture.h"
#include "../dx11shared/RenderComponentData.h"
#include <vector>
using namespace std;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

class OutlineBoxContext : public IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	OutlineBoxContext();
	~OutlineBoxContext();

	/********** Public Utility Functions ************/
	bool Initialize(HWND hWnd);	
	void RenderBuffers(unsigned int layer);
	void PrepareBuffers(LayerQueue& renderQueue);
	bool UpdateBuffers();
	void Shutdown();

	/********** Public Accessors ************/	
	ColorShader* GetShader();

	/********** Public Mutators  ************/
	void AddRenderCompToCurrentRenderBuffer(RenderComponentData* component);

private:
	static const int LINE_VERT_COUNT;
	static const unsigned int OUTLINEBOXCONTEXTTYPE;
	/********** Private Members ************/
	struct lineVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 color;
	};
	
	// Buffer for verticies
	lineVertex* m_vertexInfo;	

	// Shaders
	ColorShader* m_colorShade;

	/********** Private Accessors ************/
	unsigned int GetContextType();

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	
	bool InitializeBuffers();

};

}
#endif