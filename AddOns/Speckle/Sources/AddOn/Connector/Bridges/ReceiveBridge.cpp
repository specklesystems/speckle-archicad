#include "ReceiveBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "HostObjectBuilder.h"
#include "UserCancelledException.h"

ReceiveBridge::ReceiveBridge(IBrowserAdapter* browser)
{
    receiveBinding = std::make_unique<Binding>(
        "receiveBinding",
        std::vector<std::string>{ "Receive", "AfterGetObjects" },
        browser,
        this
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
    else if (args.methodName == "afterGetObjects")
    {
        AfterGetObjects(args);
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
    ReceiverModelCard card = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    nlohmann::json receiveArgs;

    receiveArgs["modelId"] = card.modelId;
    receiveArgs["projectId"] = card.projectId;
    receiveArgs["accountId"] = card.accountId;
    receiveArgs["modelCardId"] = card.modelCardId;
    receiveArgs["selectedVersionId"] = card.selectedVersionId;

    args.eventSource->Send("receiveByBrowser", receiveArgs);
}

void ReceiveBridge::AfterGetObjects(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    CONNECTOR.GetProcessWindow().Init("Receiving...", 1);

    HostObjectBuilderResult buildResult{};

    try
    {
        nlohmann::json receivedData = args.data[2];
        HostObjectBuilder hostObjectBuilder{};
        buildResult = hostObjectBuilder.Build(receivedData, modelCard.projectName, modelCard.modelName);
    }
    catch (const UserCancelledException&)
    {
        args.eventSource->Send("triggerCancel", modelCardId);
    }

    CONNECTOR.GetProcessWindow().Close();

    modelCard.bakedObjectIds = buildResult.bakedObjectIds;

    nlohmann::json res{};
    res["modelCardId"] = modelCardId;
    res["bakedObjectIds"] = buildResult.bakedObjectIds;
    res["conversionResults"] = buildResult.conversionResults;

    args.eventSource->Send("setModelReceiveResult", res);
}
