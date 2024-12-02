#pragma once

#include "json.hpp"

struct ErrorReport
{
    std::string message = "";
    std::string error = "";
    std::string stackTrace = "";
};

void to_json(nlohmann::json& j, const ErrorReport& err);
