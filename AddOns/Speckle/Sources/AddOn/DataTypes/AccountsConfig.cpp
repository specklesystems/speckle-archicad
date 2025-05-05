#include "AccountsConfig.h"

void to_json(nlohmann::json& j, const AccountsConfig& config)
{
    j["userSelectedAccountId"] = config.userSelectedAccountId;
}

void from_json(const nlohmann::json& j, AccountsConfig& config)
{
    config.userSelectedAccountId = j.at("userSelectedAccountId").get<std::string>();
}
