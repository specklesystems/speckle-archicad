#pragma once

#include "json.hpp"

class IDataStorage
{
public:
	virtual ~IDataStorage() = default;

	virtual void SaveData(const nlohmann::json& data, const std::string& dataId) = 0;
	virtual nlohmann::json LoadData(const std::string& dataId) = 0;
};
