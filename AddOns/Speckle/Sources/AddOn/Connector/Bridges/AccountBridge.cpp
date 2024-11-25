#include "AccountBridge.h"
#include "Connector.h"

AccountBridge::AccountBridge(IBrowserAdapter* browser)
{
	accountsBinding = std::make_unique<Binding>(
		"accountsBinding",
		std::vector<std::string>{ "GetAccounts" },
		browser);

	accountsBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void AccountBridge::OnRunMethod(const RunMethodEventArgs& args)
{
	try
	{
		RunMethod(args);
	}
	catch (const std::exception& e)
	{
		// TODO: pass message to browser
		std::string msg = e.what();
		std::cout << msg;
	}
	catch (...)
	{
		// no good
	}
}

void AccountBridge::RunMethod(const RunMethodEventArgs& args)
{
	if (args.methodName == "GetAccounts")
	{
		GetAccounts(args);
	}
	else
	{
		// TODO?
	}
}

void AccountBridge::GetAccounts(const RunMethodEventArgs& args)
{
	auto accounts = CONNECTOR.accountDatabase->GetAccounts();
	args.eventSource->SetResult(args.methodId, accounts);
}
