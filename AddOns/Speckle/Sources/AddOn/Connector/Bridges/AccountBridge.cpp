#include "AccountBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "UserCancelledException.h"
#include "WinHttpClient.h"
#include "OAuthFlow.h"
#include "AccountFactory.h"
#include "ToastNotification.h"

#include <memory>


AccountBridge::AccountBridge(IBrowserAdapter* browser)
{
	accountsBinding = std::make_unique<Binding>(
		"accountsBinding",
		std::vector<std::string>{ "GetAccounts", "removeAccount", "AddAccount", "AuthenticateAccount" },
		browser,
        this
    );
}

void AccountBridge::RunMethod(const RunMethodEventArgs& args)
{
	if (args.methodName == "GetAccounts")
	{
		GetAccounts(args);
	}
    else if (args.methodName == "removeAccount")
    {
        RemoveAccount(args);
    }
    else if (args.methodName == "AddAccount")
    {
        AddAccount(args);
    }
    else if (args.methodName == "AuthenticateAccount")
    {
        AuthenticateAccount(args);
    }
	else
	{
		throw InvalidMethodNameException(args.methodName);
	}
}

void AccountBridge::GetAccounts(const RunMethodEventArgs& args)
{
    CONNECTOR.GetAccountDatabase().RefreshFromDB();
	auto accounts = CONNECTOR.GetAccountDatabase().GetAccounts();
	args.eventSource->SetResult(args.methodId, accounts);
}

void AccountBridge::RemoveAccount(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string accountId = args.data[0].get<std::string>();
    CONNECTOR.GetAccountDatabase().RemoveAccountById(accountId);

    args.eventSource->ResponseReady(args.methodId);
}

void AccountBridge::AddAccount(const RunMethodEventArgs& args)
{
    // Called by the frontend's "Log in with OAuth token" flow, which builds the
    // account itself (incl. its id) and hands it to us to persist. Mirrors the
    // .NET AccountBinding.AddAccount(accountId, account).
    if (args.data.size() < 2)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string accountId = args.data[0].get<std::string>();
    CONNECTOR.GetAccountDatabase().SaveAccount(accountId, args.data[1]);

    args.eventSource->ResponseReady(args.methodId);
}

void AccountBridge::AuthenticateAccount(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string serverUrl = args.data[0].get<std::string>();

    // Long-running: run synchronously behind a process window (mirrors the Send
    // flow) so the user can cancel while the browser sign-in is in progress.
    CONNECTOR.GetProcessWindow().Init("Signing in to Speckle", 1);
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Waiting for browser sign-in", 1);

    try
    {
        auto http = std::make_shared<WinHttpClient>();

        OAuthFlow flow(http);
        OAuthTokens tokens = flow.Authenticate(
            serverUrl,
            // The DUI3 bridge rejects the call after 60s (GenericBridge.TIMEOUT_MS),
            // so waiting longer is pointless; time out just under that and let the
            // frontend surface its "try OAuth token" fallback.
            55,
            [] { return CONNECTOR.GetProcessWindow().IsProcessCanceled(); });

        CONNECTOR.GetAccountDatabase().RefreshFromDB();
        bool isFirstAccount = CONNECTOR.GetAccountDatabase().GetAccounts().empty();

        AccountFactory factory(http);
        nlohmann::json account = factory.CreateAccount(serverUrl, tokens.token, tokens.refreshToken, isFirstAccount);

        CONNECTOR.GetAccountDatabase().SaveAccount(account["id"].get<std::string>(), account);

        CONNECTOR.GetProcessWindow().Close();
        args.eventSource->SetResult(args.methodId, account);
    }
    catch (const UserCancelledException&)
    {
        CONNECTOR.GetProcessWindow().Close();
        // Resolve the pending JS promise with an empty object (not null) so the
        // frontend's `acc.token` check is falsy rather than throwing.
        args.eventSource->SetResult(args.methodId, nlohmann::json::object());
    }
    catch (const std::exception& ex)
    {
        CONNECTOR.GetProcessWindow().Close();
        args.eventSource->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER, "Could not add account", ex.what(), false });
        args.eventSource->SetResult(args.methodId, nlohmann::json::object());
    }
}
