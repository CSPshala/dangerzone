///////////////////////////////////////////////////////////////////////////
//	File Name	:	"D3D.h"
//	
//	Author Name	:	JC Ricks copy pastaing from: http://www.rastertek.com/dx11tut03.html
//	
//	Purpose		:	Organize new h files
///////////////////////////////////////////////////////////////////////////
#ifndef _D3D_H
#define _D3D_H

// REF: http://www.rastertek.com/dx11tut03.html

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////

#include "defines.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

class D3D
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	D3D();
	D3D(const D3D&);
	~D3D();

	/********** Public Utility Functions ************/
	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	/********** Public Accessors ************/
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};

}
#endif