#pragma once

#include "IAccountDatabase.h"
#include <map>

class AccountDatabase : public IAccountDatabase
{
public:
    AccountDatabase();

    nlohmann::json GetAccounts() const override;
    nlohmann::json GetAccount(const std::string& id) const override;
    std::string GetTokenByAccountId(const std::string& id) const override;

private:
    std::map<std::string, nlohmann::json> _accountsData;
    void LoadAccountsFromDB();
};
