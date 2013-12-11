#include "Globals.h"
// NOTE: Now defining previously declared globals

#ifdef _DEBUG
std::stringstream DEBUGLOG::G_DEBUGLOGSTREAM = std::stringstream();
#endif 

const int				ApplicationSettings::g_ResolutionW = 1024;
const int				ApplicationSettings::g_ResolutionH = 768;
const bool				ApplicationSettings::g_FullScreen = false;
const bool				ApplicationSettings::g_VSync = true;
HINSTANCE	 WindowGlobals::g_hInstance = 0;
HWND		 WindowGlobals::g_hWnd = 0;
wchar_t		 WindowGlobals::g_szWINDOW_CLASS[15] = L"none";
wchar_t		 WindowGlobals::g_szWINDOW_TITLE[15] = L"none";

rectangle::rectangle() : left(-1.0f), top(-1.0f), right(-1.0f), bottom(-1.0f)
{
}

float rectangle::Width()
{
	return right - left;
}

float rectangle::Height()
{
	return bottom - top;
}

bool G_FLOAT_EPSILON(float left, float right)
{
	float dif = left - right;
	return (dif < FLT_EPSILON && dif > -FLT_EPSILON);	
}