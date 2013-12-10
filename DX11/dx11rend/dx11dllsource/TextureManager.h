///////////////////////////////////////////////////////////////////////////
//	File Name	:	"TextureManager.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Organize loading and storage of textures
///////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <string>
#include <map>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class Texture;

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class TextureManager
{
public:
	/********** Public Utility Functions ************/
	static TextureManager* GetInstance();
	static void DeleteInstance();
	/** Returns a texture corresponding to the passed filename 
	  NOTE: Will load passed texture by filename if not previously loaded
	  NOTE: Will return a default texture if loading fails
      NOTE: returns a uint, which is just the reinterpret cast of that texture's pointer 
    **/
	unsigned int GetTexture(string fileName);

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Construct / Deconstruct / OP Overloads ************/
	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	/********** Private Members ************/
	// No texture filename
	static const string DEFAULT_TEXTURE_FILENAME;
	// Singleton Instance
	static TextureManager* m_instance;
	// map of textures
	map<string,Texture*> m_textureMap;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool LoadTexture(string fileName);
	void CleanupTextures();

};
#endif