///////////////////////////////////////////////////////////////////////////
//	File Name	:	"dx11rendexp.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Provide DLL interface for DX11 renderer
///////////////////////////////////////////////////////////////////////////
#ifndef _DX11RENDEXP_H
#define _DX11RENDEXP_H

////////////////////////////////////////
//		 DLL INTERFACE DEFINES
////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "dx11dllsource\ForwardRenderer.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////

class Rendering
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/
	static RENDER_API bool Initialize(HWND hWnd, int resW, int resH, bool vsync, bool fullscreen);
	static RENDER_API void Shutdown();
	static RENDER_API void RenderQueue();

	/********** Public Accessors ************/
	static RENDER_API void AddRenderComponentToFrame(Renderer::RenderComponentData* component);
	static RENDER_API unsigned int GetTexture(char* textureName);
	static RENDER_API int GetTextureWidth(unsigned int texture);
	static RENDER_API int GetTextureHeight(unsigned int texture);
	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	Rendering();
	~Rendering();
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};

#endif