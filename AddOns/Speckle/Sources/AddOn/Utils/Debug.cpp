#include "Debug.h"
#include <windows.h>
#include <iostream>

void Debug::Print(std::string& message)
{
    std::wstring wstr(message.begin(), message.end());
    OutputDebugString(wstr.c_str());
}
