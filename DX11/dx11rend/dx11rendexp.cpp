///////////////////////////////////////////////////////////////////////////
//	File Name	:	"dx11rendexp.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Provide DLL interface for DX11 renderer
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "dx11rendexp.h"
#include "dx11dllsource/ForwardRenderer.h"
#include "dx11dllsource/TextureManager.h"
#include "dx11dllsource/Texture.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool Rendering::Initialize(HWND hWnd, int resW, int resH, bool vsync, bool fullscreen)
{
	return Renderer::FRenderer::GetInstance()->Initialize(hWnd, resW, resH, vsync, fullscreen);	
}

void Rendering::Shutdown()
{
	Renderer::FRenderer::GetInstance()->Shutdown();
	Renderer::FRenderer::GetInstance()->DeleteInstance();
}

void Rendering::RenderQueue()
{
	Renderer::FRenderer::GetInstance()->RenderQueue();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
void Rendering::AddRenderComponentToFrame(Renderer::RenderComponentData* component)
{
	Renderer::FRenderer::GetInstance()->AddRenderComponentToFrame(component);
}

unsigned int Rendering::GetTexture(const char* textureName)
{
	return Renderer::TextureManager::GetInstance()->GetTexture(textureName);
}

int Rendering::GetTextureWidth(unsigned int texture)
{
	return reinterpret_cast<Renderer::Texture*>(texture)->GetWidth();
}

int Rendering::GetTextureHeight(unsigned int texture)
{
	return reinterpret_cast<Renderer::Texture*>(texture)->GetHeight();
}
////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
