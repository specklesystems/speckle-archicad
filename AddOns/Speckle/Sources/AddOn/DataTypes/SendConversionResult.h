#pragma once

#include "json.hpp"
#include "ConversionError.h"

enum ConversionResultStatus
{
    NONE = 0, // Do not use
    SUCCESS = 1,
    INFO = 2, // Not in use yet, maybe later as discussed
    WARNING = 3, // Not in use yet, maybe later as discussed
    ERROR = 4
};

struct SendConversionResult
{
    ConversionResultStatus status = ConversionResultStatus::SUCCESS;
    std::string sourceId = "";
    std::string sourceType = "";
    std::string resultId = "";
    std::string resultType = "";
    ConversionError error;
};

void to_json(nlohmann::json& j, const SendConversionResult& result);
