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
        browser,
        this
    );
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
    auto selectedElements = CONNECTOR.GetHostToSpeckleConverter().GetSelection();
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
