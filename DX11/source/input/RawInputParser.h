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
#include "../xml/pugixml.hpp"
using namespace std;
using namespace pugi;
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
	/** Initializes the parser */
	bool Initialize();
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
	static const int NUM_MOUSE_BUTTONS;

	RAWINPUTDEVICE* m_rawDevices;
	queue<RAWINPUT> m_inputQueue;
	//RAWINPUT		m_inputBuffer;
	bool			m_receivedInput;
	// Holds current controls for keyboard 
	// pair<event number, pair<keycode, buffer status> >
	deque<pair<int,pair<int,bool> > >*		m_currentKeyboardControls;
	// Holds current controls for mouse, data is same as keyboard control deque
	deque<pair<int,pair<int,bool> > >*      m_currentMouseControls;
	vector<bool> m_mouseButtonStatus;

	// Holds pairs of key names and their keycode values of valid keys
	vector<pair<string, int> >  m_controlKeys;
	// Holds pairs of key names and their values for mice
	vector<pair<string, int> > m_mouseControlKeys;
	// Keeps track of mouse delta this frame
	int mMouseDeltaX, mMouseDeltaY;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/

	/** Loads the keywords used for player input */
	bool LoadControlKeys();
    /** Reads control .ini for keys to be checking for input */
    bool ReadControlConfig();
	/** Handles a single keyboard RAWINPUT structure */
	void HandleKeyboardInput(PRAWINPUT input);
	/** Handles a single mouse RAWINPUT structure */
	void HandleMouseInput(PRAWINPUT input);
	/** Find a control key value */
	pair<int,pair<int,bool> > FindKeyAndEventValue(string command, string key);
	/** Find a control key value (for mouse) */
	pair<int,pair<int,bool> > FindKeyAndEventValueMouse(string command, string key);
	// Checks if an XML file properly opened
	bool LoadXMLFile(xml_document& doc,const string& filePath) const;
};
#endif
