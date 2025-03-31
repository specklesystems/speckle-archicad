#include "ArchicadElementTypeFilter.h"
#include "Connector.h"

void to_json(nlohmann::json& j, const ArchicadElementTypeFilter& filter)
{
    j["typeDiscriminator"] = filter.typeDiscriminator;
    j["selectedObjectIds"] = filter.selectedObjectIds;
    j["name"] = filter.name;
    j["id"] = filter.id;
    j["summary"] = filter.summary;
    j["isDefault"] = filter.isDefault;
    j["selectedCategories"] = filter.selectedCategories;
    j["availableCategories"] = filter.availableCategories;
}

void from_json(const nlohmann::json& j, ArchicadElementTypeFilter& filter)
{
    filter.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    filter.selectedObjectIds = j.at("selectedObjectIds").get<std::vector<std::string>>();
    filter.name = j.at("name").get<std::string>();
    filter.id = j.at("id").get<std::string>();
    filter.summary = j.at("summary").get<std::string>();
    filter.isDefault = j.at("isDefault").get<bool>();
    filter.selectedCategories = j.at("selectedCategories").get<std::vector<std::string>>();
    filter.availableCategories = j.at("availableCategories").get<std::vector<CategoryData>>();
}

void ArchicadElementTypeFilter::UpdateSelectedObjectIds()
{
    // TODO CONNECTOR singleton should not be used in a DataType
    selectedObjectIds = CONNECTOR.GetHostToSpeckleConverter().GetElementList(selectedCategories);
}
