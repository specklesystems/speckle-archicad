#include "CategoryData.h"

void to_json(nlohmann::json& j, const CategoryData& data)
{
    j["name"] = data.name;
    j["id"] = data.id;
}

void from_json(const nlohmann::json& j, CategoryData& data)
{
    data.name = j.at("name").get<std::string>();
    data.id = j.at("id").get<std::string>();
}
