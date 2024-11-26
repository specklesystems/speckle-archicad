#include "SendBridge.h"
#include "SendViaBrowserArgs.h"
#include "RootObject.h"
#include "Material.h"
#include "Connector.h"
#include "RootObjectBuilder.h"

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
        // TODO: throw
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
    SendViaBrowserArgs sendArgs;
    // get the modelcard by id
    nlohmann::json parsedJson = nlohmann::json::parse(args.args);
    std::string rawString = parsedJson[0];
    std::string id = nlohmann::json::parse(rawString).get<std::string>();
    SendModelCard modelCard = CONNECTOR.modelCardDatabase->GetModelCard(id);


    nlohmann::json sendObj;
    // TODO: do i need this?
    sendObj["id"] = "";
    
    RootObjectBuilder rootObjectBuilder{};
    sendObj["rootObject"] = rootObjectBuilder.GetRootObject(modelCard.sendFilter.selectedObjectIds);

    sendArgs.modelCardId = modelCard.modelCardId;
    sendArgs.projectId = modelCard.projectId;
    sendArgs.modelId = modelCard.modelId;
    sendArgs.token = CONNECTOR.accountDatabase->GetTokenByAccountId(modelCard.accountId);
    sendArgs.serverUrl = modelCard.serverUrl;
    sendArgs.accountId = modelCard.accountId;
    // TODO: message
    sendArgs.message = "Sending data from ArchiCAD";
    sendArgs.sendObject = sendObj;
    sendArgs.sendConversionResults = nlohmann::json::array();

    // TODO move methodId generation to Binding
    std::string methodName = "sendByBrowser";
    std::string guid = Utils::GenerateGUID64();
    std::string methodId = guid + "_" + methodName;

    //args.eventSource->CacheResult(methodId, sendArgs);
    //auto argsPtr = std::make_unique<nlohmann::json>(sendArgs);

    auto js = nlohmann::json(sendArgs);
    auto argsPtr = std::make_unique<nlohmann::json>(js);
    args.eventSource->CacheResult(methodId, std::move(argsPtr));
    args.eventSource->EmitResponseReady(methodName, methodId);
    args.eventSource->ResponseReady(args.methodId);
}
