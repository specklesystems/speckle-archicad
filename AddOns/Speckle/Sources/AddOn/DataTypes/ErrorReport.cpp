#include "ErrorReport.h"

void to_json(nlohmann::json& j, const ErrorReport& err)
{
    j["message"] = err.message;
    j["error"] = err.error;
    j["stackTrace"] = err.stackTrace;
}
