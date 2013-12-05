#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <windows.h>
#define WIN32_LEAN_AND_MEAN

#include <tchar.h>
#include <iostream>
#include <sstream>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#ifdef _DEBUG
class DEBUGLOG
{
public:
static std::stringstream G_DEBUGLOGSTREAM;
};
#define LOG(x) DEBUGLOG::G_DEBUGLOGSTREAM << x << "\n"; std::cout << x << "\n"
#else
#define LOG(x)
#endif

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#ifdef DX11_EXPORT
#include "D3D.h"
#else
#include "dx11dllsource/D3D.h"
#endif

#include "rendering/Camera.h"

class WindowGlobals
{
public:
	static HINSTANCE g_hInstance;
	static HWND	  g_hWnd;
	// Globals for window properties
	static wchar_t		g_szWINDOW_CLASS[15];
	static wchar_t		g_szWINDOW_TITLE[15];	
};

class ApplicationSettings
{
public:
	// Stuff here for resolution and such
	static const int   g_ResolutionW;
	static const int   g_ResolutionH;
	static const bool  g_FullScreen;
	static const bool  g_VSync;
	static const float g_ScreenFar; 
	static const float g_ScreenNear;
	static const int   g_MaxRenderComponents;
	// Crucial rendering globals
	static ID3D11Device* g_Device;
	static ID3D11DeviceContext* g_DeviceContext;
	static ID3D11Buffer* g_constantShaderBuffer;
	static Camera*	   g_Camera;
	static D3D*		   g_D3D;
};

struct rectangle 
{
	rectangle();
	float left;
	float top;
	float right;
	float bottom;
	float Width();
	float Height();
};

namespace ENUMS
{
	// Add enums here for created components
	namespace COMPONENTS {
		enum {PLAYER_CONTROLLER = 0, RENDERING, COLLISION, INVALID_COMPONENT};
	};
};

//* Global helper functions */

/** Determine whether two floats are within FLT_EPSILON of each other */
bool G_FLOAT_EPSILON(float left, float right);

#endif