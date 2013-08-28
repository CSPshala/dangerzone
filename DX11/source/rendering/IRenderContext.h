///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IRenderContext.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for render contexts
///////////////////////////////////////////////////////////////////////////
#ifndef _IRENDERCONTEXT_H
#define _IRENDERCONTEXT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <d3d11.h>
#include <d3dx10math.h>
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IRenderContext
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/
	virtual bool Initialize() = 0;	
	virtual void Shutdown() = 0;		
	virtual void RenderBuffers() = 0;
	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	virtual bool InitializeBuffers() = 0;
	virtual void ShutdownBuffers() = 0;
};
#endif  