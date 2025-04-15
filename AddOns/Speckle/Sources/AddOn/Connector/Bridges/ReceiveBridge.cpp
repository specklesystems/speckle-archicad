#include "ReceiveBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "HostObjectBuilder.h"
#include "UserCancelledException.h"
#include "LibpartPlacer.h"

ReceiveBridge::ReceiveBridge(IBrowserAdapter* browser)
{
    receiveBinding = std::make_unique<Binding>(
        "receiveBinding",
        std::vector<std::string>{ "Receive", "AfterGetObjects" },
        browser,
        this
    );

    receiveBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

// POC duplicated code, move try catch logic to Binding
void ReceiveBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        receiveBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::TOAST_DANGER , "Unknown exception occured" , "", false });
    }
}

void ReceiveBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "Receive")
    {
        Receive(args);
    }
    else if (args.methodName == "afterGetObjects")
    {
        AfterGetObjects(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

static bool ClearDirectory(const std::string& path) {
    try {
        if (!fs::exists(path) || !fs::is_directory(path)) {
            std::cerr << "Path does not exist or is not a directory: " << path << std::endl;
            return false;
        }

        for (const auto& entry : fs::directory_iterator(path)) {
            fs::remove_all(entry);
        }

        return true;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
        return false;
    }
}

static void RunReceiveService(const std::string& projectId, const std::string& selectedVersionId, const std::string& accountId) 
{
    std::string targetPath = R"(C:\poc)";
    ClearDirectory(targetPath);

    // Path to the .exe
    std::string exePath = R"(C:\dev\speckle-archicad\speckle-archicad\ArchicadReceiveService\Speckle.Archicad.ReceiveService\bin\Debug\net8.0\Speckle.Archicad.ReceiveService.exe)";

    // Build the full command line
    std::string commandLine = "\"" + exePath + "\" " + projectId + " " + selectedVersionId + " " + accountId;

    // Convert to LPSTR (Windows API requires mutable char array)
    char* cmdLine = _strdup(commandLine.c_str());

    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;

    // Create the process
    if (!CreateProcessA(
        NULL,
        cmdLine,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)) {
        std::cerr << "Failed to start process. Error: " << GetLastError() << std::endl;
        free(cmdLine);
        return;
    }

    // Wait until the process exits (optional)
    //WaitForSingleObject(pi.hProcess, INFINITE);

    // Cleanup
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    free(cmdLine);
}

void ReceiveBridge::Receive(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard card = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    nlohmann::json receiveArgs;

    receiveArgs["modelId"] = card.modelId;
    receiveArgs["projectId"] = card.projectId;
    receiveArgs["accountId"] = card.accountId;
    receiveArgs["modelCardId"] = card.modelCardId;
    receiveArgs["selectedVersionId"] = card.selectedVersionId;

    if (false)
    {
        args.eventSource->Send("receiveByBrowser", receiveArgs);
    }
    else
    {
        RunReceiveService(card.projectId, card.selectedVersionId, card.accountId);
        LibpartPlacer lp;
        //lp.AddLibparts("C:\\poc\\out");
        lp.WaitForResultsJson("C:\\poc\\_output\\Batch_001\\results.json");
        lp.LoadLibpartsFromSubDirs("C:\\poc\\_output");
    }
}

void ReceiveBridge::AfterGetObjects(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    HostObjectBuilderResult buildResult{};

    try
    {
        nlohmann::json receivedData = args.data[2];
        HostObjectBuilder hostObjectBuilder{};
        buildResult = hostObjectBuilder.Build(receivedData, modelCard.projectName, modelCard.modelName);
    }
    catch (const UserCancelledException&)
    {
        args.eventSource->Send("triggerCancel", modelCardId);
    }

    modelCard.bakedObjectIds = buildResult.bakedObjectIds;

    nlohmann::json res{};
    res["modelCardId"] = modelCardId;
    res["bakedObjectIds"] = buildResult.bakedObjectIds;
    res["conversionResults"] = buildResult.conversionResults;

    args.eventSource->Send("setModelReceiveResult", res);
}
