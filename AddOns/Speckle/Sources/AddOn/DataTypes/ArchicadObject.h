#pragma once

#include "json.hpp"
#include "Mesh.h"
#include "ElementBody.h"
#include "ArchicadLevel.h"

struct ArchicadObject
{
    std::string name = "";
    std::string type = "";
    std::string level = "";
    std::string speckle_type = "Objects.Data.DataObject:Objects.Data.ArchicadObject";
    std::string applicationId = "";
    ElementBody displayValue;
    nlohmann::json properties;
    std::vector<ArchicadObject> elements;
    ArchicadLevel levelInfo;
};

void to_json(nlohmann::json& j, const ArchicadObject& elem);
