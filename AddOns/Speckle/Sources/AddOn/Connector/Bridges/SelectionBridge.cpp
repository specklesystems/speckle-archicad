#include "SelectionBridge.h"
#include "LoggerFactory.h"
#include "Connector.h"

SelectionBridge::SelectionBridge(IBrowserAdapter* browser)
{
    selectionBinding = std::make_unique<Binding>(
        "selectionBinding",
        std::vector<std::string>{ "GetSelection" },
        browser);

    selectionBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
    CONNECTOR.hostAppEvents->SelectionChanged += [this]() { SelectionChanged(); };
}

void SelectionBridge::OnRunMethod(const RunMethodEventArgs& args)
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

void SelectionBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetSelection")
    {
        GetSelection(args);
    }
    else
    {
        // TODO throw
    }
}

void SelectionBridge::GetSelection(const RunMethodEventArgs& args)
{
    nlohmann::json selection;
    selection["selectedObjectIds"] = CONNECTOR.hostToSpeckleConverter->GetSelection();
    // TODO summary
    selection["summary"] = "Hello World!";
    args.eventSource->SetResult(args.methodId, selection);
}

void SelectionBridge::SelectionChanged()
{
    // TODO implement
    std::cout << "selection changed";
}
