///////////////////////////////////////////////////////////////////////////
//	File Name	:	"XbInputParser.cpp"
//	
//	Author Name	:	JC Ricks
//	
//	Purpose		:	Manage xbox controller input event sending and parsing
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//				INCLUDES
////////////////////////////////////////
#include "../Globals.h"
#include "XbInputParser.h"
#include "../events/InputEventSystem.h"

#include <fstream>
#include <sstream>
using namespace std;

////////////////////////////////////////
//				MISC
////////////////////////////////////////

///////////////////////////////////////////////
//  CONSTRUCTOR / DECONSTRUCT / OP OVERLOADS
///////////////////////////////////////////////
XbInputParser::XbInputParser()
{
	for(int i = 0; i < InputEventSystem::NUM_ALLOWED_PLAYERS; ++i)
	{
		m_controllers.push_back(new XboxController(i));	
		m_currentFrameData.push_back(pair<XINPUT_STATE,int>());
		m_oldPacketNumbers.push_back(int(0));
	}

	// Hardcoded controller strings and values
	m_controlStrings.push_back(pair<string,int>("dpad_up", XINPUT_GAMEPAD_DPAD_UP		));
	m_controlStrings.push_back(pair<string,int>("dpad_down", XINPUT_GAMEPAD_DPAD_DOWN		));
	m_controlStrings.push_back(pair<string,int>("dpad_left", XINPUT_GAMEPAD_DPAD_LEFT		));
	m_controlStrings.push_back(pair<string,int>("dpad_right", XINPUT_GAMEPAD_DPAD_RIGHT	));
	m_controlStrings.push_back(pair<string,int>("start", XINPUT_GAMEPAD_START			));
	m_controlStrings.push_back(pair<string,int>("back", XINPUT_GAMEPAD_BACK			));
	m_controlStrings.push_back(pair<string,int>("left_thumb", XINPUT_GAMEPAD_LEFT_THUMB	));
	m_controlStrings.push_back(pair<string,int>("right_thumb", XINPUT_GAMEPAD_RIGHT_THUMB	));
	m_controlStrings.push_back(pair<string,int>("left_shoulder", XINPUT_GAMEPAD_LEFT_SHOULDER ));
	m_controlStrings.push_back(pair<string,int>("right_shoulder", XINPUT_GAMEPAD_RIGHT_SHOULDER));
	m_controlStrings.push_back(pair<string,int>("a", XINPUT_GAMEPAD_A				));
	m_controlStrings.push_back(pair<string,int>("b", XINPUT_GAMEPAD_B				));
	m_controlStrings.push_back(pair<string,int>("x", XINPUT_GAMEPAD_X				));
	m_controlStrings.push_back(pair<string,int>("y", XINPUT_GAMEPAD_Y				));

	LoadControls();
}

XbInputParser::~XbInputParser()
{	
	for(unsigned int i = 0; i < m_controllers.size(); ++i)
	{
		delete m_controllers[i];
		m_controllers[i] = nullptr;
	}

	for(unsigned int i = 0; i < m_currentControls.size(); ++i)
		if(m_currentControls[i])
			delete m_currentControls[i];
}

////////////////////////////////////////
//		PUBLIC UTILITY FUNCTIONS
////////////////////////////////////////
void XbInputParser::ReadInput()
{
	for(unsigned int i = 0; i < m_controllers.size(); ++i)
	{
		pair<XINPUT_STATE,int> controllerState;
		controllerState.second = m_controllers[i]->GetState(controllerState.first);
		m_currentFrameData[i] = controllerState;
	}
}

