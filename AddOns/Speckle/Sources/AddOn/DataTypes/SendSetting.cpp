#include "SendSetting.h"

void to_json(nlohmann::json& j, const SendSetting& setting)
{
    j["id"] = setting.id;
    j["title"] = setting.title;
    j["type"] = setting.type;
    j["value"] = setting.value;
}

void from_json(const nlohmann::json& j, SendSetting& setting)
{
    setting.id = j.at("id").get<std::string>();
    setting.title = j.at("title").get<std::string>();
    setting.type = j.at("type").get<std::string>();
    setting.value = j.at("value").get<nlohmann::json>();
}
