// Defines the Import/Export keywords for this DLL
#ifndef DXRENDER_EXPORTS
#define DXRENDER_EXPORTS

#ifdef DX11REND_EXPORTS
#define RENDER_API __declspec(dllexport)
#define RENDER_API_EXTERN extern "C" __declspec(dllexport)
#else
#define RENDER_API __declspec(dllimport)
#define RENDER_API_EXTERN extern "C" __declspec(dllimport)
#endif

#endif