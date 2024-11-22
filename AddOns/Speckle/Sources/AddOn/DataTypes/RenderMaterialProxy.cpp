#include "RenderMaterialProxy.h"

void to_json(nlohmann::json& j, const RenderMaterialProxy& proxy)
{
    j["speckle_type"] = proxy.speckle_type;
    j["applicationId"] = proxy.applicationId;
    j["value"] = proxy.value;
    j["objects"] = proxy.objects;
}
