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
#include "UserCancelledException.h"


SendBridge::SendBridge(IBrowserAdapter* browser)
{
    sendBinding = std::make_unique<Binding>(
        "sendBinding",
        std::vector<std::string>{ "GetSendFilters", "GetSendSettings", "Send", "AfterSendObjects" },
        browser,
        this
    );
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
    ArchicadSelectionFilter selectionFilter;
    selectionFilter.selectedObjectIds = CONNECTOR.GetHostToSpeckleConverter().GetSelection();
    selectionFilter.summary = std::to_string(selectionFilter.selectedObjectIds.size()) + " objects selected";

    ArchicadElementTypeFilter elementTypeFilter;
    for (const auto& typeName : CONNECTOR.GetHostToSpeckleConverter().GetElementTypeList())
    {
        elementTypeFilter.availableCategories.push_back({ typeName, typeName });
    }

    auto filters = nlohmann::json::array({ selectionFilter, elementTypeFilter });
    args.eventSource->SetResult(args.methodId, filters);
}

void SendBridge::GetSendSettings(const RunMethodEventArgs& args)
{
    // TODO implement
    args.eventSource->SetResult(args.methodId, nlohmann::json::array());
}

void SendBridge::Send(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    SenderModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsSenderModelCard();

    CONNECTOR.GetProcessWindow().Init("Sending...", 1);

    SendViaBrowserArgs sendArgs{};
    sendArgs.modelCardId = modelCard.modelCardId;
    sendArgs.projectId = modelCard.projectId;
    sendArgs.modelId = modelCard.modelId;
    sendArgs.serverUrl = modelCard.serverUrl;
    sendArgs.accountId = modelCard.accountId;
    sendArgs.token = CONNECTOR.GetAccountDatabase().GetTokenByAccountId(modelCard.accountId);

    CONNECTOR.GetSpeckleToHostConverter().ShowAllIn3D();

    try
    {
        nlohmann::json sendObj;
        RootObjectBuilder rootObjectBuilder{};
        auto root = rootObjectBuilder.GetRootObject(modelCard.sendFilter.GetSelectedObjectIds(), conversionResultCache);
        BaseObjectSerializer serializer{};
        auto rootObjectId = serializer.Serialize(root);
        auto batches = serializer.BatchObjects(10);

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
    catch (const UserCancelledException&)
    {
        args.eventSource->Send("triggerCancel", sendArgs.modelCardId);
    }

    CONNECTOR.GetProcessWindow().Close();
}

void SendBridge::AfterSendObjects(const RunMethodEventArgs& args)
{
    if (args.data.size() < 2)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    SenderModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsSenderModelCard();

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
