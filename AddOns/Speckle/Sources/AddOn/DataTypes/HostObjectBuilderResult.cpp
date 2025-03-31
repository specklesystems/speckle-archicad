#include "HostObjectBuilderResult.h"

void to_json(nlohmann::json& j, const HostObjectBuilderResult& result)
{
    j["bakedObjectIds"] = result.bakedObjectIds;
    j["conversionResults"] = result.conversionResults;
}
