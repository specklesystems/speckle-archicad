#pragma once

#include "json.hpp"

struct SendFilter
{
    std::string typeDiscriminator;
    std::vector<std::string> selectedObjectIds;
    std::string name;
    std::string summary;
};

void to_json(nlohmann::json& j, const SendFilter& filter);
void from_json(const nlohmann::json& j, SendFilter& filter);
