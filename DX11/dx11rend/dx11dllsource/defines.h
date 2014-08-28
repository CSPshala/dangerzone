// Defines stuff for DLLIMPORT/EXPORT
#ifndef DXDEFINES
#define DXDEFINES

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// Turn off unref variable warning if on release. (Catch sets it off)
#ifndef _DEBUG
#pragma warning(push)
#pragma warning(disable : 4101)
#endif

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <D3DX10math.h>

#include "../targetver.h"

#include "Camera.h"
#include "D3D.h"

#include <tchar.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

#include "dx11shared/RenderComponentData.h"
#include "Texture.h"

namespace Renderer
{

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
	static const float g_ScreenFar; 
	static const float g_ScreenNear;
	static const int   g_MaxRenderComponents;
	static Camera*	   g_Camera;
};

/** Typedefs and common classes/structs **/
class layerCompare
{
public:
	bool operator() (const RenderComponentData* e1, const RenderComponentData* e2) const;
};

struct textureLayerAndCount
{
	textureLayerAndCount() : texture(nullptr), layer(0), count(0) {}

	Texture* texture;
	unsigned int layer;
	unsigned int count;
};

struct colorLayerAndCount
{
	colorLayerAndCount() : layer(0), count(0) {}

	D3DXVECTOR3 color;
	unsigned int layer;
	unsigned int count;
};

typedef std::priority_queue<RenderComponentData*,std::vector<RenderComponentData*>,layerCompare> LayerQueue;

}

#endif