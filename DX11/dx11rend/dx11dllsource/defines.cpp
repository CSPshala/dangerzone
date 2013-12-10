#include "defines.h"

ID3D11Device*			GraphicsGlobals::g_Device = nullptr;
ID3D11DeviceContext*	GraphicsGlobals::g_DeviceContext = nullptr;
D3D*					GraphicsGlobals::g_D3D = nullptr;
ID3D11Buffer*			GraphicsGlobals::g_constantShaderBuffer = nullptr;

const int				GraphicsGlobals::g_ResolutionW = 1024;
const int				GraphicsGlobals::g_ResolutionH = 768;
const bool				GraphicsGlobals::g_FullScreen = false;
const bool				GraphicsGlobals::g_VSync = true;
const float				GraphicsGlobals::g_ScreenFar = 1000.0f;
const float				GraphicsGlobals::g_ScreenNear = 0.1f;
const int				GraphicsGlobals::g_MaxRenderComponents = 500;
Camera*					GraphicsGlobals::g_Camera = nullptr;