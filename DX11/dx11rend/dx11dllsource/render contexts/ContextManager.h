///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ContextManager.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize creation and storage of render contexts
///////////////////////////////////////////////////////////////////////////
#ifndef _CONTEXTMANAGER_H
#define _CONTEXTMANAGER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <string>
#include <vector>
#include "../xml/pugixml.hpp"
#include "../defines.h"

using namespace pugi;
using namespace std;

namespace Renderer
{
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IRenderContext;
////////////////////////////////////////
//				MISC
////////////////////////////////////////



class ContextManager
{
public:	
	/********** Public Utility Functions ************/
	static ContextManager* GetInstance();
	static void DeleteInstance();
	void PrepareContexts(LayerQueue& renderQueue);
	void RenderContexts();

	/** Inits the context manager */
	bool Initialize(HWND hWnd);

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	ContextManager();
	~ContextManager();
	ContextManager(const ContextManager&);
	ContextManager& operator=(const ContextManager&);

	/********** Private Members ************/
	// Singleton Instance
	static ContextManager* m_instance;
	// map of contexts
	vector<IRenderContext*> m_contextArray;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool LoadContexts(HWND hWnd);
	bool LoadXMLFile(xml_document& doc,const string& filePath) const;
	/** Returns a render context corresponding to passed in context name
	  NOTE: Will return nullptr if context not found **/
	IRenderContext* GetRenderContext(unsigned int contextIndex);
	void CleanupContexts();
};

}
#endif