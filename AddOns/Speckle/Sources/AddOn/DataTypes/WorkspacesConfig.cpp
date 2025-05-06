#include "WorkspacesConfig.h"

void to_json(nlohmann::json& j, const WorkspacesConfig& config)
{
    j["userSelectedWorkspaceId"] = config.userSelectedWorkspaceId;
}

void from_json(const nlohmann::json& j, WorkspacesConfig& config)
{
    config.userSelectedWorkspaceId = j.at("userSelectedWorkspaceId").get<std::string>();
}
