#include "SendFilter.h"

void to_json(nlohmann::json& j, const SendFilter& filter)
{
    j["typeDiscriminator"] = filter.typeDiscriminator;
    j["selectedObjectIds"] = filter.selectedObjectIds;
    j["name"] = filter.name;
    j["summary"] = filter.summary;
}

void from_json(const nlohmann::json& j, SendFilter& filter)
{
    filter.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    filter.selectedObjectIds = j.at("selectedObjectIds").get<std::vector<std::string>>();
    filter.name = j.at("name").get<std::string>();
    filter.summary = j.at("summary").get<std::string>();
}
