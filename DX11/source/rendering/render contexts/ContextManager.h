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
#include <map>
using namespace std;
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
	/** Returns a render context corresponding to passed in context name
	  NOTE: Will return nullptr if context not found **/
	IRenderContext* GetRenderContext(string contextName);

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
	map<string,IRenderContext*> m_contextMap;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void CleanupContexts();
};
#endif