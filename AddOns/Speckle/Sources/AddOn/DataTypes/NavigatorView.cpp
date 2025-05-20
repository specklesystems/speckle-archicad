#include "NavigatorView.h"

void to_json(nlohmann::json& j, const NavigatorView& view)
{
    j["name"] = view.name;
    j["guid"] = view.guid;
}

void from_json(const nlohmann::json& j, NavigatorView& view)
{
    view.name = j.at("name").get<std::string>();
    view.guid = j.at("guid").get<std::string>();
}
