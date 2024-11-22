#include "SelectionBridge.h"
#include "LoggerFactory.h"
#include "Connector.h"

SelectionBridge::SelectionBridge(IBrowserAdapter* browser)
{
    Init(browser);
}

void SelectionBridge::Init(IBrowserAdapter* browser)
{
    selectionBinding = std::make_unique<Binding>(
        "selectionBinding",
        std::vector<std::string>{ "GetSelection" },
        browser);

    selectionBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
    CONNECTOR.hostAppEvents->SelectionChanged += [this](const std::string& msg) { SelectionChanged(msg); };
}

void SelectionBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetSelection")
    {
        GetSelection(args);
    }
    else
    {
        GET_LOGGER("SelectionBridge")->Info("Invalid method name");
    }
}

void SelectionBridge::GetSelection(const RunMethodEventArgs& args)
{
    nlohmann::json selection;
    selection["selectedObjectIds"] = CONNECTOR.hostToSpeckleConverter->GetSelection();
    // TODO
    selection["summary"] = "Hello World!";
    args.eventSource->SetResult(args.methodId, selection);
}

void SelectionBridge::SelectionChanged(const std::string& message)
{
    // TODO
    std::cout << message;
}
