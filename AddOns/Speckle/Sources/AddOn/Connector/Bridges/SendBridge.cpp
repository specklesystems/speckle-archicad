#include "SendBridge.h"
#include "SendViaBrowserArgs.h"
#include "RootObject.h"
#include "Material.h"
#include "Connector.h"
#include "RootObjectBuilder.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "BaseObjectSerializer.h"
#include "AfterSendObjectsArgs.h"


SendBridge::SendBridge(IBrowserAdapter* browser)
{
    sendBinding = std::make_unique<Binding>(
        "sendBinding",
        std::vector<std::string>{ "GetSendFilters", "GetSendSettings", "Send", "AfterSendObjects" },
        browser);

    sendBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

// POC duplicated code, move try catch logic to Binding
void SendBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        sendBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        sendBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        sendBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Unknown exception occured" , "", false });
    }
}

void SendBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetSendFilters")
    {
        GetSendFilters(args);
    }
    else if (args.methodName == "GetSendSettings")
    {
        GetSendSettings(args);
    }
    else if (args.methodName == "Send")
    {
        Send(args);
    }
    else if (args.methodName == "afterSendObjects")
    {
        AfterSendObjects(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

void SendBridge::GetSendFilters(const RunMethodEventArgs& args)
{
    SendFilter filter;
    filter.typeDiscriminator = "ArchicadSelectionFilter";
    filter.name = "Selection";
    filter.selectedObjectIds = CONNECTOR.GetHostToSpeckleConverter().GetSelection();
    filter.summary = std::to_string(filter.selectedObjectIds.size()) + " objects selected";

    nlohmann::json sendFilters;
    sendFilters.push_back(filter);
    args.eventSource->SetResult(args.methodId, sendFilters);
}

void SendBridge::GetSendSettings(const RunMethodEventArgs& args)
{
    // TODO implement
    args.eventSource->SetResult(args.methodId, nlohmann::json::array());
}

void SendBridge::Send(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string id = args.data[0].get<std::string>();
    SendModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(id);

    SendViaBrowserArgs sendArgs{};
    sendArgs.modelCardId = modelCard.modelCardId;
    sendArgs.projectId = modelCard.projectId;
    sendArgs.modelId = modelCard.modelId;
    sendArgs.serverUrl = modelCard.serverUrl;
    sendArgs.accountId = modelCard.accountId;
    sendArgs.token = CONNECTOR.GetAccountDatabase().GetTokenByAccountId(modelCard.accountId);
    // TODO: message
    //sendArgs.message = "Sending model from ArchiCAD";

    CONNECTOR.GetSpeckleToHostConverter().ShowAllIn3D();
    nlohmann::json sendObj;
    RootObjectBuilder rootObjectBuilder{};
    auto root = rootObjectBuilder.GetRootObject(modelCard.sendFilter.selectedObjectIds, conversionResultCache);

    BaseObjectSerializer serializer{};
    auto rootObjectId = serializer.Serialize(root);
    auto batches = serializer.BatchObjects(5);

    sendArgs.referencedObjectId = rootObjectId;

    int i = 1;
    int batchSize = static_cast<int>(batches.size());
    for (const auto& b : batches)
    {
        sendArgs.batch = b;
        sendArgs.currentBatch = i;
        i++;
        sendArgs.totalBatch = batchSize;
        args.eventSource->SendBatchViaBrowser(args.methodId, sendArgs);
    }
}

void SendBridge::AfterSendObjects(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string id = args.data[0].get<std::string>();
    SendModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(id);

    AfterSendObjectsArgs afterSendObjectsArgs{};
    afterSendObjectsArgs.modelCardId = modelCard.modelCardId;
    afterSendObjectsArgs.projectId = modelCard.projectId;
    afterSendObjectsArgs.modelId = modelCard.modelId;
    afterSendObjectsArgs.serverUrl = modelCard.serverUrl;
    afterSendObjectsArgs.accountId = modelCard.accountId;
    afterSendObjectsArgs.token = CONNECTOR.GetAccountDatabase().GetTokenByAccountId(modelCard.accountId);
    std::string referencedObjectId = args.data[1].get<std::string>();
    afterSendObjectsArgs.referencedObjectId = referencedObjectId;
    afterSendObjectsArgs.sendConversionResults = nlohmann::json::array();
    afterSendObjectsArgs.sendConversionResults = conversionResultCache;

    args.eventSource->CreateVersionViaBrowser(args.methodId, afterSendObjectsArgs);
    conversionResultCache.clear();
}
