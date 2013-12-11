///////////////////////////////////////////////////////////////////////////
//	File Name	:	"TextureManager.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize loading and storage of textures
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "defines.h"
#include "TextureManager.h"
#include "Texture.h"

////////////////////////////////////////
//				MISC
////////////////////////////////////////
namespace Renderer
{

TextureManager* TextureManager::m_instance(nullptr);
const string TextureManager::DEFAULT_TEXTURE_FILENAME("notexture.png");
///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
TextureManager::TextureManager()
{
	LoadTexture(TextureManager::DEFAULT_TEXTURE_FILENAME);
}

TextureManager::~TextureManager()
{
	CleanupTextures();
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
unsigned int TextureManager::GetTexture(string fileName)
{
	Texture* texture = nullptr;
	map<string,Texture*>::iterator iter = m_textureMap.find(fileName);

	if(iter == m_textureMap.end())
	{
		if(LoadTexture(fileName))
		{
			texture = m_textureMap[fileName];
		}
		else
		{
			//LOG("Couldn't load texture: " << fileName);
			texture = m_textureMap[TextureManager::DEFAULT_TEXTURE_FILENAME];
		}
	}
	else
	{
		texture = m_textureMap[fileName];
	}

	return reinterpret_cast<unsigned int>(texture);
}

TextureManager* TextureManager::GetInstance()
{
	if(m_instance == nullptr)
		m_instance = new TextureManager;

	return m_instance;
}

void TextureManager::DeleteInstance()
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
bool TextureManager::LoadTexture(string fileName)
{
	bool result = false;
	Texture* texture = nullptr;

	// Throws on bad allocation and if we pass something wrong to it
	try
	{
		texture = new Texture;

		if(!texture->Initialize(fileName.c_str()))
		{			
			string message("A new texture could not initialize with fileName: ");
			message += fileName;
			std::invalid_argument ia(message.c_str());
			throw(ia);
		}
		
		m_textureMap[fileName] = texture;

		result = true;
	}	
	catch(std::invalid_argument& ia)
	{
		//LOG("A new texture could not be allocated. invalid_argument caught: " << ia.what());	
	}
	catch(std::bad_alloc& ba)
	{
		//LOG("A new texture could not be allocated. bad_alloc caught: " << ba.what());
		result = false;
	}

	return result;
}

void TextureManager::CleanupTextures()
{
	map<string,Texture*>::iterator iter = m_textureMap.begin();
	for(;iter != m_textureMap.end(); ++iter)
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
}