#include "ProjectInfo.h"

void to_json(nlohmann::json& j, const ProjectInfo& info)
{
    j["location"] = info.location;
    j["name"] = info.name;
    j["id"] = info.id;
}
