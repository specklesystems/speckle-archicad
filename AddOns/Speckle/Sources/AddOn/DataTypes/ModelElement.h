#pragma once

#include "json.hpp"
#include "Mesh.h"
#include "ElementBody.h"

struct ModelElement
{
    std::string speckle_type = "Base";
    std::string applicationId = "";
    std::string units = "m"; // default to meters
    ElementBody displayValue;
};

void to_json(nlohmann::json& j, const ModelElement& elem);
void from_json(const nlohmann::json& j, ModelElement& elem);
