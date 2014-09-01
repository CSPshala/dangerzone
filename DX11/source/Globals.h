#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <windows.h>
#define WIN32_LEAN_AND_MEAN

// Turn off unref variable warning if on release. (Catch sets it off)
#ifndef _DEBUG
#pragma warning(push)
#pragma warning(disable : 4101)
#endif

#include <tchar.h>
#include <iostream>
#include <sstream>

#include "math/vec3.h"

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
	// Crucial rendering globals
	static const int   g_ResolutionW;
	static const int   g_ResolutionH;
	static const bool  g_FullScreen;
	static const bool  g_VSync;
};

struct rectangle 
{
	rectangle();
	// Max.x = right, Max.y = bottom
	// Min.x = left, Min.y = top
	vec3<float> Min;
	vec3<float> Max;
	float Width();
	float Height();
};

namespace ENUMS
{
	// Add enums here for created components	
		enum COMPONENTS {PLAYER_CONTROLLER = 0, RENDERING, RECT_COLLISION, MOUSE_CONTROLLER,
			CIRCLE_COLLISION, POINT_COLLISION, INVALID_COMPONENT};
	
};

//* Global helper functions */

/** Determine whether two floats are within FLT_EPSILON of each other */
bool G_FLOAT_EPSILON(float left, float right);

#endif