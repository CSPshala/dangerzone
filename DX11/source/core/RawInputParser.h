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
#include <string>
#include <vector>
#include <queue>
#include "../events/EventSystem.h"
using namespace std;
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
	/** Processess input gathered this frame and pushes it out */
	void ProcessInput();
    /** Re-reads control scheme for input */
    void RestartInput();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	
	    
private:
	/********** Private Members ************/
	static const int INPUTBUFFERSIZE;
	
	RAWINPUTDEVICE* m_rawDevices;
	PRAWINPUT		m_inputBuffer;
	UINT			m_inputBufferCount;
	deque<pair<string,int> >*		m_currentControls;
	vector<string>  m_controlKeys;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	/** Polls keys in control scheme for input and alerts listeners */
    void ReadInput();
	/** Takes care of windows API raw input registration */
    void RegisterForRawInput();
	/** Loads the keywords used for player input */
	void LoadControlKeys();
    /** Reads control .ini for keys to be checking for input */
    void ReadControlConfig();
	/** Handles a single keyboard RAWINPUT structure */
	void HandleKeyboardInput(PRAWINPUT input);
	/** Handles a single mouse RAWINPUT structure */
	void HandleMouseInput(PRAWINPUT input);
	/** Find a control key value */
	int FindKeyValue(string buffer);

};
#endif
