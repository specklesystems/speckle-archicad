#pragma once

#include "json.hpp"
#include "Mesh.h"

struct UnpackedObject
{
    std::string applicationId = "";
    std::vector<Mesh> displayValue;
};
