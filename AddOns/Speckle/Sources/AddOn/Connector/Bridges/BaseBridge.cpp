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
        browser,
        this
    );
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
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    ModelCard modelCard = args.data[0].get<ModelCard>();
    CONNECTOR.GetModelCardDatabase().AddModel(modelCard);
    args.eventSource->ResponseReady(args.methodId);
}

void BaseBridge::GetConnectorVersion(const RunMethodEventArgs& args) 
{
    // TODO move this id to ResourceIds.hpp
    short versionStringResourceId = 5010;
    auto versionInfo = CONNECTOR.GetHostToSpeckleConverter().GetResourceString(versionStringResourceId);
    args.eventSource->SetResult(args.methodId, versionInfo);
}

void BaseBridge::GetDocumentInfo(const RunMethodEventArgs& args) 
{
    try
    {
        auto documentInfo = CONNECTOR.GetHostToSpeckleConverter().GetProjectInfo();
        documentInfo.id = "9FB91C96-3D34-4A2F-81CF-206FFE2FD185";
        args.eventSource->SetResult(args.methodId, documentInfo);
    }
    catch (const ArchiCadApiException& acex)
    {
        // handle no open project exception locally
        if (acex.getErrorCode() == -2130313013)
        {
            args.eventSource->SetResult(args.methodId, nullptr);
        }
        else
        {
            throw;
        }
    }
}

void BaseBridge::GetDocumentState(const RunMethodEventArgs& args) 
{
    auto modelsJson = CONNECTOR.GetModelCardDatabase().GetModelsAsJson();
    args.eventSource->SetResult(args.methodId, modelsJson);
}

void BaseBridge::GetSourceApplicationName(const RunMethodEventArgs& args) 
{
    args.eventSource->SetResult(args.methodId, "archicad");
}

void BaseBridge::GetSourceApplicationVersion(const RunMethodEventArgs& args) 
{
    auto appVersion = CONNECTOR.GetHostToSpeckleConverter().GetHostAppReleaseInfo();
    args.eventSource->SetResult(args.methodId, appVersion);
}

void BaseBridge::HighlightModel(const RunMethodEventArgs& args) 
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    auto id = args.data[0].get<std::string>();
    ModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(id);

    if (modelCard.IsSenderModelCard())
    {
        auto selection = modelCard.AsSenderModelCard().sendFilter.GetSelectedObjectIds();
        CONNECTOR.GetSpeckleToHostConverter().SetSelection(selection);
    }
    else if(modelCard.IsReceiverModelCard())
    {
        auto selection = modelCard.AsReceiverModelCard().bakedObjectIds;
        CONNECTOR.GetSpeckleToHostConverter().SetSelection(selection);
    }
    else
    {
        // throw?
    }
}

void BaseBridge::HighlightObjects(const RunMethodEventArgs& args) 
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    auto selection = args.data[0].get<std::vector<std::string>>();
    CONNECTOR.GetSpeckleToHostConverter().SetSelection(selection);
}

void BaseBridge::OpenUrl(const RunMethodEventArgs& args) 
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string url = args.data[0].get<std::string>();
    std::string command = "start " + url;
    system(command.c_str());
}

void BaseBridge::RemoveModel(const RunMethodEventArgs& args) 
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    ModelCard modelCard = args.data[0].get<ModelCard>();
    CONNECTOR.GetModelCardDatabase().RemoveModel(modelCard.modelCardId);
    args.eventSource->ResponseReady(args.methodId);
}

void BaseBridge::UpdateModel(const RunMethodEventArgs& args) 
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    ModelCard modelCard = args.data[0].get<ModelCard>();
    CONNECTOR.GetModelCardDatabase().AddModel(modelCard);
    args.eventSource->ResponseReady(args.methodId);
}

void BaseBridge::OnDocumentChanged()
{
    baseBinding->Emit("documentChanged");
}
