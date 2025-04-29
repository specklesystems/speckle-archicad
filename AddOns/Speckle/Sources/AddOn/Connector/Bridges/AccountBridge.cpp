#include "AccountBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"


AccountBridge::AccountBridge(IBrowserAdapter* browser)
{
	accountsBinding = std::make_unique<Binding>(
		"accountsBinding",
		std::vector<std::string>{ "GetAccounts", "removeAccount" },
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
