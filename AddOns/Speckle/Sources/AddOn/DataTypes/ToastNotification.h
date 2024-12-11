#pragma once

#include "json.hpp"

enum class ToastNotificationType 
{
    TOAST_SUCCESS,
    TOAST_WARNING,
    TOAST_DANGER,
    TOAST_INFO
};

struct ToastNotification
{
    ToastNotificationType type = ToastNotificationType::TOAST_INFO;
    std::string title = "";
    std::string description = "";
    bool autoClose;
};

void to_json(nlohmann::json& j, const ToastNotification& level);
