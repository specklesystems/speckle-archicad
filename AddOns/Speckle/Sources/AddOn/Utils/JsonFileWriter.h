#pragma once
#include "json.hpp"
#include <string>

class JsonFileWriter 
{
public:
	static void WriteJsonToFile(const nlohmann::json json, const std::string filePath);
};
