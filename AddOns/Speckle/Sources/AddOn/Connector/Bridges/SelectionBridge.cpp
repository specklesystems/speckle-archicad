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
        ToastNotification toast;
        toast.title = "Exception occured in the ArhciCAD API";
        toast.description = acex.what();
        toast.type = ToastNotificationType::DANGER;
        selectionBinding->SetToastNotification(toast);
    }
    catch (const std::exception& stdex)
    {
        ToastNotification toast;
        toast.title = "Exception occured";
        toast.description = stdex.what();
        toast.type = ToastNotificationType::DANGER;
        selectionBinding->SetToastNotification(toast);
    }
    catch (...)
    {
        ToastNotification toast;
        toast.title = "Unknown exception occured";
        toast.type = ToastNotificationType::DANGER;
        selectionBinding->SetToastNotification(toast);
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
