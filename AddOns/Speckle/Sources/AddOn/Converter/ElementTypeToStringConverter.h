#pragma once

#include "APIdefs.h"
#include <map>
#include <string>

class ElementTypeToStringConverter 
{
public:
    static std::string ElementTypeToString(API_ElemTypeID type);
    static std::string ElementTypeToString(const API_ElemType& type);
    static const std::map<API_Guid, std::string>& GetMepElementTypes();
};
