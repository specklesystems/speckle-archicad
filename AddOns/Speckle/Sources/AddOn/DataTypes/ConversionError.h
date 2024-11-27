#pragma once

#include "json.hpp"

struct ConversionError
{
    std::string message = "";
    std::string stackTrace = "";
};

void to_json(nlohmann::json& j, const ConversionError& err);
