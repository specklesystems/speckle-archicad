#pragma once

#include "json.hpp"
#include "Mesh.h"
#include "ElementBody.h"

struct ModelElement
{
    std::string speckle_type = "Base";
    std::string applicationId = "D2417E06-1AA5-1714-D29A-7EC8F0830726"; //TODO: remove default
    std::string units = "m"; // default to meters
    ElementBody displayValue;
};

void to_json(nlohmann::json& j, const ModelElement& elem);
void from_json(const nlohmann::json& j, ModelElement& elem);
