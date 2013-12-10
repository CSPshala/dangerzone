// Defines stuff for DLLIMPORT/EXPORT
#ifndef DXDEFINES
#define DXDEFINES

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "../targetver.h"

#include <d3d11.h>
#include <d3dx10math.h>
#include <dxgi.h>
#include <d3dcommon.h>

#include "Camera.h"
#include "D3D.h"

class D3D;

class GraphicsGlobals
{
public:
	// Crucial rendering globals
	static ID3D11Device* g_Device;
	static ID3D11DeviceContext* g_DeviceContext;
	static ID3D11Buffer* g_constantShaderBuffer;
	static D3D*		   g_D3D;
	// Stuff here for resolution and such
	static const int   g_ResolutionW;
	static const int   g_ResolutionH;
	static const bool  g_FullScreen;
	static const bool  g_VSync;
	static const float g_ScreenFar; 
	static const float g_ScreenNear;
	static const int   g_MaxRenderComponents;
	static Camera*	   g_Camera;
};

#endif