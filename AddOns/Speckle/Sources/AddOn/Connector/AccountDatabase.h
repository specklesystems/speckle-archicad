#pragma once

#include "IAccountDatabase.h"

class AccountDatabase : public IAccountDatabase
{
public:
    AccountDatabase();

    nlohmann::json GetAccounts() const override;
    nlohmann::json GetAccount(const std::string& id) const override;
    std::string GetTokenByAccountId(const std::string& id) const override;
    std::string GetAccountsFromDB() const;

private:
    void InitData();
    std::string accountsData;
};
