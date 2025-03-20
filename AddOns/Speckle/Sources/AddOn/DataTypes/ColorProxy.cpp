#include "ColorProxy.h"

void to_json(nlohmann::json& j, const ColorProxy& proxy)
{
    j["speckle_type"] = proxy.speckle_type;
    j["applicationId"] = proxy.applicationId;
    j["value"] = proxy.value;
    j["objects"] = proxy.objects;
}

void from_json(const nlohmann::json& j, ColorProxy& proxy)
{
    proxy.speckle_type = j.at("speckle_type").get<std::string>();

    try
    {
        proxy.applicationId = j.at("applicationId").get<std::string>();
    }
    catch (const std::exception&)
    {
        proxy.applicationId = "0";
    }
   
    proxy.value = j.at("value").get<uint32_t>();
    proxy.objects = j.at("objects").get<std::vector<std::string>>();
}
