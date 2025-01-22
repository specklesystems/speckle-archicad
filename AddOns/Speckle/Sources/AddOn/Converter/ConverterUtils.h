#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"

#include <Model.hpp>
#include <string>

class ConverterUtils 
{
public:
    static API_Element GetElement(const std::string elemId);
    static API_ElementMemo GetElementMemo(const std::string elemId);
    static ModelerAPI::Model GetArchiCadModel();
    static std::string GetAttributeName(API_AttributeIndex attributeIndex, API_AttrTypeID attributeType);
};
