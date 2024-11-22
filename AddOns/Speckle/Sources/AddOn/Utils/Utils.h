#pragma once

#include <string>
#include "json.hpp"

class Utils {
public:
    static std::string GenerateGUID();
    static std::string GenerateGUID64();
    static void WriteJsonToFile(const nlohmann::json json, const std::string filePath);
    static uint32_t PackARGB(double A, double R, double G, double B);
};
