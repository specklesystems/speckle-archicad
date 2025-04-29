#include "ReceiveBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "HostObjectBuilder.h"
#include "UserCancelledException.h"
#include "LibpartPlacer.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ReceiveBridge::ReceiveBridge(IBrowserAdapter* browser)
{
    receiveBinding = std::make_unique<Binding>(
        "receiveBinding",
        std::vector<std::string>{ "Receive", "AfterGetObjects", "afterGsmConverter" },
        browser,
        this
    );
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
    else if (args.methodName == "afterGsmConverter")
    {
        AfterGsmConverter(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

static bool ClearDirectory(const std::string& path)
{
    try
    {
        if (!fs::exists(path))
        {
            std::cerr << "Path does not exist: " << path << std::endl;
            return false;
        }

        // Normalize and make sure it's not a root directory
        fs::path normalizedPath = fs::canonical(path);
        if (normalizedPath == normalizedPath.root_path())
        {
            std::cerr << "Refusing to remove root directory: " << normalizedPath << std::endl;
            return false;
        }

        std::uintmax_t removed = fs::remove_all(normalizedPath);

        if (removed == 0)
        {
            std::cerr << "Nothing was removed: " << normalizedPath << std::endl;
            return false;
        }

        return true;
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "General error: " << e.what() << std::endl;
        return false;
    }
}

void ReceiveBridge::Receive(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard card = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    std::string xmlConverterPath = CONNECTOR.GetHostToSpeckleConverter().GetApplicationFolder() + "\\LP_XMLConverter.exe";

    nlohmann::json receiveArgs;
    receiveArgs["modelId"] = card.modelId;
    receiveArgs["projectId"] = card.projectId;
    receiveArgs["accountId"] = card.accountId;
    receiveArgs["modelCardId"] = card.modelCardId;
    receiveArgs["selectedVersionId"] = card.selectedVersionId;

    // Check if the LP_XMLConverter.exe file exists
    if (fs::exists(xmlConverterPath))
    {
        receiveArgs["xmlConverterPath"] = xmlConverterPath;
        receiveArgs["endpointVersion"] = "v1";
        args.eventSource->Send("receiveByDesktopService", receiveArgs);
    }
    else
    {
        // falling back to receive by browser
        args.eventSource->Send("receiveByBrowser", receiveArgs);
    }
}

static std::string RemoveInvalidChars(const std::string& input)
{
    std::string output;
    const std::string invalidChars = "<>:\"/\\|?*";

    for (char c : input) 
    {
        output += (invalidChars.find(c) == std::string::npos) ? c : '-';
    }

    return output;
}

void ReceiveBridge::AfterGsmConverter(const RunMethodEventArgs& args)
{
    if (args.data.size() < 3)
        throw std::invalid_argument("Too few arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard modelCard = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    // cleaning up previously placed elements
    if (modelCard.bakedObjectIds.size() > 0)
    {
        GS::Array<API_Guid> elementsToDelete;
        for (const auto& elemId : modelCard.bakedObjectIds)
        {
            elementsToDelete.Push(APIGuidFromString(elemId.c_str()));
        }

        GSErrCode err = ACAPI_CallUndoableCommand("Delete elements",
            [&]() -> GSErrCode {
                return ACAPI_Element_Delete(elementsToDelete);
            });

        if (err != NoError)
        {
            std::cout << "Failed to clean up elements";
        }
    }

    std::string xmlFolderPath = args.data[2].get<std::string>();
    std::string gsmFolderPath = xmlFolderPath + "\\_output";

    std::ostringstream oss;
    oss << "Project " << modelCard.projectName << " - Model " << modelCard.modelName;
    std::string baseGroupName = oss.str();
    baseGroupName = RemoveInvalidChars(baseGroupName);

    int processPhases = 2;
    CONNECTOR.GetProcessWindow().Init("Receive", processPhases);

    LibpartPlacer libpartPlacer(baseGroupName);
    auto libpartIndices = libpartPlacer.RegisterLibpartsBatched(gsmFolderPath);
    int toPlace = static_cast<int>(libpartIndices.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Placing Elements", toPlace);
    libpartPlacer.PlaceLibparts(libpartIndices);
    CONNECTOR.GetProcessWindow().Close();
    ClearDirectory(xmlFolderPath);

    modelCard.bakedObjectIds = libpartPlacer.bakedObjectIds;

    nlohmann::json res{};
    res["modelCardId"] = modelCardId;
    res["bakedObjectIds"] = libpartPlacer.bakedObjectIds;
    res["conversionResults"] = libpartPlacer.conversionResults;

    args.eventSource->Send("setModelReceiveResult", res);
}

// this is the fallback case when we cannot receive via desktop service
void ReceiveBridge::AfterGetObjects(const RunMethodEventArgs& args)
{
    if (args.data.size() < 3)
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
