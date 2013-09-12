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

const int RawInputParser::NUM_RAW_DEVICES(1);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RawInputParser::RawInputParser() : m_rawDevices(nullptr), m_currentControls(nullptr)
{
	// Allocate for keyboard and mouse only for now
	m_rawDevices = new RAWINPUTDEVICE[NUM_RAW_DEVICES];

	// Derp
	LoadControlKeys();
    // Load our control scheme
    ReadControlConfig();
}

RawInputParser::~RawInputParser()
{
	if(m_rawDevices)
	{
		delete[] m_rawDevices;
		m_rawDevices = nullptr;
	}
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void RawInputParser::RegisterForRawInput()
{        
 //   m_rawDevices[0].usUsagePage = 0x01; 
 //   m_rawDevices[0].usUsage = 0x02; 
	//m_rawDevices[0].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
 //   m_rawDevices[0].hwndTarget = 0;

    m_rawDevices[0].usUsagePage = 0x01; 
    m_rawDevices[0].usUsage = 0x06; 
    m_rawDevices[0].dwFlags = RIDEV_NOLEGACY | RIDEV_APPKEYS;   // adds HID keyboard and also ignores legacy keyboard messages
    m_rawDevices[0].hwndTarget = 0;

	if (RegisterRawInputDevices(m_rawDevices, NUM_RAW_DEVICES, sizeof(m_rawDevices[0])) == FALSE) {
        //registration failed. Call GetLastError for the cause of the error
        OutputDebugString (TEXT("Registration of raw input keyboard/mouse failed!\n"));
    }
}

void RawInputParser::ReadInput(LPARAM lParam)
{
    UINT dwSize = 40;

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &m_inputBuffer, &dwSize, sizeof(RAWINPUTHEADER));		
}

void RawInputParser::ProcessInput()
{
	// Pointer to current data
	RAWINPUT* current = (RAWINPUT*)m_inputBuffer;

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
		m_currentControls = new deque<pair<int,int> >;
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

		m_currentControls->push_back(FindKeyAndEventValue(command,key));		
	}

	configFile.close();
}

void RawInputParser::HandleKeyboardInput(PRAWINPUT input)
{
	deque<pair<int,int> >::iterator iter = m_currentControls->begin();
	while(iter != m_currentControls->end())
	{
		if(input->data.keyboard.VKey == (*iter).second)			
			EventSystem::GetInstance()->SendEvent((*iter).first); //Send this key's event

		++iter;
	}
}

void RawInputParser::HandleMouseInput(PRAWINPUT input)
{
}

pair<int,int> RawInputParser::FindKeyAndEventValue(string command, string key)
{
	pair<int,int> eventAndKey;

	// Event code
	if(command == "up")
		eventAndKey.first = static_cast<int>(EventSystem::UP);
	else if(command == "down")
		eventAndKey.first = static_cast<int>(EventSystem::DOWN);
	else if(command == "left")
		eventAndKey.first = static_cast<int>(EventSystem::LEFT);
	else if(command == "right")
		eventAndKey.first = static_cast<int>(EventSystem::RIGHT);
	else if(command == "jump")
		eventAndKey.first = static_cast<int>(EventSystem::JUMP);
	else if(command == "attack")
		eventAndKey.first = static_cast<int>(EventSystem::ATTACK);


	// Keycode for command
	for(unsigned int i = 0; i < m_controlKeys.size(); ++i)
	{
		if(key == m_controlKeys[i])
			eventAndKey.second = i + 1;
	}
	
	return eventAndKey;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
