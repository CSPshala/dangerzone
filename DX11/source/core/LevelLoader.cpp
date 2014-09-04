///////////////////////////////////////////////////////////////////////////
//	File Name	:	"LevelLoader.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Loads components and entities from level xml files
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//  LICENCES
/////////////////////////////////////////////////////////////////////////////////
// PUGIXML is distributed under the MIT License :
// The MIT License (MIT)
// 
// Copyright (c) <year> <copyright holders>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include <iostream>
#include "../components/ComponentFactory.h"
#include "../math/vec3.h"
#include "LevelLoader.h"
#include "WorldManager.h"


////////////////////////////////////////
//				MISC
////////////////////////////////////////


///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
LevelLoader::LevelLoader() : m_currentLevel(-1), m_nextEntityID(0), m_worldMan(nullptr)
{		
}

LevelLoader::~LevelLoader()
{	
}


////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool LevelLoader::Initialize(string filename,WorldManager* worldMan)
{
	bool result = false;

	result = LoadInitialData(filename);
	m_worldMan = worldMan;

	return result;
}

void LevelLoader::Shutdown()
{
	
}

bool LevelLoader::NextLevel()
{
	// Move up our level count
	if(static_cast<unsigned int>(m_currentLevel + 1) > m_levelList.size())
		return false;

	++m_currentLevel;

	// Clear our world manager of current objects
	m_worldMan->CleanupEntities();

	// Load up entities from next level
	if(!LoadLevel(m_levelList[m_currentLevel]))
		return false;
	

	return true;
}

bool LevelLoader::PrevLevel()
{
	return true;
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
bool LevelLoader::LoadInitialData(string filename)
{
	string filePath("resource/data/levels/");
	filePath += filename + ".xml";
	xml_document doc;
	
	if(!LoadXMLFile(doc,filePath))
		return false;

	// Start reading level names and corresponding filenames in
	for( xml_node levelset = doc.child("levelset"); levelset; levelset = levelset.next_sibling("levelset"))
	{
		for( xml_node level = levelset.child("level"); level; level = level.next_sibling("level"))
		{			
			m_levelList.push_back(level.attribute("fileName").as_string());
			m_levelNames.push_back(level.attribute("name").as_string());			
		}
	}


	return true;
}

bool LevelLoader::LoadLevel(std::string filename)
{
	string filePath("resource/data/levels/");
	filePath += filename + ".xml";
	xml_document doc;

	if(!LoadXMLFile(doc,filePath))
		return false;

	bool anythingLoaded = false;

	for(xml_node entityNode = doc.child("entity"); entityNode; entityNode = entityNode.next_sibling("entity"))
	{  
		Entity* entity = nullptr;

		// Get the number of components
		unsigned int componentCount = std::distance(entityNode.children("component").begin(),
			entityNode.children("component").end());

		// Throws on bad allocation and if we pass something wrong to it
		try
		{
			entity = new Entity(m_nextEntityID++,entityNode.attribute("name").as_string(),
				componentCount);
		}
		catch(std::invalid_argument& ia)
		{
			LOG("A new entity could not be allocated. invalid_argument caught: " << ia.what());
			continue;
		}
		catch(std::bad_alloc& ba)
		{
			LOG("A new entity could not be allocated. bad_alloc caught: " << ba.what());
			continue;
		}

		entity->IsActive(entityNode.attribute("active").as_bool());
		entity->SetHP(entityNode.attribute("hp").as_int());
		entity->SetLayer(entityNode.attribute("layer").as_int());

		vec3<float> entityPos(entityNode.attribute("posX").as_float(), 
			entityNode.attribute("posY").as_float(), 0.0f);

		vec3<float> entityVel(entityNode.attribute("velX").as_float(),
			entityNode.attribute("velY").as_float(), 0.0f);

		entity->SetPosition(entityPos);
		entity->SetVelocity(entityVel);			

		for(xml_node componentNode = entityNode.child("component"); componentNode; componentNode = componentNode.next_sibling("component"))
		{
			ComponentAttribute compAt;
			std::string componentName = componentNode.attribute("type").as_string();
						
			if(componentName == "")
			{
				LOG("Tried to load invalid component type on Entity: " << entityNode.attribute("name").as_string() <<
					" Invalid Component Type: " << componentNode.attribute("type").as_string());
				continue;
			}
			
			// Grab all attributes for this component and give to the component factory to construct
			// Iteration is starting at second attribute since first is type and we already have that
			xml_attribute attributeNode = componentNode.first_attribute();
			attributeNode = attributeNode.next_attribute();

			std::vector<xml_attribute> compAttributes;

			for(; attributeNode; attributeNode = attributeNode.next_attribute())
			{
				compAttributes.push_back(attributeNode);
			}

			ComponentFactory::GetInstance().AddComponentToEntity(*entity, componentName, compAttributes);
		}

		m_worldMan->AddEntity(entity);
		anythingLoaded = true;
	}

	if(!anythingLoaded)
	{
		LOG("No valid entities to load in : " << filePath);
		return false;
	}

	return true;
}



////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////
string LevelLoader::GetCurrentLevelName()
{
	if(m_currentLevel > -1 && static_cast<unsigned int>(m_currentLevel) < m_levelNames.size())
		return m_levelNames[m_currentLevel];

	return "invalid_level";
}

string LevelLoader::GetPreviousLevelName()
{
	if(m_currentLevel - 1 > -1 && static_cast<unsigned int>(m_currentLevel) - 1 < m_levelNames.size())
		return m_levelNames[m_currentLevel - 1];

	return "invalid_level";
}

string LevelLoader::GetNextLevelName()
{
	if(m_currentLevel + 1 > -1 && static_cast<unsigned int>(m_currentLevel) + 1 < m_levelNames.size())
		return m_levelNames[m_currentLevel + 1];

	return "invalid_level";
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////