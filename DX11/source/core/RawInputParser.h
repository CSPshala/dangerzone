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
#include "../events/InputEventSystem.h"
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
	/** Polls keys in control scheme for input and alerts listeners */
    void ReadInput(LPARAM lParam);
	/** Takes care of windows API raw input registration */
    void RegisterForRawInput();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	
	    
private:
	/********** Private Members ************/
	static const int NUM_RAW_DEVICES;

	RAWINPUTDEVICE* m_rawDevices;
	LPBYTE		    m_inputBuffer[40];
	bool			m_receivedInput;
	deque<pair<int,pair<int,bool> > >*		m_currentControls;
	vector<string>  m_controlKeys;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

	/** Loads the keywords used for player input */
	void LoadControlKeys();
    /** Reads control .ini for keys to be checking for input */
    void ReadControlConfig();
	/** Handles a single keyboard RAWINPUT structure */
	void HandleKeyboardInput(PRAWINPUT input);
	/** Handles a single mouse RAWINPUT structure */
	void HandleMouseInput(PRAWINPUT input);
	/** Find a control key value */
	pair<int,pair<int,bool> > FindKeyAndEventValue(string command, string key);

};
#endif
