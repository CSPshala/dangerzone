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
RawInputParser::RawInputParser() : m_rawDevices(nullptr), m_currentKeyboardControls(nullptr), 
	m_currentMouseControls(nullptr), m_receivedInput(false),	mMouseDeltaX(0), mMouseDeltaY(0)
{
	
}

RawInputParser::~RawInputParser()
{
	if(m_rawDevices)
	{
		delete[] m_rawDevices;
		m_rawDevices = nullptr;
	}

	if(m_currentKeyboardControls)
	{
		delete m_currentKeyboardControls;
	}
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
bool RawInputParser::Initialize()
{
	// Allocate for keyboard and mouse only for now
	m_rawDevices = new RAWINPUTDEVICE[NUM_RAW_DEVICES];

	// Add bools for buffering mouse input button status
	for(unsigned int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
		m_mouseButtonStatus.push_back(false);

	// Derp
	if(!LoadControlKeys())
	{
		LOG("RawInputParser Loading control keys failed.");
		return false;
	}
    // Load our control scheme
    if(!ReadControlConfig())
	{
		LOG("RawInputParser Reading control config failed.");
		return false;
	}

	return true;
}

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
bool RawInputParser::LoadControlKeys()
{
	xml_document doc;
	string filePath("resource/data/RawInputCommands.xml");
	
	if(!LoadXMLFile(doc,filePath))
		return false;

	for(xml_node command = doc.child("command"); command; command = command.next_sibling("command"))
	{
		string dev = command.attribute("device").as_string();
		if(dev == "keyboard")
		{
			pair<string,int> toAdd;
			toAdd.first = command.attribute("button").as_string();
			toAdd.second = command.attribute("value").as_int();
			m_controlKeys.push_back(toAdd);
		}
		else if(dev == "mouse")
		{
			pair<string,int> toAdd;
			toAdd.first = command.attribute("button").as_string();
			toAdd.second = command.attribute("value").as_int();
			m_mouseControlKeys.push_back(toAdd);
		}
		else
		{
			continue;
		}
	}

	return true;
}

bool RawInputParser::ReadControlConfig()
{
	if(m_currentKeyboardControls)
	{
		delete m_currentKeyboardControls;
		m_currentKeyboardControls = nullptr;
	}

	if(m_currentMouseControls)
	{
		delete m_currentMouseControls;
		m_currentMouseControls = nullptr;
	}

	if(m_currentKeyboardControls == nullptr)
	{
		m_currentKeyboardControls = new deque<pair<int,pair<int,bool> > >;
	}

	if(m_currentMouseControls == nullptr)
	{
		m_currentMouseControls = new deque<pair<int,pair<int,bool> > >;
	}

	// Load in control key vector
	fstream configFile(L"resource/config/user.cfg",ios::in);

	if(!configFile.is_open())
	{
		LOG("RawInputParser could not open user.cfg for parsing.");
		return false;
	}

	// Rando number for char, 30 > more than we'll need
	char keyBuff[30];

	// Line by line
	while(!configFile.eof())
	{
		bool isMouse = false;

		configFile.get(keyBuff,30,':');

		// check for mouse (fuck off I didn't wanna fix the \n issue)
		if( strcmp(keyBuff,"mouse") == 0 || strcmp(&keyBuff[1],"mouse") == 0 )
			isMouse = true;

		configFile.get(keyBuff,30);

		//Paranoid check
		if(configFile.eof())
			break;
		
		char* context = nullptr;
		char* tokPos = strtok_s(&keyBuff[1]," ",&context);
		string command(tokPos);
		string key(context);

		if(!isMouse)
		{
			m_currentKeyboardControls->push_back(FindKeyAndEventValue(command,key));
		}
		else
		{
			m_currentMouseControls->push_back(FindKeyAndEventValueMouse(command,key));
		}
	}

	configFile.close();

	return true;
}

void RawInputParser::HandleKeyboardInput(PRAWINPUT input)
{
	deque<pair<int,pair<int,bool> > >::iterator iter = m_currentKeyboardControls->begin();
	while(iter != m_currentKeyboardControls->end())
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

	// Early out if we have no flags raised for mouse buttons
	if(input->data.mouse.ulButtons == 0)
		return;

	deque<pair<int,pair<int,bool> > >::iterator iter = m_currentMouseControls->begin();
	for(;iter != m_currentMouseControls->end(); ++iter)
	{
		if((input->data.mouse.ulButtons & (*iter).second.first) && (*iter).second.second == true)
			continue;
		if((input->data.mouse.ulButtons & (*iter).second.first) == 0 && (*iter).second.second == false)
			continue;

		// Toggle button flag
		(*iter).second.second = !(*iter).second.second;

		//HAX: Send our mouse button event (the last player is mouse for now)
		InputEventSystem::GetInstance()->SendEvent((*iter).first, InputEventSystem::NUM_ALLOWED_PLAYERS - 1);
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
		if(key == m_controlKeys[i].first)
		{
			eventAndKey.second.first = m_controlKeys[i].second;
			eventAndKey.second.second = false;
		}
	}
	
	return eventAndKey;
}

pair<int,pair<int,bool> > RawInputParser::FindKeyAndEventValueMouse(string command, string key)
{
	pair<int,pair<int,bool> > eventAndKey;

	// Event code
	if(command == "click1")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK1);
	else if(command == "click2")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK2);
	else if(command == "click3")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK3);
	else if(command == "click4")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK4);
	else if(command == "click5")
		eventAndKey.first = static_cast<int>(InputEventSystem::CLICK5);

	// Keycode for command
	for(unsigned int i = 0; i < m_mouseControlKeys.size(); ++i)
	{
		if(key == m_mouseControlKeys[i].first)
		{
			eventAndKey.second.first = m_mouseControlKeys[i].second;
			eventAndKey.second.second = false;
		}
	}
	
	return eventAndKey;
}

bool RawInputParser::LoadXMLFile(xml_document& doc,const string& filePath) const
{
	xml_parse_result result = doc.load_file(filePath.c_str());

	bool returnResult = false;

	if (result)
	{
		LOG("XML [" << filePath << "] parsed without errors\n");
		returnResult = true;
	}
	else
	{
		LOG("XML [" << filePath << "] parsed with errors\n");
		LOG("Error description: " << result.description() << "\n");
		LOG("Error offset: " << result.offset << "\n");
		returnResult = false;
	}

	return returnResult;
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////
