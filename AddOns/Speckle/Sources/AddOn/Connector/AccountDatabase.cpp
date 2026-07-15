#include "AccountDatabase.h"
#include "PlatformPaths.h"
#include "sqlite3.h"
#include <iostream>

static const int ACCOUNT_ID_COLUMN = 0;
static const int ACCOUNT_DATA_COLUMN = 1;

namespace
{
    const std::string& GetAccountsDatabasePath()
    {
        static const std::string path = PlatformPaths::ToUtf8(
            PlatformPaths::GetSpeckleApplicationDataDirectory() / "Accounts.db");
        return path;
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

void AccountDatabase::RefreshFromDB()
{
    LoadAccountsFromDB();
}

void AccountDatabase::LoadAccountsFromDB()
{
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    const int openResult = sqlite3_open_v2(
        GetAccountsDatabasePath().c_str(), &db, SQLITE_OPEN_READONLY, nullptr);
    if (openResult != SQLITE_OK)
    {
        std::cerr << "Error opening account database: "
                  << (db != nullptr ? sqlite3_errmsg(db) : "unknown error") << std::endl;
        if (db != nullptr)
            sqlite3_close(db);
        return;
    }

    const char* sql = "SELECT * FROM objects";
    const int prepareResult = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (prepareResult != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::map<std::string, nlohmann::json> accounts;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        try
        {
            const char* id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, ACCOUNT_ID_COLUMN));
            const char* account = reinterpret_cast<const char*>(sqlite3_column_text(stmt, ACCOUNT_DATA_COLUMN));
            if (id != nullptr && account != nullptr)
                accounts[id] = nlohmann::json::parse(account);
        }
        catch (...)
        {
            // Ignore malformed rows while keeping the remaining accounts usable.
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    _accountsData = std::move(accounts);
}

void AccountDatabase::AddOrUpdateAccount(
    const std::string& id,
    const nlohmann::json& account)
{
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    const int openResult = sqlite3_open_v2(
        GetAccountsDatabasePath().c_str(),
        &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
        nullptr);
    if (openResult != SQLITE_OK)
    {
        const std::string error = db != nullptr ? sqlite3_errmsg(db) : "unknown error";
        if (db != nullptr)
            sqlite3_close(db);
        throw std::runtime_error("Failed to open the Speckle account database: " + error);
    }

    const char* createTableSql = R"(
        CREATE TABLE IF NOT EXISTS objects(
            hash TEXT PRIMARY KEY,
            content TEXT
        ) WITHOUT ROWID;
    )";
    char* createError = nullptr;
    if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &createError) != SQLITE_OK)
    {
        const std::string error = createError != nullptr ? createError : "unknown error";
        sqlite3_free(createError);
        sqlite3_close(db);
        throw std::runtime_error("Failed to initialize the Speckle account database: " + error);
    }

    const char* insertSql =
        "INSERT OR REPLACE INTO objects (hash, content) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const std::string error = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Failed to prepare the Speckle account update: " + error);
    }

    const std::string serializedAccount = account.dump();
    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, serializedAccount.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        const std::string error = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Failed to save the Speckle account: " + error);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    _accountsData[id] = account;
}

void AccountDatabase::RemoveAccountById(const std::string& id)
{
    sqlite3* db;
    int rc;

    // Open the database
    rc = sqlite3_open(GetAccountsDatabasePath().c_str(), &db);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL query to delete the account
    const char* sql = "DELETE FROM objects WHERE hash = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the ID parameter
    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
    else
    {
        _accountsData.erase(id);
    }

    // Finalize and close
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

