#include "SqliteJsonObjectDatabase.h"
#include "PlatformPaths.h"
#include "sqlite3.h"
#include <iostream>

namespace
{
    const std::string& GetDUI3ConfigDatabasePath()
    {
        static const std::string path = PlatformPaths::ToUtf8(
            PlatformPaths::GetSpeckleApplicationDataDirectory() / "DUI3Config.db");
        return path;
    }
}

sqlite3* db = nullptr;

SqliteJsonObjectDatabase::SqliteJsonObjectDatabase()
{
    Init();
}

void SqliteJsonObjectDatabase::Init()
{
    const std::string& dbPath = GetDUI3ConfigDatabasePath();
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK)
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
