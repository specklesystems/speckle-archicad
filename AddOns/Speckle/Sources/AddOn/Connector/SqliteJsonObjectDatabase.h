#pragma once

#include "IJsonObjectDatabase.h"

class SqliteJsonObjectDatabase : public IJsonObjectDatabase
{
public:
    SqliteJsonObjectDatabase();

	void CreateOrUpdate(const std::string& id, const nlohmann::json data) override;
    nlohmann::json Get(const std::string& id) const override;
    void Delete(const std::string& id) override;

private:
    void Init();
};
