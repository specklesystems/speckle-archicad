#pragma once

#include "IDataStorage.h"

class ArchiCadDataStorage : public IDataStorage
{
public:
	ArchiCadDataStorage() = default;

	void SaveData(const nlohmann::json& data, const std::string& dataId) override;
	nlohmann::json LoadData(const std::string& dataId) override;
	std::string GetDataStorageId(const std::string& dataId) override;
};
