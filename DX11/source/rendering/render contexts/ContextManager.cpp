///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ContextManager.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize creation and storage of render contexts
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../../Globals.h"
#include "ContextManager.h"
#include "IRenderContext.h"
#include "DiffuseContext.h"
////////////////////////////////////////
//				MISC
////////////////////////////////////////
ContextManager* ContextManager::m_instance(nullptr);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
ContextManager::ContextManager()
{
	IRenderContext* toAdd = new DiffuseContext;
	toAdd->Initialize("paperbowser.png",64,64);
	m_contextMap["diffuse"] = toAdd;
}

ContextManager::~ContextManager()
{
	CleanupContexts();
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
IRenderContext* ContextManager::GetRenderContext(string contextName)
{
	IRenderContext* context = nullptr;

	map<string,IRenderContext*>::iterator iter = m_contextMap.find(contextName);

	if(iter == m_contextMap.end())
	{
		LOG("Couldn't load context with name: " << contextName);
	}
	else
	{
		context = m_contextMap[contextName];
	}

	return context;
}

ContextManager* ContextManager::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new ContextManager;

	return m_instance;
}

void ContextManager::DeleteInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void ContextManager::CleanupContexts()
{
	map<string,IRenderContext*>::iterator iter = m_contextMap.begin();
	for(;iter != m_contextMap.end(); ++iter)
	{
		(*iter).second->Shutdown();
		delete (*iter).second;
	}
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////