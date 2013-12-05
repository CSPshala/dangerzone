// Defines stuff for DLLIMPORT/EXPORT

#ifdef DX11_EXPORT
#define DX11_API __declspec(dllexport)
#define DX11_API_EXTERN extern "C" __declspec(dllexport)
#else
#define DX11_API __declspec(dllimport)
#define DX11_API_EXTERN extern "C" __declspec(dllimport)
#endif