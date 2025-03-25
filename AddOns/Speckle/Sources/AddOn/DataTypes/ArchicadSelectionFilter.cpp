#include "ArchicadSelectionFilter.h"

void to_json(nlohmann::json& j, const ArchicadSelectionFilter& filter)
{
    j["typeDiscriminator"] = filter.typeDiscriminator;
    j["selectedObjectIds"] = filter.selectedObjectIds;
    j["name"] = filter.name;
    j["summary"] = filter.summary;
    j["isDefault"] = filter.isDefault;
}

void from_json(const nlohmann::json& j, ArchicadSelectionFilter& filter)
{
    filter.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    filter.selectedObjectIds = j.at("selectedObjectIds").get<std::vector<std::string>>();
    filter.name = j.at("name").get<std::string>();
    filter.summary = j.at("summary").get<std::string>();
    filter.isDefault = j.at("isDefault").get<bool>();
}
