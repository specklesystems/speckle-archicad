#pragma once

#include "json.hpp"

struct ConnectorConfig
{
    bool darkTheme;
};

void to_json(nlohmann::json& j, const ConnectorConfig& config);
void from_json(const nlohmann::json& j, ConnectorConfig& config);
