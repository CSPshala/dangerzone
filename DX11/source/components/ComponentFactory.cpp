///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ComponentFactory.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Allows creation of requested components and the ability add them to existing entities
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "ComponentFactory.h"
#include "../components/PlayerControllerComponent.h"
#include "../components/DiffuseRenderComponent.h"
#include "../components/RectCollisionComponent.h"
#include "../components/PointCollisionComponent.h"
#include "../components/MouseControllerComponent.h"
#include "../components/OutlineBoxRenderComponent.h"
#include "../xml/pugixml.hpp"
using namespace pugi;

////////////////////////////////////////
//				MISC
////////////////////////////////////////
const string ComponentFactory::VALID_COMPONENTS_FILEPATH("resource/data/componenttypes.xml");
ComponentFactory* ComponentFactory::m_instance(nullptr);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
ComponentFactory& ComponentFactory::GetInstance()
{
	if(m_instance == nullptr)
	{
		m_instance = new ComponentFactory;
		if(m_instance->Initialize() == false)
		{
			LOG("Couldn't initialize an instance of ComponentFactory, undefined behavior/crash INC...");
		}		
	}

	return *m_instance;
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////

//TODO: Fix code dupe here.  Just don't care enough right now.
void ComponentFactory::AddComponentToEntity(Entity* entity, const ENUMS::COMPONENTS componentType, 
		const std::vector<ComponentAttribute>* compAttributes)
{
	// Create the component type by type
	IComponent* component = CreateComponentType(componentType);

	component->setParentEntity(entity);

	SetDefaultLocalMessages(component);

	if(compAttributes != nullptr && compAttributes->size() > 0)
	{
		AddAttributesToComponent(component, compAttributes);
	}
	// Register component for any system messages it may have
	component->RegisterForMessages();

	entity->AttachComponent(component);
}

void ComponentFactory::AddComponentToEntity(Entity* entity, const std::string name, 
		const std::vector<xml_attribute>* compAttributes)
{
	// Create the component type by name
	IComponent* component = FindAndCreateComponentType(name);

	component->setParentEntity(entity);

	SetDefaultLocalMessages(component);

	if(compAttributes != nullptr && compAttributes->size() > 0)
	{
		std::vector<ComponentAttribute> internalAttributes;

		// Convert XML strings to actual types and add to a vector to add
		for(unsigned int i = 0; i < compAttributes->size(); ++i)
		{
			ComponentAttribute comp(ConvertXmlAttributeToInternal((*compAttributes)[i]));
			internalAttributes.push_back(comp);
		}


		AddAttributesToComponent(component, &internalAttributes);
	}

	// Register component for any system messages it may have
	component->RegisterForMessages();

	entity->AttachComponent(component);
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
ComponentFactory::ComponentFactory() : m_nextComponentID(0)
{
}

bool ComponentFactory::Initialize()
{
	// The valid components file
	xml_document doc;

	// Get valid components
	if(!LoadXMLFile(doc,ComponentFactory::VALID_COMPONENTS_FILEPATH))
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

	// Get all existing attribute types
	for(xml_node attribute = doc.child("attributeTypes").child("attribute"); attribute; attribute = attribute.next_sibling("attribute"))
	{
		std::string name(attribute.attribute("name").as_string());
		std::string type(attribute.attribute("type").as_string());

		m_attributeTypes.insert(std::make_pair(name, type));
	}

	return true;
}

void ComponentFactory::SetDefaultLocalMessages(IComponent* comp)
{
	// Set component's default registered local messages
	for(unsigned int i = 0; i < m_validComponents.size(); ++i)
	{
		if(m_validComponents[i].type == comp->getComponentType())
		{
			comp->setLocalMessagesToReceieve(m_validComponents[i].localMsgTypes);
		}
	}
}

void ComponentFactory::AddAttributesToComponent(IComponent* comp, 
												const std::vector<ComponentAttribute>* compAttributes)
{
	for(unsigned int i = 0; i < compAttributes->size(); ++i)
	{
		comp->AddAttributeAndValue(&((*compAttributes)[i]));
	}
}

IComponent*	ComponentFactory::FindAndCreateComponentType(const std::string type)
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

ComponentAttribute ComponentFactory::ConvertXmlAttributeToInternal(const xml_attribute& attribAuto)
{
	ComponentAttribute attr;
	attr.name = std::string(attribAuto.name());

	std::string type;

	type = m_attributeTypes[attr.name];

	if(type == "int")
	{
		attr.valueI = attribAuto.as_int();
	}
	else if(type == "string")
	{
		attr.valueString = attribAuto.as_string();
	}
	else if(type == "bool")
	{
		attr.valueB = attribAuto.as_bool();
	}
	else if(type == "float")
	{
		attr.valueF = attribAuto.as_float();
	}
	else
	{
		LOG("An undefined type was contained in an XML file, expect undefined behavior...");
	}

	return attr;
}

IComponent*	ComponentFactory::CreateComponentType(const int type)
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
	case ENUMS::DIFFUSE_RENDER:
		{
			try
			{
				component = new DiffuseRenderComponent(ENUMS::DIFFUSE_RENDER,m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new diffuse render component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new diffuse render component be allocated. bad_alloc caught: " << ba.what());		
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
	case ENUMS::OUTLINEBOX_RENDER:
		{
			try
			{
				component = new OutlineBoxRenderComponent(ENUMS::OUTLINEBOX_RENDER,m_nextComponentID++);
			}
			catch(std::invalid_argument& ia)
			{				
				LOG("A new diffuse render component could not be allocated. invalid_argument caught: " << ia.what());		
			}
			catch(std::bad_alloc& ba)
			{				
				LOG("A new diffuse render component be allocated. bad_alloc caught: " << ba.what());		
			}
		}
		break;
	default:
		{
			LOG("An unrecognized Component was requested in ComponentFactory");
		}
		break;
	}

	return component;
}

int ComponentFactory::GetComponentValue(std::string componentName)
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
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////




