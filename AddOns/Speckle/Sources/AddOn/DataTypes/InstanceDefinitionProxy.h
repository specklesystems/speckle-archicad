#pragma once

#include "json.hpp"

struct InstanceDefinitionProxy
{
    std::string speckle_type = "";
    std::string applicationId = "";
    std::vector<std::string> objects;
};

void from_json(const nlohmann::json& j, InstanceDefinitionProxy& proxy);
