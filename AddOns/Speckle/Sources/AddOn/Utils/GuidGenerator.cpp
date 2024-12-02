#include "GuidGenerator.h"
#include <windows.h>
#include <objbase.h>


std::string GuidGenerator::NewGuid()
{
    GUID guid;
    CoCreateGuid(&guid);

    // Format the GUID as a string
    char guidString[37]; // 36 characters + null terminator
    snprintf(guidString, sizeof(guidString),
        "%08x-%04x-%04x-%04x-%012llx",
        guid.Data1, guid.Data2, guid.Data3,
        (guid.Data4[0] << 8) | guid.Data4[1],
        *((unsigned long long*) & guid.Data4[2]));

    return std::string(guidString);
}
