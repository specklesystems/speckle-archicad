#include "SendBridge.h"
#include "SendViaBrowserArgs.h"
#include "RootObject.h"
#include "Material.h"
#include "Connector.h"
#include "RootObjectBuilder.h"
#include "InvalidMethodNameException.h"


SendBridge::SendBridge(IBrowserAdapter* browser)
{
    sendBinding = std::make_unique<Binding>(
        "sendBinding",
        std::vector<std::string>{ "GetSendFilters", "GetSendSettings", "Send" },
        browser);

    sendBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void SendBridge::OnRunMethod(const RunMethodEventArgs& args)
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
    filter.selectedObjectIds = CONNECTOR.hostToSpeckleConverter->GetSelection();
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
    std::string id = args.data.get<std::string>();
    SendModelCard modelCard = CONNECTOR.modelCardDatabase->GetModelCard(id);

    SendViaBrowserArgs sendArgs{};
    sendArgs.modelCardId = modelCard.modelCardId;
    sendArgs.projectId = modelCard.projectId;
    sendArgs.modelId = modelCard.modelId;
    sendArgs.serverUrl = modelCard.serverUrl;
    sendArgs.accountId = modelCard.accountId;
    sendArgs.token = CONNECTOR.accountDatabase->GetTokenByAccountId(modelCard.accountId);
    // TODO: message
    sendArgs.message = "Sending data from ArchiCAD";
    sendArgs.sendConversionResults = nlohmann::json::array();

    nlohmann::json sendObj;
    RootObjectBuilder rootObjectBuilder{};
    sendObj["rootObject"] = rootObjectBuilder.GetRootObject(modelCard.sendFilter.selectedObjectIds);
    sendArgs.sendObject = sendObj;

    args.eventSource->SendByBrowser(args.methodId, sendArgs);
}
