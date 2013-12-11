///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ForwardRenderer.h"
//	
//	Author Name	:	JC Ricks copy pastaing from: http://www.rastertek.com/dx11tut03.html
//	
//	Purpose		:	Handles forward DX11 rendering
///////////////////////////////////////////////////////////////////////////
#ifndef _FRENDERER_H
#define _FRENDERER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////

#include "dx11shared\RenderComponentData.h"
#include "defines.h"
#include "D3D.h"
#include <queue>
using namespace std;

namespace Renderer
{

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Camera;
class DiffuseContext;
class D3D;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class FRenderer
{
public:
	/********** Public Utility Functions ************/
	static FRenderer* GetInstance();
	static void DeleteInstance();

	bool Initialize(HWND hWnd, int resW, int resH, bool vsync, bool fullscreen);
	void Shutdown();
	void RenderQueue();	

	/********** Public Accessors ************/
	Camera* GetCamera() { return m_Camera; }
	void AddRenderComponentToFrame(RenderComponentData* component);

	int getResW() { return m_resW; }
	int getResH() { return m_resH; }
	bool getVsync() { return m_vsync; }
	bool getFullscreen() { return m_fullscreen; }

	/********** Public Mutators  ************/	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	FRenderer();
	FRenderer(const FRenderer&);
	~FRenderer();
	FRenderer& operator=(const FRenderer&);

	/********** Private Members ************/
	static FRenderer* m_instance;

	D3D* m_D3D;
	Camera*     m_Camera;

	class layerCompare
	{
	public:
		bool operator() (const RenderComponentData* e1, const RenderComponentData* e2) const;
	};

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX ortho;
		D3DXVECTOR4 camPos;
	};

	ID3D11Buffer* m_matrixBuffer;

	// HWND to our window
	HWND	  m_hWnd;
	// Saved window settings
	int m_resW;
	int m_resH;
	bool m_vsync;
	bool m_fullscreen;

	// Contexts
	DiffuseContext* m_diffuseContext;
	// Vector of textures for diffuse context
	// Staging priority queue for render components
	priority_queue<RenderComponentData*,vector<RenderComponentData*>,layerCompare> m_renderQueue;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool CreateConstantShaderBuffer();
	bool UpdateConstantShaderBuffer();
};

}
#endif