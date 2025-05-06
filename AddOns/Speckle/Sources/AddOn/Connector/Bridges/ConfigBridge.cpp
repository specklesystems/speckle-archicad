#include "ConfigBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "ConnectorConfig.h"
#include "AccountsConfig.h"
#include "WorkspacesConfig.h"


ConfigBridge::ConfigBridge(IBrowserAdapter* browser)
{
    configBinding = std::make_unique<Binding>(
        "configBinding",
        std::vector<std::string>{ "GetConfig", "GetIsDevMode", "UpdateConfig", "OpenUrl", "GetUserSelectedAccountId", "SetUserSelectedAccountId", "GetWorkspacesConfig", "SetUserSelectedWorkspaceId" },
        browser,
        this
    );
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
    else if (args.methodName == "OpenUrl")
    {
        OpenUrl(args);
    }
    else if (args.methodName == "GetUserSelectedAccountId")
    {
        GetUserSelectedAccountId(args);
    }
    else if (args.methodName == "SetUserSelectedAccountId")
    {
        SetUserSelectedAccountId(args);
    }
    else if (args.methodName == "GetWorkspacesConfig")
    {
        GetWorkspacesConfig(args);
    }
    else if (args.methodName == "SetUserSelectedWorkspaceId")
    {
        SetUserSelectedWorkspaceId(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

void ConfigBridge::GetIsDevMode(const RunMethodEventArgs& args)
{
#if defined DEBUG
    args.eventSource->SetResult(args.methodId, true);
#else
    args.eventSource->SetResult(args.methodId, false);
#endif
}

static void SeedConfig()
{
    try
    {
        ConnectorConfig config;
        config.darkTheme = true;
        CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("Archicad", config);
    }
    catch (const std::exception&)
    {
        std::cout << "Failed to update connector config";
    }
}

void ConfigBridge::GetConfig(const RunMethodEventArgs& args)
{
    try
    {
        ConnectorConfig config = CONNECTOR.GetJsonObjectDatabase().Get("Archicad");
        args.eventSource->SetResult(args.methodId, config);
    }
    catch (...)
    {
        SeedConfig();
    }
}

void ConfigBridge::UpdateConfig(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    try
    {
        ConnectorConfig config = args.data[0].get<ConnectorConfig>();
        CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("Archicad", config);
    }
    catch (...)
    {
        std::cout << "Failed to update connector config";
    }
}

void ConfigBridge::OpenUrl(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string url = args.data[0].get<std::string>();
    std::string command = "start " + url;
    system(command.c_str());
}

void ConfigBridge::GetUserSelectedAccountId(const RunMethodEventArgs& args)
{
    try
    {
        AccountsConfig config = CONNECTOR.GetJsonObjectDatabase().Get("accounts");
        args.eventSource->SetResult(args.methodId, config);
    }
    catch (...)
    {
        args.eventSource->SetResult(args.methodId, nullptr);
    }
}

void ConfigBridge::SetUserSelectedAccountId(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    try
    {
        AccountsConfig config;
        config.userSelectedAccountId = args.data[0].get<std::string>();
        CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("accounts", config);
    }
    catch (...)
    {
        std::cout << "Failed to update accounts config";
    }
}

void ConfigBridge::GetWorkspacesConfig(const RunMethodEventArgs & args)
{
    try
    {
        WorkspacesConfig config = CONNECTOR.GetJsonObjectDatabase().Get("workspaces");
        args.eventSource->SetResult(args.methodId, config);
    }
    catch (...)
    {
        args.eventSource->SetResult(args.methodId, nullptr);
    }
}

void ConfigBridge::SetUserSelectedWorkspaceId(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    try
    {
        WorkspacesConfig config;
        config.userSelectedWorkspaceId = args.data[0].get<std::string>();
        CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("workspaces", config);
    }
    catch (...)
    {
        std::cout << "Failed to update workspaces config";
    }
}
