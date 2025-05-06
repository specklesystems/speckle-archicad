#pragma once

#include <string>
#include "json.hpp"

class IJsonObjectDatabase 
{
public:
    virtual ~IJsonObjectDatabase() = default;

	virtual void CreateOrUpdate(const std::string& id, const nlohmann::json data) = 0;
    virtual nlohmann::json Get(const std::string& id) const = 0;
    virtual void Delete(const std::string& id) = 0;
};
