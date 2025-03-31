#pragma once

#include "json.hpp"


struct CategoryData
{
    std::string name;
    std::string id;
};

void to_json(nlohmann::json& j, const CategoryData& level);
void from_json(const nlohmann::json& j, CategoryData& level);
