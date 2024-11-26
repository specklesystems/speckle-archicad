#include "SelectionBridge.h"
#include "Connector.h"
#include "InvalidMethodNameException.h"
#include "Base64GuidGenerator.h"


SelectionBridge::SelectionBridge(IBrowserAdapter* browser)
{
    selectionBinding = std::make_unique<Binding>(
        "selectionBinding",
        std::vector<std::string>{ "GetSelection" },
        browser);

    selectionBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
    // TODO move subscription to AddOnMain initialize?
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
        throw InvalidMethodNameException(args.methodName);
    }
}

void SelectionBridge::GetSelection(const RunMethodEventArgs& args)
{
    nlohmann::json selection;
    auto selectedElements = CONNECTOR.hostToSpeckleConverter->GetSelection();
    selection["selectedObjectIds"] = CONNECTOR.hostToSpeckleConverter->GetSelection();
    selection["summary"] = std::to_string(selectedElements.size()) + " objects selected";
    args.eventSource->SetResult(args.methodId, selection);
}

void SelectionBridge::SelectionChanged()
{
    // TODO refactor, remove code duplications
    nlohmann::json selection;
    auto selectedElements = CONNECTOR.hostToSpeckleConverter->GetSelection();
    selection["selectedObjectIds"] = selectedElements;
    selection["summary"] = std::to_string(selectedElements.size()) + " objects selected";

    std::string methodName = "setSelection";
    std::string guid = Base64GuidGenerator::NewGuid();
    std::string methodId = guid + "_" + methodName;

    auto argsPtr = std::make_unique<nlohmann::json>(selection);
    selectionBinding->CacheResult(methodId, std::move(argsPtr));
    selectionBinding->EmitResponseReady(methodName, methodId);
}
