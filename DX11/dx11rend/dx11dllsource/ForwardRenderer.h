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
#include "defines.h"
#include "Globals.h"

#include "dx11shared\RenderComponentData.h"
#include <queue>
using namespace std;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Camera;
class DiffuseContext;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class FRenderer
{
public:
	/********** Public Utility Functions ************/
	static FRenderer* GetInstance();
	static void DeleteInstance();

	bool Initialize();
	void Shutdown();
	void RenderQueue();	

	/********** Public Accessors ************/
	Camera* GetCamera() { return m_Camera; }
	void AddRenderComponentToFrame(RenderComponentData* component);

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
		bool operator() (const RenderComponentData* e1, const RenderComponentData* e2) const
		{
			// If layers are same and pointer to texture address is lower (cause reasons)
			// trying to order same texture components together
			if(e1->getLayer() == e2->getLayer())
			{
				if(e1->getTexture() < e2->getTexture())
					return true;
				else
					return false;
			}		
			// If not, compare layers
			return e1->getLayer() < e2->getLayer();
		}
	};

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX ortho;
		D3DXVECTOR4 camPos;
	};

	ID3D11Buffer* m_matrixBuffer;

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
#endif