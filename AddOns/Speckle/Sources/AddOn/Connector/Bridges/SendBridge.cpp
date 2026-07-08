#include "SendBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "UserCancelledException.h"
#include "SendSetting.h"
#include "SendConversionResult.h"
#include "ArchicadArtifactRootObjectBuilder.h"


SendBridge::SendBridge(IBrowserAdapter* browser)
{
    sendBinding = std::make_unique<Binding>(
        "sendBinding",
        std::vector<std::string>{ "GetSendFilters", "GetSendSettings", "Send" },
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

    ArchicadLayerFilter layerFilter;
    for (const auto& layer : CONNECTOR.GetHostToSpeckleConverter().GetLayers())
    {
        layerFilter.availableCategories.push_back({ layer.name, layer.id });
    }

    // CNX-2007
    // ACAPI_Navigator_SearchNavigatorItem API function crashes Archicad with specific files
    // temp remove view filters until we find a workaround or an API fix is released
    /*ArchicadViewsFilter viewsFilter;
    for (const auto& navigatorView : CONNECTOR.GetHostToSpeckleConverter().GetNavigatorViews())
    {
        viewsFilter.availableViews.push_back(navigatorView.name);
    }*/

    auto filters = nlohmann::json::array({ selectionFilter, elementTypeFilter, layerFilter });
    args.eventSource->SetResult(args.methodId, filters);
}

void SendBridge::GetSendSettings(const RunMethodEventArgs& args)
{
    SendSetting sendPropertiesSetting{
        "sendProperties" ,
        "Include Object Properties (disable for better performance)",
        "boolean",
        true
    };
    args.eventSource->SetResult(args.methodId, { sendPropertiesSetting });
}

static bool GetSendPropertiesSetting(const SenderModelCard& modelCard)
{
    bool sendProperties = true;

    for (const auto& setting : modelCard.settings)
    {
        if (setting.id == "sendProperties")
        {
            sendProperties = setting.value.get<bool>();
            break;
        }
    }

    return sendProperties;
}

void SendBridge::Send(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    SenderModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsSenderModelCard();

    CONNECTOR.GetProcessWindow().Init("Sending...", 1);

    CONNECTOR.GetSpeckleToHostConverter().ShowIn3D();
    auto layerStatesStart = CONNECTOR.GetHostToSpeckleConverter().GetLayers();

    bool includeProperties = GetSendPropertiesSetting(modelCard);

    // Speckle 4.0: write the parquet artefact bundle locally and upload it natively
    // (sign -> presigned PUT -> complete).
    SendViaArtifacts(args, modelCard, includeProperties);

    // restore hidden layers after send (in case user sent with LayerFilter)
    auto layerStatesEnd = CONNECTOR.GetHostToSpeckleConverter().GetLayers();
    std::vector<int> layersToHide;
    for (int i = 0; i < layerStatesStart.size(); i++)
    {
        if (layerStatesStart[i].hidden && !layerStatesEnd[i].hidden)
        {
            layersToHide.push_back(std::stoi(layerStatesStart[i].id));
        }
    }
    CONNECTOR.GetSpeckleToHostConverter().SetLayerVisibility(layersToHide, false);

    CONNECTOR.GetProcessWindow().Close();
}

void SendBridge::SendViaArtifacts(const RunMethodEventArgs& args, SenderModelCard& modelCard, bool includeProperties)
{
    std::string token = CONNECTOR.GetAccountDatabase().GetTokenByAccountId(modelCard.accountId);

    try
    {
        ArchicadArtifactRootObjectBuilder builder;
        std::vector<SendConversionResult> conversionResults;
        NativeSendResult result = builder.BuildAndUpload(
            modelCard.sendFilter.GetSelectedObjectIds(),
            includeProperties,
            modelCard.serverUrl,
            token,
            modelCard.projectId,
            modelCard.modelId,
            conversionResults);

        // Resolve the UI's Send() call and report the created version + conversion results.
        args.eventSource->SetResult(args.methodId, nlohmann::json::object());

        nlohmann::json res{};
        res["modelCardId"] = modelCard.modelCardId;
        res["versionId"] = result.versionId;
        res["sendConversionResults"] = conversionResults;
        args.eventSource->Send("setModelSendResult", res);
    }
    catch (const UserCancelledException&)
    {
        args.eventSource->Send("triggerCancel", modelCard.modelCardId);
    }
}
