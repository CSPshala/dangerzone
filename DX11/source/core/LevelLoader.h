///////////////////////////////////////////////////////////////////////////
//	File Name	:	"LevelLoader.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Loads components and entities from level xml files
///////////////////////////////////////////////////////////////////////////
#ifndef _LEVELLOADER_H
#define _LEVELLOADER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../messaging/CMessages.h"
#include <string>
#include <vector>
#include "../xml/pugixml.hpp"
using namespace std;
using namespace pugi;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class WorldManager;
////////////////////////////////////////
//				MISC
////////////////////////////////////////


class LevelLoader
{
public:	
	/********** Construct / Deconstruct / OP Overloads ************/
	LevelLoader();
	~LevelLoader();

	/********** Public Utility Functions ************/
	bool Initialize(string filename,WorldManager* worldMan);	
	void Shutdown();

	bool NextLevel();
	bool PrevLevel();
		
	/********** Public Accessors ************/
	string GetCurrentLevelName();
	string GetPreviousLevelName();
	string GetNextLevelName();
	/** Get the component value of a string type 
		Returns -1 if not found */
	int	   GetComponentValue(string componentName);

	/********** Public Mutators  ************/	

private:	
	/********** Private Members ************/
	static const string VALID_COMPONENTS_FILEPATH;

	struct CompPrototype
	{
		int		type;
		string	typeName;
		vector<COMPONENT_MESSAGE_TYPE> localMsgTypes;
	};

	struct MessageType
	{
		COMPONENT_MESSAGE_TYPE value;
		string name;
	};

	// List of levels to load
	vector<string> m_levelList;
	vector<string> m_levelNames;
	vector<MessageType>  m_messages;
	vector<CompPrototype> m_validComponents;
	// Currently loaded level
	int m_currentLevel;
	// Unique Entity and component IDs for this world and level loader
	int m_nextEntityID;
	int m_nextComponentID;
	// Pointer to our world manager
	WorldManager* m_worldMan;
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool LoadInitialData(std::string filename);
	bool LoadXMLFile(xml_document& doc,const string& filePath) const;
	bool LoadLevel(std::string filename);	
	IComponent* FindAndCreateComponentType(const string type);
	IComponent* CreateComponentType(const int type);

};
#endif