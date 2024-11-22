#include "AccountDatabase.h"
#include "sqlite3.h"
#include <iostream>

AccountDatabase::AccountDatabase() 
{
    InitData();
}

void AccountDatabase::InitData()
{
    accountsData = R"([
        {"id":"56CEDA5BBD148EA03214D2E8A59B3EB8", "token" : "e2a025001a55d70bfc43d8aa0c8f6e497898371d95", "refreshToken" : "89035e3fd8bc66b754026c54dd6d1ec725fc31bf5a", "isDefault" : true, "isOnline" : true, "serverInfo" : {"name":"Speckle", "company" : "AEC Systems Ltd.", "version" : "2.22.2", "adminContact" : "office@speckle.systems", "description" : "The Official Speckle Server - Empowering Your Design and Construction Data.", "frontend2" : true, "url" : "https://app.speckle.systems", "migration" : {"movedTo":null, "movedFrom" : "https://speckle.xyz/"}}, "userInfo" : {"id":"95449dbbad", "name" : "David Kekesi", "email" : "david@speckle.systems", "company" : null, "avatar" : null, "streams" : {"totalCount":6}, "commits" : {"totalCount":393}} },
		{"id":"F7408EBF9F5A4604D8781898234F1994", "token" : "3b2aa790d886241e4b8829a230679b9f2fa04b4721", "refreshToken" : "2aaf45814fc65e220c0dc92af985969ee10a8f4cb8", "isDefault" : false, "isOnline" : true, "serverInfo" : {"name":"Latest", "company":"AEC Systems","version":"2.22.3-alpha.228564","adminContact":"devops@speckle.systems","description":"This a test deployment of a Speckle Server.","frontend2":true,"url":"https://latest.speckle.systems","migration":{"movedTo":null,"movedFrom":"https://latest.speckle.dev/"}},"userInfo":{"id":"f159d23159","name":"David Kekesi","email":"david@speckle.systems","company":null,"avatar":null,"streams":{"totalCount":3},"commits":{"totalCount":4}}}
    ])";
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
