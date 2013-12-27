// DX11.cpp : Defines the entry point for the application.

// TODO: reference additional headers your program requires here
#include "source/Globals.h"
#include <fstream>
#include "DX11.h"
#include "source/core/Game.h"
#include "source/input/RawInputParser.h"
#include "source/input/XbInputParser.h"

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:Console")
#include <vld_def.h>
#include <vld.h>
#else
#pragma comment(linker, "/SUBSYSTEM:Windows")
#endif

#define MAX_LOADSTRING 15

// Forward declarations of functions included in this code module:
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow);
ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HWND MakeWindow(HINSTANCE hInstance);
int  FindOsVersion();
void ClampMouseToWindow();

// Raw input reader
RawInputParser g_RawInputParser;
// Xbox controller input reader
XbInputParser g_XbInputParser;

// Console "main" - only called in Debug Mode
//		Calls Windows' WinMain
int main(int argc, char* argv[])
{
	srand(time_t(0));
	std::cout <<  "Running " << GetCommandLine() << " in Debug Mode\n\n";
	std::cout <<  "Debug Log:\n------------\n\n";
	std::cout <<  "``_```_``````_`_````````__````````__`````````_`````_`\n"
			   << "`|`|`|`|`___|`|`|`___```\\`\\``````/`/__``_`__|`|`__|`|\n"
			   << "`|`|_|`|/`_`\\`|`|/`_`\\```\\`\\`/\\`/`/`_`\\|`'__|`|/`_``|\n"
			   << "`|``_``|``__/`|`|`(_)`|```\\`V``V`/`(_)`|`|``|`|`(_|`|\n"
			   << "`|_|`|_|\\___|_|_|\\___/`````\\_/\\_/`\\___/|_|``|_|\\__,_|\n"
			   << "`````````````````````````````````````````````````````\n";

	LOG("Win Main Start...\n");

	_tWinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOWDEFAULT);

	LOG("Main finished.\n");

#ifdef _DEBUG
	// Write debug log with accumulated stringstream
	std::fstream logFile("DEBUGLOG.LOG", ios::out);
	if(logFile.is_open())
	{
		logFile << DEBUGLOG::G_DEBUGLOGSTREAM.str();
	}
	logFile.close();
#endif
	return 0;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	Game theGame;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, WindowGlobals::g_szWINDOW_TITLE, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DX11, WindowGlobals::g_szWINDOW_CLASS, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Save our HWND && HInstance
	WindowGlobals::g_hWnd = MakeWindow(hInstance);
	HWND temp = WindowGlobals::g_hWnd;
	WindowGlobals::g_hInstance = hInstance;
	
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DX11));

	ShowWindow(WindowGlobals::g_hWnd, nCmdShow);
	UpdateWindow(WindowGlobals::g_hWnd);
	

	// Init game
	if(!theGame.Initialize()) {
		return false; }

	// Register for input
	g_RawInputParser.RegisterForRawInput();

	// Clamp mouse
	ClampMouseToWindow();

	while(WindowGlobals::g_hWnd)
	{
		// Main message loop:
		while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) break;

			// Peek message and dispatch it to the message proc
			TranslateAccelerator(WindowGlobals::g_hWnd,hAccelTable,&msg);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_XbInputParser.ReadInput();

		g_RawInputParser.ProcessInput();

		g_XbInputParser.ProcessInput();

		if(!theGame.Main())
			break;
	}

	// Cleanup game
	theGame.Shutdown();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX11));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;//MAKEINTRESOURCE(IDC_DX11);
	wcex.lpszClassName	= WindowGlobals::g_szWINDOW_CLASS;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

HWND MakeWindow(HINSTANCE hInstance)
{
	unsigned nWindowWidth, nWindowHeight;
	bool bFullScreen;	

	// TODO: Create a loading script for loading vid options
	nWindowWidth = ApplicationSettings::g_ResolutionW;
	nWindowHeight = ApplicationSettings::g_ResolutionH;
	bFullScreen = ApplicationSettings::g_FullScreen;

	DWORD dwWindowStyleFlags = WS_VISIBLE;
	dwWindowStyleFlags |= (bFullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW);

	ShowCursor(FALSE);

	RECT rClientArea  = { 0, 0, nWindowWidth, nWindowHeight };
	AdjustWindowRectEx(&rClientArea, dwWindowStyleFlags, false, WS_EX_APPWINDOW);

	int nClientWidth	= rClientArea.right - rClientArea.left;
	int nClientHeight	= rClientArea.bottom - rClientArea.top;

	HWND hWnd = CreateWindowEx(0, WindowGlobals::g_szWINDOW_CLASS, WindowGlobals::g_szWINDOW_TITLE, dwWindowStyleFlags,										
		(GetSystemMetrics(SM_CXSCREEN)/2) - (nClientWidth/2),
		(GetSystemMetrics(SM_CYSCREEN)/2) - (nClientHeight/2),
		nClientWidth, nClientHeight, HWND_DESKTOP, nullptr, hInstance, nullptr);	

	return hWnd;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_INPUT:
			{
				g_RawInputParser.ReadInput(lParam);
			}
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(WindowGlobals::g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			case IDM_CLOSE:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int  FindOsVersion()
{
	// Find what version of windows we're on for the DirectX SDK
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	// Get version
	if(GetVersionEx(&versionInfo))
	{
		//Win8?
		if(versionInfo.dwMajorVersion == 6 && versionInfo.dwMinorVersion >= 1)
		{
			return 8;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return -1;
	}
}

void ClampMouseToWindow()
{
	RECT windRect;
	GetWindowRect(WindowGlobals::g_hWnd,&windRect);
	ClipCursor(&windRect);
}
