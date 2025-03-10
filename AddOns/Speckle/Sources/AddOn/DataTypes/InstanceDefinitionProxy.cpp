#include "InstanceDefinitionProxy.h"

void from_json(const nlohmann::json& j, InstanceDefinitionProxy& proxy)
{
    try
    {
        proxy.speckle_type = j.at("speckle_type").get<std::string>();
    }
    catch (const std::exception&)
    {
        proxy.speckle_type = "Objects.Geometry.Mesh";
    }

    try
    {
        proxy.applicationId = j.at("applicationId").get<std::string>();
    }
    catch (const std::exception&)
    {
        proxy.applicationId = "0";
    }
    
    proxy.objects = j.at("objects").get<std::vector<std::string>>();
}
