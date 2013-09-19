///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IComponent.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Interface for a component 
///////////////////////////////////////////////////////////////////////////
#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <string>
using namespace std;

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////
class IMessage;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

class IComponent
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	IComponent(const string& componentName, int componentID = -1);
	~IComponent();

	/********** Public Utility Functions ************/
	virtual void Update(float deltaTime) = 0;
	virtual void ReceiveMessage(IMessage* message) = 0;

	/********** Public Accessors ************/	
	virtual int getComponentType() = 0;
	int getComponentID();

	/********** Public Mutators  ************/	
	void setComponentID(int id);

private:
	/********** Private Members ************/
	// String name of the component
	string m_componentName;
	// ID unique to this component's entity
	int	m_componentID;
	
	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif