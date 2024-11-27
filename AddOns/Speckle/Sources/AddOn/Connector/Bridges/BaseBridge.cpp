#include "BaseBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"


BaseBridge::BaseBridge(IBrowserAdapter* browser)
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

// POC duplicated code, move try catch logic to Binding
void BaseBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        baseBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        baseBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        baseBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Unknown exception occured" , "", false });
    }
}

void BaseBridge::RunMethod(const RunMethodEventArgs& args) 
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
        throw InvalidMethodNameException(args.methodName);
    }
}

void BaseBridge::AddModel(const RunMethodEventArgs& args) 
{
    SendModelCard modelCard = args.data.get<SendModelCard>();
    CONNECTOR.GetModelCardDatabase().AddModel(modelCard);
    args.eventSource->ResponseReady(args.methodId);
}

void BaseBridge::GetConnectorVersion(const RunMethodEventArgs& args) 
{
    // TODO what should this number be?
    args.eventSource->SetResult(args.methodId, "3.0.0");
}

void BaseBridge::GetDocumentInfo(const RunMethodEventArgs& args) 
{
    auto documentInfo = CONNECTOR.GetHostToSpeckleConverter().GetProjectInfo();
    documentInfo.id = CONNECTOR.GetDataStorage().GetDataStorageId(Connector::MODELCARD_ADDONOBJECT_NAME);
    args.eventSource->SetResult(args.methodId, documentInfo);
}

void BaseBridge::GetDocumentState(const RunMethodEventArgs& args) 
{
    auto modelsJson = CONNECTOR.GetModelCardDatabase().GetModelsAsJson();
    args.eventSource->SetResult(args.methodId, modelsJson);
}

void BaseBridge::GetSourceApplicationName(const RunMethodEventArgs& args) 
{
    args.eventSource->SetResult(args.methodId, "ArchiCAD");
}

void BaseBridge::GetSourceApplicationVersion(const RunMethodEventArgs& args) 
{
    // TODO implement
    // ACAPI_GetReleaseNumber
    args.eventSource->SetResult(args.methodId, "27");
}

void BaseBridge::HighlightModel(const RunMethodEventArgs& args) 
{
    auto id = args.data.get<std::string>();
    SendModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(id);
    auto selection = modelCard.sendFilter.selectedObjectIds;
    CONNECTOR.GetSpeckleToHostConverter().SetSelection(selection);
}

void BaseBridge::HighlightObjects(const RunMethodEventArgs& /*args*/) 
{
    // TODO implement
}

void BaseBridge::OpenUrl(const RunMethodEventArgs& args) 
{
    std::string url = args.data.get<std::string>();
    std::string command = "start " + url;
    system(command.c_str());
}

void BaseBridge::RemoveModel(const RunMethodEventArgs& /*args*/) 
{
    // TODO implement
}

void BaseBridge::UpdateModel(const RunMethodEventArgs& args) 
{
    SendModelCard modelCard = args.data.get<SendModelCard>();
    CONNECTOR.GetModelCardDatabase().AddModel(modelCard);
    args.eventSource->ResponseReady(args.methodId);
}

void BaseBridge::OnDocumentChanged()
{
    baseBinding->Emit("documentChanged");
}
