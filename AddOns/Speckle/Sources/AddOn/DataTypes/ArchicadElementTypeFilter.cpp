#include "ArchicadElementTypeFilter.h"
#include "Connector.h"
#include <algorithm>

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

bool ArchicadElementTypeFilter::SelectsEveryAvailableCategory() const
{
    return !availableCategories.empty() &&
        std::all_of(availableCategories.begin(), availableCategories.end(), [&](const CategoryData& category) {
            return std::find(selectedCategories.begin(), selectedCategories.end(), category.id) != selectedCategories.end();
        });
}

void ArchicadElementTypeFilter::UpdateSelectedObjectIds()
{
    // TODO CONNECTOR singleton should not be used in a DataType
    auto& converter = CONNECTOR.GetHostToSpeckleConverter();

    // A card stores the categories it was offered, so one that selected all of them keeps
    // meaning "every type" when a category is added later (ENG-10269: Lamp).
    const auto categories = SelectsEveryAvailableCategory() ? converter.GetElementTypeList() : selectedCategories;
    selectedObjectIds = converter.GetElementList(categories);
}
