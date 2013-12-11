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
}