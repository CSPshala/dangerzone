#include "Globals.h"
// NOTE: Now defining previously declared globals

const int				ApplicationSettings::g_ResolutionW = 1024;
const int				ApplicationSettings::g_ResolutionH = 768;
const bool				ApplicationSettings::g_FullScreen = false;
const bool				ApplicationSettings::g_VSync = true;
const float				ApplicationSettings::g_ScreenFar = 1000.0f;
const float				ApplicationSettings::g_ScreenNear = 0.1f;
ID3D11Device*			ApplicationSettings::g_Device = nullptr;
ID3D11DeviceContext*	ApplicationSettings::g_DeviceContext = nullptr;
Camera*					ApplicationSettings::g_Camera = nullptr;
D3D*					ApplicationSettings::g_D3D = nullptr;
ID3D11Buffer*			ApplicationSettings::g_constantShaderBuffer = nullptr;

HINSTANCE	 WindowGlobals::g_hInstance = 0;
HWND		 WindowGlobals::g_hWnd = 0;
wchar_t		 WindowGlobals::g_szWINDOW_CLASS[15] = L"none";
wchar_t		 WindowGlobals::g_szWINDOW_TITLE[15] = L"none";