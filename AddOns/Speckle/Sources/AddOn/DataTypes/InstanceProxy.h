#pragma once

#include "json.hpp"

struct InstanceProxy
{
    std::string speckle_type = "";
    std::string applicationId = "";
    std::string definitionId = "";
    std::string units = "";
    std::vector<double> transform;
};

void from_json(const nlohmann::json& j, InstanceProxy& proxy);
