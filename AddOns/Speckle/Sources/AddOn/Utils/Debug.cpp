#include "Debug.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

void Debug::Print(std::string& message)
{
#ifdef _WIN32
    OutputDebugStringA(message.c_str());
#else
    std::clog << message;
#endif
}
