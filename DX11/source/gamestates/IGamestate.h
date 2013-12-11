///////////////////////////////////////////////////////////////////////////
//	File Name	:	"IGamestate.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Gamestate interface to be inherited
///////////////////////////////////////////////////////////////////////////
#ifndef _IGAMESTATE_H
#define _IGAMESTATE_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class IGamestate
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/


	/********** Public Utility Functions ************/
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float deltaTime) = 0;

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

};
#endif