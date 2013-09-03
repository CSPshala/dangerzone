#ifndef _GLOBALS_H_
#define _GLOBALS_H_

// Tell compiler to shut up that I'm forcing old versions of DirectX headers
#pragma warning( disable: 4005 )

#include <windows.h>
#include <tchar.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#include "rendering\D3D.h"
#include "rendering\Camera.h"

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
	// Crucial rendering globals
	static ID3D11Device* g_Device;
	static ID3D11DeviceContext* g_DeviceContext;
	static ID3D11Buffer* g_constantShaderBuffer;
	static Camera*	   g_Camera;
	static D3D*		   g_D3D;
};


#endif