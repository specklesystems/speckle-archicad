#pragma once

#include "json.hpp"

enum ToastNotificationType 
{
    SUCCESS,
    WARNING,
    DANGER,
    INFO
};

struct ToastNotification
{
    ToastNotificationType type = ToastNotificationType::INFO;
    std::string title = "";
    std::string description = "";
    bool autoClose;
};

void to_json(nlohmann::json& j, const ToastNotification& level);
