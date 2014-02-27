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
#include "../shaders/DiffuseShader.h"
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
	bool UpdateBuffers();
	void RenderBuffers();
	void Shutdown();

	/********** Public Accessors ************/	
	DiffuseShader* GetShader();

	/********** Public Mutators  ************/
	void AddRenderCompToCurrentRenderBuffer(RenderComponentData* component);

private:
	static const int QUAD_VERT_COUNT;
	/********** Private Members ************/
	struct bitmapVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
	
	// Buffer for verticies
	bitmapVertex* m_vertexInfo;	

	// Shaders
	DiffuseShader* m_boxShade;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
};

}
#endif