void XbInputParser::ProcessInput()
{
	// ENJOY REMEMBERING THIS SHIT MOTHERFUCKER!!!!! AT LEAST YOU FEEL SMART RIGHT NOW!
	// - Signed: "Past" Me
	for(unsigned int i = 0; i < m_currentFrameData.size(); ++i)
	{
		if(m_currentFrameData[i].second == ERROR_SUCCESS)
		{
			if(m_currentFrameData[i].first.dwPacketNumber != m_oldPacketNumbers[i])
			{
				for(unsigned int contInt = 0; contInt < m_currentControls[i]->size(); ++contInt)
				{
					if((*m_currentControls[i])[contInt].second.second & m_currentFrameData[i].first.Gamepad.wButtons)
					{
						if((*m_currentControls[i])[contInt].first == false)
						{
							InputEventSystem::GetInstance()->SendEvent((*m_currentControls[i])[contInt].second.first,i);
							(*m_currentControls[i])[contInt].first = true;
						}
					}
					else
					{
						if((*m_currentControls[i])[contInt].first == true)
						{
							InputEventSystem::GetInstance()->SendEvent((*m_currentControls[i])[contInt].second.first,i);
							(*m_currentControls[i])[contInt].first = false;
						}
					}				
				}

				// Send joystick info
				InputEventSystem::JoystickInfo joyInfo;
				joyInfo.mLeftStickX  = m_currentFrameData[i].first.Gamepad.sThumbLX;
				joyInfo.mLeftStickY  = m_currentFrameData[i].first.Gamepad.sThumbLY;
				joyInfo.mRightStickX = m_currentFrameData[i].first.Gamepad.sThumbRX;
				joyInfo.mRightStickY = m_currentFrameData[i].first.Gamepad.sThumbRY;

				if(joyInfo.mLeftStickX  <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
					joyInfo.mLeftStickX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					joyInfo.mLeftStickX = 0;
				}
				if(joyInfo.mLeftStickY  <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
					joyInfo.mLeftStickY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					joyInfo.mLeftStickY = 0;
				}
				if(joyInfo.mRightStickX  <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
					joyInfo.mRightStickX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					joyInfo.mRightStickX = 0;
				}
				if(joyInfo.mRightStickY  <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
					joyInfo.mRightStickY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					joyInfo.mRightStickY = 0;
				}
				InputEventSystem::GetInstance()->SendJoystickEvent(joyInfo,i);
			}			
		}
		m_oldPacketNumbers[i] = m_currentFrameData[i].first.dwPacketNumber;
	}
}

////////////////////////////////////////
//		PRIVATE UTILITY FUNCTIONS
////////////////////////////////////////
void XbInputParser::LoadControls()
{
	for(unsigned int i = 0; i < m_currentControls.size(); ++i)
		if(m_currentControls[i])
			delete m_currentControls[i];

	m_currentControls.clear();	

	for(int i = 0; i < InputEventSystem::NUM_ALLOWED_PLAYERS; ++i)
	{
		m_currentControls.push_back(new vector<pair<bool,pair<int,int> > >);

		wstring filePath(L"resource/config/xb");
		wstringstream num;
		num << i << ".cfg";
		filePath += num.str();

		// Load in control key vector
		fstream configFile(filePath,ios::in);

		if(!configFile.is_open())
			return;

		// Rando number for char, 30 > more than we'll need
		char keyBuff[30];	

		// Line by line
		while(!configFile.eof())
		{
			configFile.get(keyBuff,30,':');

			// Ignore this line char
			if(keyBuff[0] == '/' && keyBuff[1] == '/')
			{
				configFile.getline(keyBuff,30);
				continue;
			}

			configFile.get(keyBuff,30);

			//Paranoid check
			if(configFile.eof())
				break;

			pair<bool,pair<int,int> > eventAndKey;		
			char* context = nullptr;
			char* tokPos = strtok_s(&keyBuff[1]," ",&context);
			string key(tokPos);
			string command(context);

			for(unsigned int x = 0; x < m_controlStrings.size(); ++x)
				if(key == m_controlStrings[x].first)
				{
					// Event code
					if(command == "up")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::UP);
					else if(command == "down")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::DOWN);
					else if(command == "left")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::LEFT);
					else if(command == "right")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::RIGHT);
					else if(command == "jump")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::JUMP);
					else if(command == "attack")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::ATTACK);
					else if(command == "quit")
						eventAndKey.second.first = static_cast<int>(InputEventSystem::QUIT);

					eventAndKey.second.second = m_controlStrings[x].second;
					eventAndKey.first = false;
					break;
				}


				m_currentControls[i]->push_back(eventAndKey);		

				configFile.getline(keyBuff,30);

				if(configFile.eof())
					break;
		}

		configFile.close();
	}
}

////////////////////////////////////////
//	    PUBLIC ACCESSORS / MUTATORS
////////////////////////////////////////

////////////////////////////////////////
//	    PRIVATE ACCESSORS / MUTATORS
////////////////////////////////////////