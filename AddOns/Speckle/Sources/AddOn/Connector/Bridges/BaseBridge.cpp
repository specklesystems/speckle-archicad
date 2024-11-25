#include "BaseBridge.h"
#include "LoggerFactory.h"
#include "Connector.h"

BaseBridge::BaseBridge(IBrowserAdapter* browser)
{
    Init(browser);
}

void BaseBridge::Init(IBrowserAdapter* browser)
{
    baseBinding = std::make_unique<Binding>(
        "baseBinding",
        std::vector<std::string>{
        "AddModel", "GetConnectorVersion", "GetDocumentInfo", "GetDocumentState",
            "GetSourceApplicationName", "GetSourceApplicationVersion", "HighlightModel",
            "HighlightObjects", "OpenUrl", "RemoveModel", "UpdateModel"
    },
        browser
    );

    baseBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void BaseBridge::OnRunMethod(const RunMethodEventArgs& args) 
{
    if (args.methodName == "AddModel") 
    {
        AddModel(args);
    }
    else if (args.methodName == "GetConnectorVersion") 
    {
        GetConnectorVersion(args);
    }
    else if (args.methodName == "GetDocumentInfo") 
    {
        GetDocumentInfo(args);
    }
    else if (args.methodName == "GetDocumentState") 
    {
        GetDocumentState(args);
    }
    else if (args.methodName == "GetSourceApplicationName") 
    {
        GetSourceApplicationName(args);
    }
    else if (args.methodName == "GetSourceApplicationVersion") 
    {
        GetSourceApplicationVersion(args);
    }
    else if (args.methodName == "HighlightModel") 
    {
        HighlightModel(args);
    }
    else if (args.methodName == "HighlightObjects") 
    {
        HighlightObjects(args);
    }
    else if (args.methodName == "OpenUrl") 
    {
        OpenUrl(args);
    }
    else if (args.methodName == "RemoveModel") 
    {
        RemoveModel(args);
    }
    else if (args.methodName == "UpdateModel") 
    {
        UpdateModel(args);
    }
    else 
    {
        GET_LOGGER("BaseBridge")->Info("Invalid method name: " + args.methodName);
    }
}

void BaseBridge::AddModel(const RunMethodEventArgs& args) 
{
    GET_LOGGER("BaseBridge")->Info(args.methodName + " called with args:" + args.args);
    try
    {
        nlohmann::json parsedJson = nlohmann::json::parse(args.args);
        std::string rawString = parsedJson[0];
        auto model = nlohmann::json::parse(rawString);
        SendModelCard mc = model.get<SendModelCard>();

        CONNECTOR.modelCardDatabase->AddModel(mc);

        args.eventSource->ResponseReady(args.methodId);
    }
    catch (nlohmann::json::parse_error& e)
    {
        GET_LOGGER("BaseBridge")->Info("JSON parse error: " + std::string(e.what()));
    }
    catch (std::exception& e)
    {
        GET_LOGGER("BaseBridge")->Info("Unexpected error " + std::string(e.what()));
    }
    catch (...)
    {
        // oh
    }
}

void BaseBridge::GetConnectorVersion(const RunMethodEventArgs& args) 
{
    args.eventSource->SetResult(args.methodId, "1.2.3");
}

void BaseBridge::GetDocumentInfo(const RunMethodEventArgs& args) 
{
    nlohmann::json documentInfo;
    documentInfo["location"] = "C:\\Users\\david\\Desktop\\A.pln";
    documentInfo["name"] = "A";
    documentInfo["id"] = "123456";

    args.eventSource->SetResult(args.methodId, documentInfo);
}

void BaseBridge::GetDocumentState(const RunMethodEventArgs& args) 
{
    auto models = CONNECTOR.modelCardDatabase->GetModels();
    nlohmann::json modelsJson;
    modelsJson["models"] = models;
    args.eventSource->SetResult(args.methodId, modelsJson);
}

void BaseBridge::GetSourceApplicationName(const RunMethodEventArgs& args) 
{
    args.eventSource->SetResult(args.methodId, "ArchiCAD");
}

void BaseBridge::GetSourceApplicationVersion(const RunMethodEventArgs& args) 
{
    args.eventSource->SetResult(args.methodId, "27");
}

void BaseBridge::HighlightModel(const RunMethodEventArgs& args) 
{
    GET_LOGGER("BaseBridge")->Info(args.methodName + " called with args:" + args.args);
    try
    {
        // get the modelcard by id
        nlohmann::json parsedJson = nlohmann::json::parse(args.args);
        std::string rawString = parsedJson[0];
        std::string id = nlohmann::json::parse(rawString).get<std::string>();
        SendModelCard modelCard = CONNECTOR.modelCardDatabase->GetModelCard(id);

        auto selection = modelCard.sendFilter.selectedObjectIds;
        CONNECTOR.speckleToHostConverter->SetSelection(selection);
    }
    catch (nlohmann::json::parse_error& e)
    {
        GET_LOGGER("BaseBridge")->Info("JSON parse error: " + std::string(e.what()));
    }
    catch (...)
    {
        GET_LOGGER("BaseBridge")->Info("Unexpected error");
    }
}

void BaseBridge::HighlightObjects(const RunMethodEventArgs& args) 
{
    GET_LOGGER("BaseBridge")->Info(args.methodName + " called with args:" + args.args);
}

void BaseBridge::OpenUrl(const RunMethodEventArgs& args) 
{
    nlohmann::json parsedJson = nlohmann::json::parse(args.args);
    std::string rawString = parsedJson[0];
    std::string url = nlohmann::json::parse(rawString).get<std::string>();

    std::string command = "start " + url;
    system(command.c_str());
}

void BaseBridge::RemoveModel(const RunMethodEventArgs& args) 
{
    GET_LOGGER("BaseBridge")->Info(args.methodName + " called with args:" + args.args);
}

void BaseBridge::UpdateModel(const RunMethodEventArgs& args) 
{
    GET_LOGGER("BaseBridge")->Info(args.methodName + " called with args:" + args.args);
    try
    {
        nlohmann::json parsedJson = nlohmann::json::parse(args.args);
        std::string rawString = parsedJson[0];
        auto model = nlohmann::json::parse(rawString);
        CONNECTOR.modelCardDatabase->AddModel(model);

        args.eventSource->ResponseReady(args.methodId);
    }
    catch (nlohmann::json::parse_error& e)
    {
        GET_LOGGER("BaseBridge")->Info("JSON parse error: " + std::string(e.what()));
    }
    catch (...)
    {
        GET_LOGGER("BaseBridge")->Info("Unexpected error");
    }
}
