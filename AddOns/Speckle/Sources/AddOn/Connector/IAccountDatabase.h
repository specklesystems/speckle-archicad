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
    virtual void RefreshFromDB() = 0;
    virtual void RemoveAccountById(const std::string& id) = 0;

    // Upserts an account (INSERT OR REPLACE) into the shared Accounts.db under
    // the given id (the account's computed hash) with the JSON payload.
    virtual void SaveAccount(const std::string& id, const nlohmann::json& account) = 0;
};
