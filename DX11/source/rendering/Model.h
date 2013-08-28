///////////////////////////////////////////////////////////////////////////
//	File Name	:	"Model.h"
//	
//	Author Name	:	JC Ricks copy-pasta from http://www.rastertek.com/dx11tut04.html
//	
//	Purpose		:	Hold model / mesh data
///////////////////////////////////////////////////////////////////////////
#ifndef _MODEL_H
#define _MODEL_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "TestModelContext.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class Model
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	Model();
	Model(const Model&);
	~Model();

	/********** Public Utility Functions ************/
	bool Initialize();
	void Shutdown();
	void Render();	

	/********** Public Accessors ************/
	TestModelContext* GetContext() { return &m_RenderContext; }

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// TODO: Mesh and Animation data
	
	// Render context for this model
	TestModelContext m_RenderContext;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/	
};
#endif