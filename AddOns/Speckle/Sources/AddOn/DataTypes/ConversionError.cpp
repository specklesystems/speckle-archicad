#include "ConversionError.h"

void to_json(nlohmann::json& j, const ConversionError& err)
{
    j["message"] = err.message;
    j["stackTrace"] = err.stackTrace;
}
