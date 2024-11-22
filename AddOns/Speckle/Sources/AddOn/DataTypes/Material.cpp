#include "Material.h"

void to_json(nlohmann::json& j, const Material& material)
{
    j["speckle_type"] = material.speckle_type;
    j["applicationId"] = material.applicationId;
    j["name"] = material.name;
    j["diffuse"] = material.diffuse;
    j["opacity"] = material.opacity;
    j["emissive"] = material.emissive;
    j["metalness"] = material.metalness;
    j["roughness"] = material.roughness;
}

void from_json(const nlohmann::json& j, Material& material)
{
    material.speckle_type = j.at("speckle_type").get<std::string>();
    material.applicationId = j.at("applicationId").get<std::string>();
    material.name = j.at("name").get<std::string>();
    material.diffuse = j.at("diffuse").get<uint32_t>();
    material.opacity = j.at("opacity").get<double>();
    material.emissive = j.at("emissive").get<double>();
    material.metalness = j.at("metalness").get<double>();
    material.roughness = j.at("roughness").get<double>();
}
