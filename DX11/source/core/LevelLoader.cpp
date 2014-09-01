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
#include "../components/Entity.h"
#include "../components/PlayerControllerComponent.h"
#include "../components/RenderComponent.h"
#include "../components/RectCollisionComponent.h"
#include "../components/PointCollisionComponent.h"
#include "../components/MouseControllerComponent.h"
#include "../math/vec3.h"
#include "LevelLoader.h"
#include "WorldManager.h"


////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string LevelLoader::VALID_COMPONENTS_FILEPATH("resource/data/componenttypes.xml");

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
LevelLoader::LevelLoader() : m_currentLevel(-1), m_nextEntityID(0), m_nextComponentID(0),
	m_worldMan(nullptr)
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

	// Get valid components
	if(!LoadXMLFile(doc,LevelLoader::VALID_COMPONENTS_FILEPATH))
		return false;

	for(xml_node messages = doc.child("messageTypes").child("message"); messages; messages = messages.next_sibling("message"))
	{
		MessageType toAdd;
		toAdd.name = messages.attribute("name").value();
		toAdd.value = static_cast<COMPONENT_MESSAGE_TYPE>(messages.attribute("value").as_int());
		m_messages.push_back(toAdd);
	}

	for(xml_node component = doc.child("validComponents").child("component"); component; component = component.next_sibling("component"))
	{

		CompPrototype toAdd;
		toAdd.typeName = component.attribute("typeName").value();
		toAdd.type = component.attribute("type").as_int();

		// Add whatever messages are needed
		for(xml_attribute_iterator messages = component.child("messages").attributes_begin(); 
			messages != component.child("messages").attributes_end(); ++messages)
		{
			// Get attribute name and add value
			for(unsigned int i = 0; i < m_messages.size(); ++i)
			{
				if(m_messages[i].name == messages->value())
				{
					toAdd.localMsgTypes.push_back(m_messages[i].value);
				}
			}
		}

		m_validComponents.push_back(toAdd);	
	}


	return true;
}

bool LevelLoader::LoadXMLFile(xml_document& doc,const string& filePath) const
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

		vec3<float> entityPos(entityNode.attribute("posX").as_float(), 
			entityNode.attribute("posY").as_float(), 0.0f);

		vec3<float> entityVel(entityNode.attribute("velX").as_float(),
			entityNode.attribute("velY").as_float(), 0.0f);

		entity->SetPosition(entityPos);
		entity->SetVelocity(entityVel);

		for(xml_node componentNode = entityNode.child("component"); componentNode; componentNode = componentNode.next_sibling("component"))
		{
			IComponent* component = FindAndCreateComponentType(componentNode.attribute("type").as_string());
			if(!component)
			{
				LOG("Tried to load invalid component type on Entity: " << entityNode.attribute("name").as_string() <<
					" Invalid Component Type: " << componentNode.attribute("type").as_string());
				continue;
			}

			component->setParentEntity(entity);

			// Set component's default registered local messages
			for(unsigned int i = 0; i < m_validComponents.size(); ++i)
			{
				if(m_validComponents[i].type == component->getComponentType())
				{
					component->setLocalMessagesToReceieve(m_validComponents[i].localMsgTypes);
				}
			}

			if(!component->LoadComponentAttributes(componentNode))
			{
				LOG("Component couldn't load attributes for Entity: " << entityNode.attribute("name").as_string() <<
					" Component Type: " << componentNode.attribute("type").as_string());

				delete component;
				continue;
			}

			// Register the component for it's system messages (if any)
			component->RegisterForMessages();
			
			entity->AttachComponent(component);
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

IComponent*	LevelLoader::FindAndCreateComponentType(const string type)
{
	IComponent* component = nullptr;

	// Validate component type then allocate
	const int num = m_validComponents.size();
	const CompPrototype* ptr = (num != 0) ? &m_validComponents.front() : NULL;
	for(int i = 0; i < num; i++)
	{
		if(m_validComponents[i].typeName == type)
		{
			component = CreateComponentType(m_validComponents[i].type);
			break;
		}
	}

	return component;
}

IComponent*	LevelLoader::CreateComponentType(const int type)
{
	IComponent* component = nullptr;

	switch(type)
	{
	case ENUMS::PLAYER_CONTROLLER:
		{
			try
			{
				component = new PlayerControllerComponent(ENUMS::PLAYER_CONTROLLER,m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new player controller component could not be allocated. invalid_argument caught: " << ia.what());			
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new player controller component could not be allocated. bad_alloc caught: " << ba.what());				
			}
		}
		break;
	case ENUMS::RENDERING:
		{
			try
			{
				component = new RenderComponent(ENUMS::RENDERING,m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new render component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new render component be allocated. bad_alloc caught: " << ba.what());		
			}
		}
		break;
	case ENUMS::RECT_COLLISION:
        {
            try
			{
				component = new RectCollisionComponent(
					ENUMS::RECT_COLLISION, m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new collision component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new collision component could not be allocated. bad_alloc caught: " << ba.what());		
			}
        }
        break;
    case ENUMS::POINT_COLLISION:
        {
            try
			{
				component = new PointCollisionComponent(
					ENUMS::POINT_COLLISION, m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new collision component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new collision component could not be allocated. bad_alloc caught: " << ba.what());		
			}
        }
        break;
	case ENUMS::MOUSE_CONTROLLER:
		{
			try
			{
				component = new MouseControllerComponent(ENUMS::MOUSE_CONTROLLER,m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new mouse controller component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new mouse controller component could not be allocated. bad_alloc caught: " << ba.what());		
			}
		}
		break;
	}

	return component;
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

int LevelLoader::GetComponentValue(string componentName)
{
	// Fast vector iteration and access
	int retVal = -1;
	const int num = m_validComponents.size();
	const CompPrototype* ptr = (num != 0) ? &m_validComponents.front() : NULL;
	for(int i = 0; i < num; i++)
	{
		if(m_validComponents[i].typeName == componentName)
		{
			retVal = m_validComponents[i].type;
			break;
		}
	}

	return retVal;
}

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////