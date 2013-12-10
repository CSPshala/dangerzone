///////////////////////////////////////////////////////////////////////////
//	File Name	:	"SpriteContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles rendering of a sprite
///////////////////////////////////////////////////////////////////////////
#ifndef _DIFFUSECONTEXT_H
#define _DIFFUSECONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "IRenderContext.h"
#include "../shaders/DiffuseShader.h"
#include "../Texture.h"
#include "../dx11shared/RenderComponentData.h"
#include <vector>
using namespace std;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class RenderComponent;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class DiffuseContext : public IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	DiffuseContext();
	~DiffuseContext();

	/********** Public Utility Functions ************/
	bool Initialize();
	bool UpdateBuffers();
	void RenderBuffers();
	void Shutdown();

	/********** Public Accessors ************/	
	DiffuseShader* GetShader();

	/********** Public Mutators  ************/
	void AddRenderCompToCurrentRenderBuffer(RenderComponentData* component);

private:
	static const int QUAD_VERT_COUNT;
	/********** Private Members ************/
	struct bitmapVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
	
	// Buffer for verticies
	bitmapVertex* m_vertexInfo;	

	// Shaders
	DiffuseShader* m_diffuseShade;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool InitializeBuffers();
};
#endif