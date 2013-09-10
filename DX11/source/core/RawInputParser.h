///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RawInputParser.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles raw input and sends it out as input events for controller independence
///////////////////////////////////////////////////////////////////////////
#ifndef _RAWINPUTPARSER_H
#define _RAWINPUTPARSER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../events/EventSystem.h"

////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////

////////////////////////////////////////
//				MISC
////////////////////////////////////////


class RawInputParser
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
    RawInputParser();
    ~RawInputParser();

	/********** Public Utility Functions ************/

    /** Takes care of windows API raw input registration */
    void RegisterForRawInput();
    /** Polls keys in control scheme for input and alerts listeners */
    void ReadAndSendInput();
    /** Re-reads control scheme for input */
    void RestartInput();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
    
    /** Reads control .ini for keys to be checking for input */
    void ReadControls();

};
#endif
