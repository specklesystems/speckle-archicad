#pragma once

#include "json.hpp"
#include "ReceiveConversionResult.h"

struct HostObjectBuilderResult
{
    std::vector<std::string> bakedObjectIds;
    std::vector<ReceiveConversionResult> conversionResults;
};

void to_json(nlohmann::json& j, const HostObjectBuilderResult& result);
