#include "SendConversionResult.h"

void to_json(nlohmann::json& j, const SendConversionResult& result)
{
    j["status"] = result.status;
    j["sourceId"] = result.sourceId;
    j["sourceType"] = result.sourceType;
    j["resultId"] = result.resultId;
    j["resultType"] = result.resultType;
    j["error"] = result.error;
}
