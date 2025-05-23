#pragma once

#include "json.hpp"

struct SendSetting
{
    std::string id = "";
    std::string title = "";
    std::string type = "";
    nlohmann::json value = {};
};

void to_json(nlohmann::json& j, const SendSetting& setting);
void from_json(const nlohmann::json& j, SendSetting& setting);
