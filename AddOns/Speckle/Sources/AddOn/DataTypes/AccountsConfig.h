#pragma once

#include "json.hpp"

struct AccountsConfig
{
    std::string userSelectedAccountId;
};

void to_json(nlohmann::json& j, const AccountsConfig& config);
void from_json(const nlohmann::json& j, AccountsConfig& config);
