#include "AccountDatabase.h"

#include <cassert>
#include <iostream>

namespace
{
    nlohmann::json MakeAccount(const std::string& token)
    {
        return {
            { "id", "TEST-ACCOUNT-ID" },
            { "token", token },
            { "refreshToken", "test-refresh-token" },
            { "isDefault", true },
            { "serverInfo", {
                { "url", "https://next.speckle.dev" },
                { "name", "Test Server" }
            } },
            { "userInfo", {
                { "id", "test-user-id" },
                { "email", "test@example.com" },
                { "name", "Test User" }
            } }
        };
    }
}

int main()
{
    {
        AccountDatabase database;
        assert(database.GetAccounts().empty());

        database.AddOrUpdateAccount("TEST-ACCOUNT-ID", MakeAccount("first-token"));
        assert(database.GetAccounts().size() == 1);
        assert(database.GetAccount("TEST-ACCOUNT-ID")["token"] == "first-token");

        database.AddOrUpdateAccount("TEST-ACCOUNT-ID", MakeAccount("updated-token"));
        assert(database.GetAccounts().size() == 1);
        assert(database.GetAccount("TEST-ACCOUNT-ID")["token"] == "updated-token");
    }

    {
        AccountDatabase reloadedDatabase;
        assert(reloadedDatabase.GetAccounts().size() == 1);
        assert(reloadedDatabase.GetAccount("TEST-ACCOUNT-ID")["token"] == "updated-token");

        reloadedDatabase.RemoveAccountById("TEST-ACCOUNT-ID");
        assert(reloadedDatabase.GetAccounts().empty());
    }

    std::cout << "AccountDatabase persistence test passed\n";
    return 0;
}
