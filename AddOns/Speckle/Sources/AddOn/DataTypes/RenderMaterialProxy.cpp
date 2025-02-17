#include "RenderMaterialProxy.h"

void to_json(nlohmann::json& j, const RenderMaterialProxy& proxy)
{
    j["speckle_type"] = proxy.speckle_type;
    j["applicationId"] = proxy.applicationId;
    j["value"] = proxy.value;
    j["objects"] = proxy.objects;
}

void from_json(const nlohmann::json& j, RenderMaterialProxy& proxy)
{
    proxy.speckle_type = j.at("speckle_type").get<std::string>();
    proxy.applicationId = j.at("applicationId").get<std::string>();
    proxy.value = j.at("value").get<Material>();
    proxy.objects = j.at("objects").get<std::vector<std::string>>();
}
