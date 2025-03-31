#pragma once

#include "json.hpp"
#include "EConversionResultStatus.h"
#include "ConversionError.h"

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
