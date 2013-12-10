///////////////////////////////////////////////////////////////////////////
//	File Name	:	"dx11rendexp.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Provide DLL interface for DX11 renderer
///////////////////////////////////////////////////////////////////////////
#ifndef _DX11RENDEXP_H
#define _DX11RENDEXP_H

////////////////////////////////////////
//		 DLL INTERFACE DEFINES
////////////////////////////////////////
#ifdef DX11REND_EXPORTS
#define RENDER_API __declspec(dllexport)
#define RENDER_API_EXTERN extern "C" __declspec(dllexport)
#else
#define RENDER_API __declspec(dllimport)
#define RENDER_API_EXTERN extern "C" __declspec(dllimport)
#endif
////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class RENDER_API Renderer
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/

	/********** Public Utility Functions ************/

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif