#include "AccountBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"


AccountBridge::AccountBridge(IBrowserAdapter* browser)
{
	accountsBinding = std::make_unique<Binding>(
		"accountsBinding",
		std::vector<std::string>{ "GetAccounts" },
		browser);

	accountsBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

// POC duplicated code, move try catch logic to Binding
void AccountBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        accountsBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        accountsBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        accountsBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Unknown exception occured" , "", false });
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
		throw InvalidMethodNameException(args.methodName);
	}
}

void AccountBridge::GetAccounts(const RunMethodEventArgs& args)
{
	auto accounts = CONNECTOR.GetAccountDatabase().GetAccounts();
	args.eventSource->SetResult(args.methodId, accounts);
}
