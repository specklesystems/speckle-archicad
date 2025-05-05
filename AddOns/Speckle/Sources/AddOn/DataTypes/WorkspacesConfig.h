#pragma once

#include "json.hpp"

struct WorkspacesConfig
{
    std::string userSelectedWorkspaceId;
};

void to_json(nlohmann::json& j, const WorkspacesConfig& config);
void from_json(const nlohmann::json& j, WorkspacesConfig& config);
