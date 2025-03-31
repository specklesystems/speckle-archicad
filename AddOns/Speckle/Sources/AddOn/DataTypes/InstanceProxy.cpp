#include "InstanceProxy.h"

void from_json(const nlohmann::json& j, InstanceProxy& proxy)
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

    try
    {
        proxy.definitionId = j.at("definitionId").get<std::string>();
    }
    catch (const std::exception&)
    {
        proxy.definitionId = "0";
    }

    try
    {
        proxy.units = j.at("units").get<std::string>();
    }
    catch (const std::exception&)
    {
        proxy.units = "m";
    }
    
    proxy.transform = j.at("transform").get<std::vector<double>>();
}
