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
#include "../Globals.h"
#include <fstream>
#include "RawInputParser.h"

using namespace std;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

// Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx#standard_read
// Mouse: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645578(v=vs.85).aspx
// Keyboard: http://msdn.microsoft.com/en-us/library/windows/desktop/ms645575(v=vs.85).aspx

// Two raw devices atm (mouse/keyboard)
const int RawInputParser::NUM_RAW_DEVICES(2);
const int RawInputParser::NUM_MOUSE_BUTTONS(5);

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
RawInputParser::RawInputParser() : m_rawDevices(nullptr), m_currentControls(nullptr), m_receivedInput(false),
	mMouseDeltaX(0), mMouseDeltaY(0)
{
	// Allocate for keyboard and mouse only for now
	m_rawDevices = new RAWINPUTDEVICE[NUM_RAW_DEVICES];

	// Add bools for buffering mouse input button status
	for(unsigned int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
		m_mouseButtonStatus.push_back(false);

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

	if(m_currentControls)
	{
		delete m_currentControls;
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
    m_rawDevices[1].dwFlags = RIDEV_NOLEGACY | RIDEV_APPKEYS;   // adds HID keyboard and also ignores legacy keyboard messages
    m_rawDevices[1].hwndTarget = 0;

	if (RegisterRawInputDevices(m_rawDevices, NUM_RAW_DEVICES, sizeof(m_rawDevices[0])) == FALSE) {
        //registration failed. Call GetLastError for the cause of the error
        OutputDebugString (TEXT("Registration of raw input keyboard/mouse failed!\n"));
    }
}

void RawInputParser::ReadInput(LPARAM lParam)
{
    static UINT dwSize = sizeof(RAWINPUT);
	RAWINPUT input;

	if(GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &input, &dwSize, sizeof(RAWINPUTHEADER)) > 0)	
	{
		m_inputQueue.push(input);
	}
}

void RawInputParser::ProcessInput()
{
	if(m_inputQueue.size() == 0)
		return;

	bool sendMouseInfo = false;

	while(m_inputQueue.size() > 0)
	{
		// Pointer to current data
		RAWINPUT* current = (RAWINPUT*)&m_inputQueue.front();		

		switch(current->header.dwType)
		{
		case RIM_TYPEKEYBOARD:
			{
				HandleKeyboardInput(current);
			}
			break;
		case RIM_TYPEMOUSE:
			{
				HandleMouseInput(current);
				sendMouseInfo = true;
			}
			break;
		default:
			{
				LOG("RawInputParser received invalid input buffer type.");
			}
			break;
		}

		m_inputQueue.pop();
	}

	if(sendMouseInfo)
	{
		InputEventSystem::MouseInfo info;
		info.mDeltaX = mMouseDeltaX;
		info.mDeltaY = mMouseDeltaY;
		InputEventSystem::GetInstance()->SendMouseEvent(info);
		mMouseDeltaX = mMouseDeltaY = 0;
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
		m_currentControls = new deque<pair<int,pair<int,bool> > >;
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
	deque<pair<int,pair<int,bool> > >::iterator iter = m_currentControls->begin();
	while(iter != m_currentControls->end())
	{
		if(input->data.keyboard.VKey == (*iter).second.first)	
		{
			// Buffer the input
			if((input->data.keyboard.Flags == RI_KEY_MAKE) && (*iter).second.second == true)
				return;
			if((input->data.keyboard.Flags & RI_KEY_BREAK) && (*iter).second.second == false)
				return;	

			// Toggle down flag
			(*iter).second.second = !(*iter).second.second;

			InputEventSystem::GetInstance()->SendEvent((*iter).first); //Send this key's event
		}
		++iter;
	}

	
}

void RawInputParser::HandleMouseInput(PRAWINPUT input)
{
	mMouseDeltaX += input->data.mouse.lLastX;
	mMouseDeltaY += input->data.mouse.lLastY;

	// Do some bitshifting magic to check flags RI_MOUSE_LEFT_BUTTON_DOWN   0x0001 to
	// RI_MOUSE_BUTTON_5_UP        0x0200 buffer check and send event if need be	
	const int shifts = NUM_MOUSE_BUTTONS * 2;
	int count = 0;
	for(unsigned int i = 0; i < shifts; i += 2, ++count)
	{
		int bitCheck = (1 << i);
		if((input->data.mouse.ulButtons & bitCheck) && (m_mouseButtonStatus[count] == true))
			continue;
		if((input->data.mouse.ulButtons & bitCheck) == 0 && (m_mouseButtonStatus[count] == false))
			continue;

		// Toggle down flag
		m_mouseButtonStatus[count] = !m_mouseButtonStatus[count];

		// Send click event (8 = first click event), last client = mouse
		InputEventSystem::GetInstance()->SendEvent(8 + count,InputEventSystem::NUM_ALLOWED_PLAYERS - 1);		
	}
}

pair<int,pair<int,bool> > RawInputParser::FindKeyAndEventValue(string command, string key)
{
	pair<int,pair<int,bool> > eventAndKey;

	// Event code
	if(command == "up")
		eventAndKey.first = static_cast<int>(InputEventSystem::UP);
	else if(command == "down")
		eventAndKey.first = static_cast<int>(InputEventSystem::DOWN);
	else if(command == "left")
		eventAndKey.first = static_cast<int>(InputEventSystem::LEFT);
	else if(command == "right")
		eventAndKey.first = static_cast<int>(InputEventSystem::RIGHT);
	else if(command == "jump")
		eventAndKey.first = static_cast<int>(InputEventSystem::JUMP);
	else if(command == "attack")
		eventAndKey.first = static_cast<int>(InputEventSystem::ATTACK);
	else if(command == "quit")
		eventAndKey.first = static_cast<int>(InputEventSystem::QUIT);
	else if(command == "click1")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK1);
	else if(command == "click2")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK2);


	// Keycode for command
	for(unsigned int i = 0; i < m_controlKeys.size(); ++i)
	{
		if(key == m_controlKeys[i])
		{
			eventAndKey.second.first = i + 1;
			eventAndKey.second.second = false;
		}
	}
	
	return eventAndKey;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
