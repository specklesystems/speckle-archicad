#include "ConnectorConfig.h"

void to_json(nlohmann::json& j, const ConnectorConfig& config)
{
    j["darkTheme"] = config.darkTheme;
}

void from_json(const nlohmann::json& j, ConnectorConfig& config)
{
    config.darkTheme = j.at("darkTheme").get<bool>();
}
