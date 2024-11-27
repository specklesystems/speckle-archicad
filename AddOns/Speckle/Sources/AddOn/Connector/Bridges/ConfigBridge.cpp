#include "ConfigBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"


ConfigBridge::ConfigBridge(IBrowserAdapter* browser)
{
    configBinding = std::make_unique<Binding>(
        "configBinding",
        std::vector<std::string>{ "GetConfig", "GetIsDevMode", "UpdateConfig" },
        browser
    );

    configBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void ConfigBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        configBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        configBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        configBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Unknown exception occured" , "", false });
    }
}

void ConfigBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetConfig")
    {
        GetConfig(args);
    }
    else if (args.methodName == "GetIsDevMode")
    {
        GetIsDevMode(args);
    }
    else if (args.methodName == "UpdateConfig")
    {
        UpdateConfig(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

void ConfigBridge::GetConfig(const RunMethodEventArgs& args)
{    
    nlohmann::json res;
    res["darkTheme"] = true;
    args.eventSource->SetResult(args.methodId, res);
}

void ConfigBridge::GetIsDevMode(const RunMethodEventArgs& args)
{
    // TODO implement
    args.eventSource->SetResult(args.methodId, true);
}

void ConfigBridge::UpdateConfig(const RunMethodEventArgs& /*args*/)
{
    // TODO implement
}
