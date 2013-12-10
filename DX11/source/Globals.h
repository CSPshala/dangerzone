#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <windows.h>
#define WIN32_LEAN_AND_MEAN

#include <tchar.h>
#include <iostream>
#include <sstream>

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