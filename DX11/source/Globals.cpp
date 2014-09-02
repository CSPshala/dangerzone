#include "Globals.h"
// NOTE: Now defining previously declared globals

#ifdef _DEBUG
std::stringstream DEBUGLOG::G_DEBUGLOGSTREAM = std::stringstream();
#endif 

const int				ApplicationSettings::g_ResolutionW = 1024;
const int				ApplicationSettings::g_ResolutionH = 768;
const bool				ApplicationSettings::g_FullScreen = false;
const bool				ApplicationSettings::g_VSync = true;
HINSTANCE	 WindowGlobals::g_hInstance = 0;
HWND		 WindowGlobals::g_hWnd = 0;
wchar_t		 WindowGlobals::g_szWINDOW_CLASS[15] = L"none";
wchar_t		 WindowGlobals::g_szWINDOW_TITLE[15] = L"none";

rectangle::rectangle() : Min(-1.0f,-1.0f,0.0f), Max(-1.0f,-1.0f,0.0f)
{
}

float rectangle::Width()
{
	return Max.x - Min.x;
}

float rectangle::Height()
{
	return Max.y - Min.y;
}

bool G_FLOAT_EPSILON(float left, float right)
{
	float dif = left - right;
	return (dif < FLT_EPSILON && dif > -FLT_EPSILON);	
}

bool LoadXMLFile(xml_document& doc,const std::string& filePath)
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