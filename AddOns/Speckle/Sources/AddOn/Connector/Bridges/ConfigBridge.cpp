#include "ConfigBridge.h"
#include "LoggerFactory.h"


ConfigBridge::ConfigBridge(IBrowserAdapter* browser)
{
    Init(browser);
}

void ConfigBridge::Init(IBrowserAdapter* browser)
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
        GET_LOGGER("ConfigBridge")->Info("Invalid method name");
    }
}

void ConfigBridge::GetConfig(const RunMethodEventArgs& args)
{
    GET_LOGGER("ConfigBridge")->Info(args.methodName + " called");
    
    nlohmann::json res;
    res["darkTheme"] = true;
    args.eventSource->SetResult(args.methodId, res);
}

void ConfigBridge::GetIsDevMode(const RunMethodEventArgs& args)
{
    GET_LOGGER("ConfigBridge")->Info(args.methodName + " called");

    args.eventSource->SetResult(args.methodId, true);
}

void ConfigBridge::UpdateConfig(const RunMethodEventArgs& args)
{
    GET_LOGGER("ConfigBridge")->Info(args.methodName + " called");
    // Logic to update the configuration data goes here
}
