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
#include "../Globals.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Emitter;
class Model;
class D3D;
class Camera;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class FRenderer
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	FRenderer();
	FRenderer(const FRenderer&);
	~FRenderer();

	/********** Public Utility Functions ************/
	bool Initialize();
	void Shutdown();
	bool Render();

	/********** Public Accessors ************/
	Camera* GetCamera() { return m_Camera; }

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	D3D* m_D3D;
	Camera*     m_Camera;
	Model*	    m_Model;	
	Emitter*	m_Emitter;

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
		D3DXVECTOR4 camPos;
	};

	ID3D11Buffer* m_matrixBuffer;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool _render();
	bool CreateConstantShaderBuffer();
	bool UpdateConstantShaderBuffer();
};
#endif