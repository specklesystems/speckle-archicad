#include "SendBridge.h"
#include "LoggerFactory.h"
#include "SendViaBrowserArgs.h"
#include "RootObject.h"
#include "Material.h"
#include "Connector.h"


SendBridge::SendBridge(IBrowserAdapter* browser)
{
    Init(browser);
}

void SendBridge::Init(IBrowserAdapter* browser)
{
    sendBinding = std::make_unique<Binding>(
        "sendBinding",
        std::vector<std::string>{ "GetSendFilters", "GetSendSettings", "Send" },
        browser);

    sendBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void SendBridge::OnRunMethod(const RunMethodEventArgs& args)
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
        GET_LOGGER("SendBridge")->Info("Invalid method name");
    }
}

void SendBridge::GetSendFilters(const RunMethodEventArgs& args)
{
    SendFilter filter;
    filter.typeDiscriminator = "ArchicadSelectionFilter";
    filter.name = "Selection";
    filter.selectedObjectIds = CONNECTOR.hostToSpeckleConverter->GetSelection();
    filter.summary = "Hello World";

    nlohmann::json sendFilters;
    sendFilters.push_back(filter);
    args.eventSource->SetResult(args.methodId, sendFilters);
}

void SendBridge::GetSendSettings(const RunMethodEventArgs& args)
{
    args.eventSource->SetResult(args.methodId, nlohmann::json::array());
}

void SendBridge::Send(const RunMethodEventArgs& args)
{
    // try create sendargs
    SendViaBrowserArgs sendArgs;
    try
    {
        // get the modelcard by id
        nlohmann::json parsedJson = nlohmann::json::parse(args.args);
        std::string rawString = parsedJson[0];
        std::string id = nlohmann::json::parse(rawString).get<std::string>();
        SendModelCard modelCard = CONNECTOR.modelCardDatabase->GetModelCard(id);

        nlohmann::json sendObj;
        sendObj["id"] = "";
        RootObject rootObject;

        std::vector<ElementBody> bodies;
        for (const auto& elemId : modelCard.sendFilter.selectedObjectIds)
        {
            auto body = CONNECTOR.hostToSpeckleConverter->GetElementMesh(elemId);
            bodies.push_back(body);
            ModelElement me;
            me.displayValue = body;
            rootObject.elements.push_back(me);
        }

        std::map<int, RenderMaterialProxy> collectedProxies;
        for (const auto& b : bodies)
        {
            for (const auto& m : b.meshes)
            {
                int mind = m.second.materialIndex;
                if (collectedProxies.find(mind) == collectedProxies.end())
                {
                    auto mat = CONNECTOR.hostToSpeckleConverter->GetModelMaterial(mind);
                    RenderMaterialProxy rmp;
                    rmp.value = mat;
                    collectedProxies[mind] = rmp;
                }
                
                collectedProxies[mind].objects.push_back(m.second.applicationId);
            }
        }

        for (const auto& r : collectedProxies)
        {
            rootObject.renderMaterialProxies.push_back(r.second);
        }

        sendObj["rootObject"] = rootObject;
        
        sendArgs.modelCardId = modelCard.modelCardId;
        sendArgs.projectId = modelCard.projectId;
        sendArgs.modelId = modelCard.modelId;
        sendArgs.token = CONNECTOR.accountDatabase->GetTokenByAccountId(modelCard.accountId);
        sendArgs.serverUrl = modelCard.serverUrl;
        sendArgs.accountId = modelCard.accountId;
        sendArgs.message = "Hello World: Sending data from ArchiCAD";
        sendArgs.sendObject = sendObj;
        sendArgs.sendConversionResults = nlohmann::json::array();
    }
    catch (...)
    {
         // TODO 
    }
    
    // trysend
    try
    {
        std::string methodName = "sendByBrowser";
        std::string guid = Utils::GenerateGUID64();
        std::string methodId = guid + "_" + methodName;


        auto start = std::chrono::high_resolution_clock::now();

        //args.eventSource->CacheResult(methodId, sendArgs);
        //auto argsPtr = std::make_unique<nlohmann::json>(sendArgs);

        auto js = nlohmann::json(sendArgs);
        auto argsPtr = std::make_unique<nlohmann::json>(js);
        args.eventSource->CacheResult(methodId, std::move(argsPtr));
        args.eventSource->EmitResponseReady(methodName, methodId);
        args.eventSource->ResponseReady(args.methodId);
    }
    catch (...)
    {
        // TODO
    }  
}
