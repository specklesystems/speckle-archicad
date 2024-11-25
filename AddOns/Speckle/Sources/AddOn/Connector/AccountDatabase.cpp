#include "AccountDatabase.h"
#include "sqlite3.h"
#include <iostream>
#include <windows.h>
#include <shlobj.h>

static const int ACCOUNT_ID_COLUMN = 0;
static const int ACCOUNT_DATA_COLUMN = 1;

namespace
{
    // Function to convert wide string to narrow string
    std::string WideStringToString(const std::wstring& wideString) 
    {
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
        if (sizeNeeded <= 0) 
        {
            throw std::runtime_error("WideCharToMultiByte conversion failed");
        }
        std::string narrowString(sizeNeeded, 0);
        WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], sizeNeeded, NULL, NULL);
        return narrowString;
    }

    // Function to get the dynamic DB path
    const char* GetAccountsDatabasePath() 
    {
        static char resultPath[MAX_PATH];
        wchar_t appDataPath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appDataPath))) 
        {
            std::wstring wideDbPath = std::wstring(appDataPath) + L"\\Speckle\\Accounts.db";
            std::string dbPath = WideStringToString(wideDbPath);
            strncpy_s(resultPath, dbPath.c_str(), MAX_PATH - 1);
            resultPath[MAX_PATH - 1] = '\0'; // Ensure null-termination
            return resultPath;
        }
        else 
        {
            throw std::runtime_error("Failed to get AppData path");
        }
    }
}

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

    // Open the database (or create it if it doesn’t exist)
    rc = sqlite3_open(GetAccountsDatabasePath(), &db);
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
