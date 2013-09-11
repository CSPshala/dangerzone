///////////////////////////////////////////////////////////////////////////
//	File Name	:	"RawInputParser.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Handles raw input and sends it out as input events for controller independence
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include <Windows.h>
#include <fstream>
#include "RawInputParser.h"

using namespace std;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

// Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx#standard_read
// Mouse: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645578(v=vs.85).aspx
// Keyboard: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645575(v=vs.85).aspx

// Wild guess at the size of the largest array of input I'd need
const int RawInputParser::INPUTBUFFERSIZE(200);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RawInputParser::RawInputParser() : m_rawDevices(nullptr), m_inputBuffer(nullptr), m_inputBufferCount(0),
	m_currentControls(nullptr)
{
	// Allocate for keyboard and mouse only for now
	m_rawDevices = new RAWINPUTDEVICE[2];
	// Mouse = 40 byte input structure size, Keyboard = 32 
	// creating 40 as largest size for a buffer to be safe
	m_inputBuffer = new RAWINPUT[INPUTBUFFERSIZE];

	// Derp
	LoadControlKeys();
    // Load our control scheme
    ReadControlConfig();
	// Register for raw
	RegisterForRawInput();
}

RawInputParser::~RawInputParser()
{
	if(m_rawDevices)
	{
		delete[] m_rawDevices;
		m_rawDevices = nullptr;
	}

	if(m_inputBuffer)
	{
		delete[] m_inputBuffer;
		m_inputBuffer = nullptr;
	}
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void RawInputParser::RegisterForRawInput()
{        
    m_rawDevices[0].usUsagePage = 0x01; 
    m_rawDevices[0].usUsage = 0x02; 
    m_rawDevices[0].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
    m_rawDevices[0].hwndTarget = 0;

    m_rawDevices[1].usUsagePage = 0x01; 
    m_rawDevices[1].usUsage = 0x06; 
    m_rawDevices[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
    m_rawDevices[1].hwndTarget = 0;

	if (RegisterRawInputDevices(m_rawDevices, 2, sizeof(m_rawDevices[0])) == FALSE) {
        //registration failed. Call GetLastError for the cause of the error
        OutputDebugString (TEXT("Registration of raw input keyboard/mouse failed!\n"));
    }
}

void RawInputParser::ReadInput()
{
    UINT dwSize;	

	GetRawInputBuffer(NULL, &dwSize, sizeof(RAWINPUTHEADER));
    
	if (dwSize > INPUTBUFFERSIZE * sizeof(RAWINPUT) ) 
    {
		OutputDebugString (TEXT("GetRawInputData returned size too small for input buffer.\n"));
        return;
    } 

	m_inputBufferCount = GetRawInputBuffer(m_inputBuffer,&dwSize,sizeof(RAWINPUTHEADER));

	if(m_inputBufferCount == -1)
         OutputDebugString (TEXT("GetRawInputData does not return correct size !\n")); 
		
}

void RawInputParser::ProcessInput()
{
	ReadInput();

	// No input to process
	if(m_inputBufferCount == -1)
		return;
	
	// Pointer to current data
	PRAWINPUT current = m_inputBuffer;
	for(unsigned int i = 0; i < m_inputBufferCount; ++i)
	{
		if(current->header.dwType == RIM_TYPEKEYBOARD) 
		{        
			// DO stuff
			HandleKeyboardInput(current);
		}
		else if(current->header.dwType == RIM_TYPEMOUSE) 
		{
			//DO stuff
			HandleMouseInput(current);
		}   

		current = NEXTRAWINPUTBLOCK(current);
	}
	
}

void RawInputParser::RestartInput()
{
	// Reload and re-read config file
	ReadControlConfig();
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void RawInputParser::LoadControlKeys()
{
	// Load in control key vector
	fstream keyFile(L"resource/data/controlstrings.txt",ios::in);

	if(!keyFile.is_open())
		return;

	// Rando number for char, 30 > more than we'll need
	char keyBuff[30];

	// Line by line
	while(!keyFile.eof())
	{
		keyFile.getline(keyBuff,30);
		
		//Paranoid check
		if(keyFile.eof())
			break;

		m_controlKeys.push_back(string(keyBuff));

	}

	keyFile.close();
}

void RawInputParser::ReadControlConfig()
{
	if(m_currentControls)
	{
		delete m_currentControls;
		m_currentControls = nullptr;
	}

	if(m_currentControls == nullptr)
	{
		m_currentControls = new deque<pair<string,int> >;
	}

	// Load in control key vector
	fstream configFile(L"resource/config/user.cfg",ios::in);

	if(!configFile.is_open())
		return;

	// Rando number for char, 30 > more than we'll need
	char keyBuff[30];

	// Line by line
	while(!configFile.eof())
	{
		configFile.get(keyBuff,30,':');
		configFile.get(keyBuff,30);

		//Paranoid check
		if(configFile.eof())
			break;
		
		char* context = nullptr;
		char* tokPos = strtok_s(&keyBuff[1]," ",&context);
		string command(tokPos);
		string key(context);		

		int keyCode = FindKeyValue(key);
		m_currentControls->push_back(pair<string,int>(command,keyCode));
	}

	configFile.close();
}

void RawInputParser::HandleKeyboardInput(PRAWINPUT input)
{

}

void RawInputParser::HandleMouseInput(PRAWINPUT input)
{
}

int RawInputParser::FindKeyValue(string buffer)
{
	for(unsigned int i = 0; i < m_controlKeys.size(); ++i)
	{
		if(buffer == m_controlKeys[i])
			return i + 1;
	}

	return -1;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
