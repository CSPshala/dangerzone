///////////////////////////////////////////////////////////////////////////
//	File Name	:	"XbInputParser.h"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Manage xbox controller input event sending and parsing
///////////////////////////////////////////////////////////////////////////
#ifndef _XBINPUTPARSER_H
#define _XBINPUTPARSER_H

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "XboxController.h"
#include <vector>
#include <string>
using namespace std;
////////////////////////////////////////
//		   FORWARD DECLARATIONS
////////////////////////////////////////


////////////////////////////////////////
//				MISC
////////////////////////////////////////


class XbInputParser
{
public:
	/********** Construct / Deconstruct / OP Overloads ************/
	XbInputParser();
	~XbInputParser();

	/********** Public Utility Functions ************/
	void ReadInput();
	void ProcessInput();

	/********** Public Accessors ************/

	/********** Public Mutators  ************/	

private:
	/********** Private Members ************/
	// Current controls mapped for each player
	vector<vector<pair<bool,pair<int,int> > >*> m_currentControls;
	vector<pair<XINPUT_STATE,int> > m_currentFrameData;
	vector<int> m_oldPacketNumbers;
	vector<XboxController*> m_controllers;
	vector<pair<string,int> > m_controlStrings;

	/********** Private Accessors ************/

	/********** Private Mutators ************/

	/********** Private Utility Functions ************/
	void LoadControls();
};
#endif