#pragma once

#include "json.hpp"
#include "Mesh.h"
#include "ElementBody.h"

struct ArchicadObject
{
    std::string name = "";
    std::string type = "";
    std::string level = "";
    std::vector<std::string> classification;
    std::string speckle_type = "Objects.Data.ArchicadObject";
    std::string applicationId = "";
    std::string units = "m"; // default to meters
    ElementBody displayValue;
    nlohmann::json properties;
};

void to_json(nlohmann::json& j, const ArchicadObject& elem);
//void from_json(const nlohmann::json& j, ArchicadObject& elem);
