#pragma once

#include "json.hpp"


struct LayerData
{
    std::string name;
    std::string id;
};

void to_json(nlohmann::json& j, const LayerData& data);
void from_json(const nlohmann::json& j, LayerData& data);
