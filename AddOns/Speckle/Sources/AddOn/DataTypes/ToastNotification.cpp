#include "ToastNotification.h"

void to_json(nlohmann::json& j, const ToastNotification& notification)
{
    j["type"] = notification.type;
    j["title"] = notification.title;
    j["description"] = notification.description;
    j["autoClose"] = notification.autoClose;
}
