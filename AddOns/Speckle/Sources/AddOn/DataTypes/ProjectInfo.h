#pragma once

#include "json.hpp"

struct ProjectInfo
{
    std::string location = "";
    std::string name = "";
    std::string id = "";
};

void to_json(nlohmann::json& j, const ProjectInfo& info);
