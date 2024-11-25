#include "AccountDatabase.h"
#include "sqlite3.h"
#include <iostream>

static const int ACCOUNT_ID_COLUMN = 0;
static const int ACCOUNT_DATA_COLUMN = 1;

AccountDatabase::AccountDatabase() 
{
    LoadAccountsFromDB();
}

nlohmann::json AccountDatabase::GetAccounts() const 
{
    auto accounts = nlohmann::json::array();
    for (const auto& [id, account] : _accountsData)
        accounts.push_back(account);

    return accounts;
}

nlohmann::json AccountDatabase::GetAccount(const std::string& id) const 
{
    try
    {
        return _accountsData.at(id);
    }
    catch (const std::exception&)
    {
        // TODO
        return {};
    }
}

std::string AccountDatabase::GetTokenByAccountId(const std::string& id) const
{
    auto account = GetAccount(id);
    auto token = account["token"].get<std::string>();
    return token;
}

void AccountDatabase::LoadAccountsFromDB()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    // TODO: change this to actual appdata
    const char* dbPath = "C:/Users/david/AppData/Roaming/Speckle/Accounts.db";

    // Open the database (or create it if it doesn’t exist)
    rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }

    // SQL query to execute
    const char* sql = "SELECT * FROM objects";

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    // Execute the query and collect results
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        try
        {
            const char* id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, ACCOUNT_ID_COLUMN));
            const char* account = reinterpret_cast<const char*>(sqlite3_column_text(stmt, ACCOUNT_DATA_COLUMN));
            _accountsData[id] = nlohmann::json::parse(account);
        }
        catch (...)
        {
            // TODO
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
