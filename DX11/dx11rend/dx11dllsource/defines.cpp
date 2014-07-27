#include "defines.h"
namespace Renderer
{

#ifdef _DEBUG
std::stringstream DEBUGLOG::G_DEBUGLOGSTREAM = std::stringstream();
#endif 

ID3D11Device*			GraphicsGlobals::g_Device = nullptr;
ID3D11DeviceContext*	GraphicsGlobals::g_DeviceContext = nullptr;
D3D*					GraphicsGlobals::g_D3D = nullptr;
ID3D11Buffer*			GraphicsGlobals::g_constantShaderBuffer = nullptr;

const float				GraphicsGlobals::g_ScreenFar = 1000.0f;
const float				GraphicsGlobals::g_ScreenNear = 0.1f;
const int				GraphicsGlobals::g_MaxRenderComponents = 500;
Camera*					GraphicsGlobals::g_Camera = nullptr;


bool layerCompare::operator() (const RenderComponentData* e1, const RenderComponentData* e2) const
{
	// If layers are same and pointer to texture address is lower (cause reasons)
	// trying to order same texture components together
	if(e1->getLayer() == e2->getLayer())
	{
		if(e1->getShader() == e2->getShader())
		{
			if(e1->getTexture() < e2->getTexture())
				return true;
			else
				return false;
		}
		else
		{
			return e1->getShader() > e2->getShader();
		}
	}		
	// If not, compare layers (we want larger layer # on top, 0 == bottom)
	return e1->getLayer() > e2->getLayer();
}

}