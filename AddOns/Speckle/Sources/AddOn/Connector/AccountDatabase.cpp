#include "AccountDatabase.h"
#include "sqlite3.h"
#include <iostream>

AccountDatabase::AccountDatabase() 
{
    InitData();
}

void AccountDatabase::InitData()
{
    accountsData = R"([])";
}

nlohmann::json AccountDatabase::GetAccounts() const 
{
    try
    {
        return nlohmann::json::parse(accountsData);
    }
    catch (...)
    {
        return nlohmann::json::object();
    }
}

nlohmann::json AccountDatabase::GetAccount(const std::string& id) const 
{
    for (const auto& account : GetAccounts()) 
    {
        if (account["id"] == id) 
        {
            return account;
        }
    }
    return nlohmann::json::object();
}

std::string AccountDatabase::GetTokenByAccountId(const std::string& id) const
{
    auto account = GetAccount(id);
    auto token = account["token"].get<std::string>();
    return token;
}

std::string AccountDatabase::GetAccountsFromDB() const
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

    // String to collect the results
    std::ostringstream resultStream;

    // Execute the query and collect results
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; ++i)
        {
            const char* columnText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            resultStream << (columnText ? columnText : "NULL");
            if (i < columnCount - 1)
            {
                resultStream << ", "; // Add a comma between column values
            }
        }
        resultStream << "\n"; // Add a newline after each row
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return resultStream.str();
}
