#include "ReceiveBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"


ReceiveBridge::ReceiveBridge(IBrowserAdapter* browser)
{
    receiveBinding = std::make_unique<Binding>(
        "receiveBinding",
        std::vector<std::string>{ "Receive" },
        browser
    );

    receiveBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

// POC duplicated code, move try catch logic to Binding
void ReceiveBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Unknown exception occured" , "", false });
    }
}

void ReceiveBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "Receive")
    {
        Receive(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

void ReceiveBridge::Receive(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    std::cout << modelCardId;
}
