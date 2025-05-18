#pragma once

#include "json.hpp"

struct NavigatorView
{
    std::string name;
    std::string guid;
};

void to_json(nlohmann::json& j, const NavigatorView& view);
void from_json(const nlohmann::json& j, NavigatorView& view);
