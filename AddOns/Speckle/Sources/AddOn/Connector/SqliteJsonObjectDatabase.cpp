#include "SqliteJsonObjectDatabase.h"
#include "sqlite3.h"
#include <iostream>
#include <windows.h>
#include <shlobj.h>

static const int HASH_COLUMN = 0;
static const int DATA_COLUMN = 1;

namespace
{
    std::string WideStringToString(const std::wstring& wideString)
    {
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
        if (sizeNeeded <= 0)
        {
            throw std::runtime_error("WideCharToMultiByte conversion failed");
        }
        std::string narrowString(sizeNeeded - 1, 0); // subtract null-terminator
        WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], sizeNeeded, NULL, NULL);
        return narrowString;
    }

    const char* GetDUI3ConfigDatabasePath()
    {
        static char resultPath[MAX_PATH];
        wchar_t appDataPath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appDataPath)))
        {
            std::wstring wideDbPath = std::wstring(appDataPath) + L"\\Speckle\\DUI3Config.db";
            std::string dbPath = WideStringToString(wideDbPath);
            strncpy_s(resultPath, dbPath.c_str(), MAX_PATH - 1);
            resultPath[MAX_PATH - 1] = '\0';
            return resultPath;
        }
        else
        {
            throw std::runtime_error("Failed to get AppData path");
        }
    }
}

sqlite3* db = nullptr;

SqliteJsonObjectDatabase::SqliteJsonObjectDatabase()
{
    Init();
}

void SqliteJsonObjectDatabase::Init()
{
    const char* dbPath = GetDUI3ConfigDatabasePath();
    if (sqlite3_open(dbPath, &db) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to open database");
    }

    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS objects(
            hash TEXT PRIMARY KEY,
            content TEXT
        ) WITHOUT ROWID;
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::string err = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw std::runtime_error("Failed to create table: " + err);
    }
}

void SqliteJsonObjectDatabase::CreateOrUpdate(const std::string& id, const nlohmann::json data)
{
    const char* insertSQL = R"(
        INSERT OR REPLACE INTO objects (hash, content) VALUES (?, ?);
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare insert statement");
    }

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);
    std::string jsonData = data.dump();
    sqlite3_bind_text(stmt, 2, jsonData.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute insert");
    }

    sqlite3_finalize(stmt);
}

nlohmann::json SqliteJsonObjectDatabase::Get(const std::string& id) const
{
    const char* selectSQL = R"(
        SELECT content FROM objects WHERE hash = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare select statement");
    }

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);

    nlohmann::json result;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text)
        {
            result = nlohmann::json::parse(reinterpret_cast<const char*>(text));
        }
    }
    else
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Object not found: " + id);
    }

    sqlite3_finalize(stmt);
    return result;
}

void SqliteJsonObjectDatabase::Delete(const std::string& id)
{
    const char* deleteSQL = R"(
        DELETE FROM objects WHERE hash = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, nullptr) != SQLITE_OK)
    {
        throw std::runtime_error("Failed to prepare delete statement");
    }

    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute delete");
    }

    sqlite3_finalize(stmt);
}
