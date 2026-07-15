#include "AccountBridge.h"
#include "BridgeDiagnostics.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"

#ifdef __APPLE__
#include "AccountAuthenticator.h"
#include "ToastNotification.h"
#include "UrlLauncher.h"

#include <dispatch/dispatch.h>

#include <memory>

namespace
{
    struct AuthenticationCompletion
    {
        AccountBridge* bridge;
        std::shared_ptr<std::atomic_bool> lifetime;
        std::uint64_t generation;
        std::string methodId;
        nlohmann::json account;
        std::string error;
    };

    void OpenAuthenticationUrlOnMainQueue(void* context)
    {
        std::unique_ptr<std::string> url(static_cast<std::string*>(context));
        try
        {
            UrlLauncher::OpenInDefaultBrowser(*url);
        }
        catch (...)
        {
            // The authentication worker will time out and report a safe error
            // if macOS cannot open the browser.
        }
    }

    void QueueAuthenticationUrl(const std::string& url)
    {
        dispatch_async_f(
            dispatch_get_main_queue(),
            new std::string(url),
            OpenAuthenticationUrlOnMainQueue);
    }
}
#endif

AccountBridge::AccountBridge(IBrowserAdapter* browser)
{
	auto methodNames =
		std::vector<std::string>{ "GetAccounts", "addAccount", "removeAccount" };
#ifdef __APPLE__
	methodNames.push_back("AuthenticateAccount");
#endif
	accountsBinding = std::make_unique<Binding>(
		"accountsBinding",
		methodNames,
		browser,
        this
    );
}

AccountBridge::~AccountBridge()
{
#ifdef __APPLE__
    lifetime->store(false);
    authenticationThread.request_stop();
#endif
}

void AccountBridge::RunMethod(const RunMethodEventArgs& args)
{
	if (args.methodName == "GetAccounts")
	{
		GetAccounts(args);
	}
    else if (args.methodName == "addAccount")
    {
        AddAccount(args);
    }
#ifdef __APPLE__
    else if (args.methodName == "AuthenticateAccount")
    {
        AuthenticateAccount(args);
    }
#endif
    else if (args.methodName == "removeAccount")
    {
        RemoveAccount(args);
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
	BridgeDiagnostics::Write(
		"accounts-loaded count=" + std::to_string(accounts.size()));
	args.eventSource->SetResult(args.methodId, accounts);
}

void AccountBridge::AddAccount(const RunMethodEventArgs& args)
{
    if (args.data.size() < 2)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    const std::string accountId = args.data[0].get<std::string>();
    const nlohmann::json& account = args.data[1];
    if (accountId.empty() || !account.is_object())
        throw std::invalid_argument("Invalid account data");
    if (!account.contains("id") || !account["id"].is_string() ||
        account["id"].get<std::string>() != accountId)
        throw std::invalid_argument("The account ID does not match the account data");
    if (!account.contains("token") || !account["token"].is_string() ||
        account["token"].get<std::string>().empty())
        throw std::invalid_argument("The account token is missing");
    if (!account.contains("serverInfo") || !account["serverInfo"].is_object() ||
        !account["serverInfo"].contains("url") ||
        !account["serverInfo"]["url"].is_string())
        throw std::invalid_argument("The account server information is missing");
    if (!account.contains("userInfo") || !account["userInfo"].is_object())
        throw std::invalid_argument("The account user information is missing");

    CONNECTOR.GetAccountDatabase().AddOrUpdateAccount(accountId, account);
    args.eventSource->ResponseReady(args.methodId);
}

#ifdef __APPLE__
void AccountBridge::AuthenticateAccount(const RunMethodEventArgs& args)
{
    if (args.data.empty())
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    const std::string serverUrl = args.data[0].get<std::string>();
    if (serverUrl.empty())
        throw std::invalid_argument("The Speckle server URL is empty");

    ++authenticationGeneration;
    const std::uint64_t generation = authenticationGeneration;
    authenticationThread.request_stop();
    if (authenticationThread.joinable())
        authenticationThread.join();

    const auto bridgeLifetime = lifetime;
    const std::string methodId = args.methodId;
    authenticationThread = std::jthread(
        [this, bridgeLifetime, generation, methodId, serverUrl](std::stop_token stopToken)
        {
            nlohmann::json account;
            std::string error;
            try
            {
                account = AccountAuthentication::Authenticate(
                    serverUrl,
                    stopToken,
                    QueueAuthenticationUrl);
            }
            catch (const std::exception& exception)
            {
                error = exception.what();
            }
            catch (...)
            {
                error = "Unknown authentication error";
            }

            auto* completion = new AuthenticationCompletion{
                this,
                bridgeLifetime,
                generation,
                methodId,
                std::move(account),
                std::move(error)
            };
            dispatch_async_f(
                dispatch_get_main_queue(),
                completion,
                CompleteAuthenticationOnMainQueue);
        });
}

void AccountBridge::CompleteAuthenticationOnMainQueue(void* context)
{
    std::unique_ptr<AuthenticationCompletion> completion(
        static_cast<AuthenticationCompletion*>(context));
    if (!completion->lifetime->load() ||
        completion->generation != completion->bridge->authenticationGeneration)
        return;

    completion->bridge->CompleteAuthentication(
        completion->methodId,
        std::move(completion->account),
        completion->error);
}

void AccountBridge::CompleteAuthentication(
    const std::string& methodId,
    nlohmann::json account,
    const std::string& authenticationError)
{
    std::string error = authenticationError;
    if (error.empty())
    {
        try
        {
            auto& accountDatabase = CONNECTOR.GetAccountDatabase();
            account["isDefault"] = accountDatabase.GetAccounts().empty();
            const std::string accountId = account.at("id").get<std::string>();
            accountDatabase.AddOrUpdateAccount(accountId, account);
            accountsBinding->SetResult(methodId, account);
            return;
        }
        catch (const std::exception& exception)
        {
            error = exception.what();
        }
    }

    accountsBinding->SetToastNotification(ToastNotification{
        ToastNotificationType::TOAST_DANGER,
        "Failed to add your Speckle account",
        error,
        false
    });
    accountsBinding->SetResult(methodId, nlohmann::json::object());
}
#endif

void AccountBridge::RemoveAccount(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string accountId = args.data[0].get<std::string>();
    CONNECTOR.GetAccountDatabase().RemoveAccountById(accountId);

    args.eventSource->ResponseReady(args.methodId);
}
