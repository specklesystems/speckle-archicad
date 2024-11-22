#pragma once

#include <string>
#include "json.hpp"

class IAccountDatabase 
{
public:
    virtual ~IAccountDatabase() = default;

    virtual nlohmann::json GetAccounts() const = 0;
    virtual nlohmann::json GetAccount(const std::string& id) const = 0;
    virtual std::string GetTokenByAccountId(const std::string& id) const = 0;

};
