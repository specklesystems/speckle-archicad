#pragma once

#include "json.hpp"
#include "ConversionError.h"

enum class ConversionResultStatus
{
    CONVERSION_NONE = 0, // Do not use
    CONVERSION_SUCCESS = 1,
    CONVERSION_INFO = 2, // Not in use yet, maybe later as discussed
    CONVERSION_WARNING = 3, // Not in use yet, maybe later as discussed
    CONVERSION_ERROR = 4
};

struct SendConversionResult
{
    ConversionResultStatus status = ConversionResultStatus::CONVERSION_SUCCESS;
    std::string sourceId = "";
    std::string sourceType = "";
    std::string resultId = "";
    std::string resultType = "";
    ConversionError error;
};

void to_json(nlohmann::json& j, const SendConversionResult& result);
