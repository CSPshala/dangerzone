///////////////////////////////////////////////////////////////////////////
//	File Name	:	"ComponentFactory.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Allows creation of requested components and the ability add them to existing entities
///////////////////////////////////////////////////////////////////////////
#ifndef _COMPONENTFACTORY_H
#define _COMPONENTFACTORY_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "Entity.h"
#include <map>

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////

class ComponentFactory
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	static ComponentFactory& GetInstance();

	/********** Public Structs *************/
	

	/********** Public Utility Functions ************/

	// Adds a component of type to the passed entity with attributes listed (if valid)
	// Used when manually adding components where types are known (usually some component adding to another entity)
	void AddComponentToEntity(Entity* entity, const ENUMS::COMPONENTS componentType, 
		const std::vector<ComponentAttribute>* compAttributes = nullptr);

	// Adds a component of name to the passed entity with the attributes listed (if valid)
	// Used for loading from XML files
	// Is slower than Non-XML variant so don't use unless you need to
	void AddComponentToEntity(Entity* entity, const std::string name, 
		const std::vector<xml_attribute>* compAttributes = nullptr);

	void RemoveComponentFromEntity(Entity* entity, ENUMS::COMPONENTS componentType);

	/********** Public Accessors ************/

	/********** Public Mutators  ************/

private:
	/********** Private Members ************/
	static const string VALID_COMPONENTS_FILEPATH;

	static ComponentFactory* m_instance;

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

	vector<MessageType>  m_messages;
	vector<CompPrototype> m_validComponents;
	map<std::string,std::string> m_attributeTypes;
	int m_nextComponentID;

	// Class is entirely static right now, we don't want ANY instantiation
	ComponentFactory();
	~ComponentFactory();
	ComponentFactory(const ComponentFactory&);
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	bool Initialize();

	IComponent*	FindAndCreateComponentType(const std::string type);
	IComponent*	CreateComponentType(const int type);
	void AddAttributesToComponent(IComponent* comp, const std::vector<ComponentAttribute>* compAttributes);
	void SetDefaultLocalMessages(IComponent* comp);
	int GetComponentValue(string componentName);
	ComponentAttribute ConvertXmlAttributeToInternal(const xml_attribute& attribAuto);	
};
#endif