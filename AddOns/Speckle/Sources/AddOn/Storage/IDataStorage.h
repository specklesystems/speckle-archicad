#pragma once

#include "json.hpp"
#include <string>

class IDataStorage
{
public:
	virtual ~IDataStorage() = default;

	virtual void SaveData(const nlohmann::json& data, const std::string& dataId) = 0;
	virtual nlohmann::json LoadData(const std::string& dataId) = 0;
	virtual std::string GetDataStorageId(const std::string& dataId) = 0;
};
