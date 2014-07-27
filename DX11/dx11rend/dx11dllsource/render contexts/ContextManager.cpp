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
#include "../defines.h"
#include "ContextManager.h"
#include "IRenderContext.h"
#include "DiffuseContext.h"
#include "OutlineBoxContext.h"

using namespace pugi;
////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

ContextManager* ContextManager::m_instance(nullptr);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
ContextManager::ContextManager()
{	
}

ContextManager::~ContextManager()
{
	CleanupContexts();
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool ContextManager::Initialize(HWND hWnd)
{
	if(LoadContexts(hWnd))	
		return true;	
	else	
		LOG("ContextManager Initialize failed...");
	

	return false;
}

void ContextManager::PrepareContexts(LayerQueue& renderQueue)
{
	while(renderQueue.size() > 0)
	{
		GetRenderContext(renderQueue.top()->getShader())->PrepareBuffers(renderQueue);
	}

	for(unsigned int i = 0; i < m_contextArray.size(); ++i)
	{
		m_contextArray[i]->UpdateBuffers();
	}
}

void ContextManager::RenderContexts()
{
	// Render until all layers have been rendered in every context
	// w/o this counter this would be infinite CAUSE I WANT ALL THE LAYYERRRRSSS
	unsigned int contextsDone(0);
	unsigned int arraySize = m_contextArray.size();

	for(unsigned int layer = 0; contextsDone < arraySize; ++layer)
	{
		// Now render this layer per context (if applicable)
		for(unsigned int i = 0; i < arraySize; ++i)
		{
			if(m_contextArray[i]->AreLayersToRender())
			{
				m_contextArray[i]->RenderBuffers(layer);
			}
			else
			{
				contextsDone++;
			}				
		}


	}
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
bool ContextManager::LoadContexts(HWND hWnd)
{
	xml_document doc;
	string filePath("resource/data/shadertypes.xml");
	
	if(!LoadXMLFile(doc,filePath))
		return false;

	try
	{

		for(xml_node shader = doc.child("validShaders").child("shader"); shader; shader = shader.next_sibling("shader"))
		{
			string contextName = shader.attribute("typeName").as_string();
			if(contextName == "diffuse")
			{
				m_contextArray.push_back(new DiffuseContext);
				m_contextArray.back()->Initialize(hWnd);
			}
			else if(contextName == "outlineBox")
			{
				m_contextArray.push_back(new OutlineBoxContext);
				m_contextArray.back()->Initialize(hWnd);
			}
		}

	}
	catch(...)
	{
		LOG("Unexpected exception caught in ContextManager::LoadContexts...");
		return false;
	}

	return true;
}

IRenderContext* ContextManager::GetRenderContext(unsigned int contextIndex)
{
	return m_contextArray[contextIndex];
}

bool ContextManager::LoadXMLFile(xml_document& doc,const string& filePath) const
{
	xml_parse_result result = doc.load_file(filePath.c_str());

	bool returnResult = false;

	if (result)
	{
		LOG("XML [" << filePath << "] parsed without errors\n");
		returnResult = true;
	}
	else
	{
		LOG("XML [" << filePath << "] parsed with errors\n");
		LOG("Error description: " << result.description() << "\n");
		LOG("Error offset: " << result.offset << "\n");
		returnResult = false;
	}

	return returnResult;
}

void ContextManager::CleanupContexts()
{
	vector<IRenderContext*>::iterator iter = m_contextArray.begin();
	for(;iter != m_contextArray.end(); ++iter)
	{
		(*iter)->Shutdown();
		delete (*iter);
	}
}

}
////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////