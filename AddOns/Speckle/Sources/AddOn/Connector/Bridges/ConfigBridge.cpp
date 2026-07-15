#include "ConfigBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "ConnectorConfig.h"
#include "AccountsConfig.h"
#include "WorkspacesConfig.h"
#include "UrlLauncher.h"


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

void ConfigBridge::GetConfig(const RunMethodEventArgs& args)
{
    try
    {
        ConnectorConfig config = CONNECTOR.GetJsonObjectDatabase().Get("Archicad");
        args.eventSource->SetResult(args.methodId, config);
    }
    catch (...)
    {
		ConnectorConfig config;
		config.darkTheme = true;
		CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("Archicad", config);
		args.eventSource->SetResult(args.methodId, config);
    }
}

void ConfigBridge::UpdateConfig(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
	{
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);
	}

	ConnectorConfig config = args.data[0].get<ConnectorConfig>();
	CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("Archicad", config);
	args.eventSource->ResponseReady(args.methodId);
}

void ConfigBridge::OpenUrl(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
	{
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);
	}

	UrlLauncher::OpenInDefaultBrowser(args.data[0].get<std::string>());
	args.eventSource->ResponseReady(args.methodId);
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
	{
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);
	}

	AccountsConfig config;
	config.userSelectedAccountId = args.data[0].get<std::string>();
	CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("accounts", config);
	args.eventSource->ResponseReady(args.methodId);
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
	{
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);
	}

	WorkspacesConfig config;
	config.userSelectedWorkspaceId = args.data[0].get<std::string>();
	CONNECTOR.GetJsonObjectDatabase().CreateOrUpdate("workspaces", config);
	args.eventSource->ResponseReady(args.methodId);
}
