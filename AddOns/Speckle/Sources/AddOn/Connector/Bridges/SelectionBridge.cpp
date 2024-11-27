#include "SelectionBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "Base64GuidGenerator.h"
#include "ArchiCadApiException.h"


SelectionBridge::SelectionBridge(IBrowserAdapter* browser)
{
    selectionBinding = std::make_unique<Binding>(
        "selectionBinding",
        std::vector<std::string>{ "GetSelection" },
        browser);

    selectionBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void SelectionBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        selectionBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false});
    }
    catch (const std::exception& stdex)
    {
        selectionBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        selectionBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Unknown exception occured" , "", false });
    }
}

void SelectionBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetSelection")
    {
        GetSelection(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

static nlohmann::json GetSelectionAsJson()
{
    nlohmann::json selection;
    auto selectedElements = CONNECTOR.hostToSpeckleConverter->GetSelection();
    selection["selectedObjectIds"] = selectedElements;
    selection["summary"] = std::to_string(selectedElements.size()) + " objects selected";

    return selection;
}

void SelectionBridge::GetSelection(const RunMethodEventArgs& args)
{
    args.eventSource->SetResult(args.methodId, GetSelectionAsJson());
}

void SelectionBridge::OnSelectionChanged()
{
    selectionBinding->Send("setSelection", GetSelectionAsJson());
}
