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

	/********** Public Utility Functions ************/
	void AddComponentToEntity(Entity& entity, ENUMS::COMPONENTS componentType);
	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// Class is entirely static right now, we don't want ANY instantiation
	ComponentFactory();
	~ComponentFactory();
	ComponentFactory(const ComponentFactory&);
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif