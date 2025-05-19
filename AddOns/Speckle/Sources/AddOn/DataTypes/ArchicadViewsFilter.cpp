#include "ArchicadViewsFilter.h"
#include "Connector.h"

void to_json(nlohmann::json& j, const ArchicadViewsFilter& filter)
{
    j["typeDiscriminator"] = filter.typeDiscriminator;
    j["selectedObjectIds"] = filter.selectedObjectIds;
    j["name"] = filter.name;
    j["id"] = filter.id;
    j["type"] = filter.type;
    j["summary"] = filter.summary;
    j["isDefault"] = filter.isDefault;
    j["selectedView"] = filter.selectedView;
    j["availableViews"] = filter.availableViews;
}

void from_json(const nlohmann::json& j, ArchicadViewsFilter& filter)
{
    filter.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    filter.selectedObjectIds = j.at("selectedObjectIds").get<std::vector<std::string>>();
    filter.name = j.at("name").get<std::string>();
    filter.id = j.at("id").get<std::string>();
    filter.type = j.at("type").get<std::string>();
    filter.summary = j.at("summary").get<std::string>();
    filter.isDefault = j.at("isDefault").get<bool>();
    filter.selectedView = j.at("selectedView").get<std::string>();
    filter.availableViews = j.at("availableViews").get<std::vector<std::string>>();
}

void ArchicadViewsFilter::UpdateSelectedObjectIds()
{
    // TODO CONNECTOR singleton should not be used in a DataType
    CONNECTOR.GetSpeckleToHostConverter().SetView(selectedView);
    selectedObjectIds = CONNECTOR.GetHostToSpeckleConverter().GetElementListAllVisibleIn3D();
}
