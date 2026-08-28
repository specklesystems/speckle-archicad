#include "ReceiveBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "Connector.h"
#include "UserCancelledException.h"
#include "LibpartPlacer.h"
#include "ArtifactReceiver.h"
#include "WinHttpClient.h"

#include "APIEnvir.h"
#include "ACAPinc.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ReceiveBridge::ReceiveBridge(IBrowserAdapter* browser)
{
    receiveBinding = std::make_unique<Binding>(
        "receiveBinding",
        std::vector<std::string>{ "Receive" },
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

static void DeletePreviouslyBakedElements(const std::vector<std::string>& bakedObjectIds)
{
    if (bakedObjectIds.empty())
        return;

    GS::Array<API_Guid> elementsToDelete;
    for (const auto& elemId : bakedObjectIds)
    {
        elementsToDelete.Push(APIGuidFromString(elemId.c_str()));
    }

    GSErrCode err = ACAPI_CallUndoableCommand("Delete elements",
        [&]() -> GSErrCode
        {
            return ACAPI_Element_Delete(elementsToDelete);
        });

    if (err != NoError)
    {
        std::cerr << "Failed to clean up elements" << std::endl;
    }
}

void ReceiveBridge::Receive(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string modelCardId = args.data[0].get<std::string>();
    ReceiverModelCard card = CONNECTOR.GetModelCardDatabase().GetModelCard(modelCardId).AsReceiverModelCard();

    std::string xmlConverterPath = CONNECTOR.GetHostToSpeckleConverter().GetApplicationFolder() + "\\LP_XMLConverter.exe";
    if (!fs::exists(xmlConverterPath))
    {
        throw std::runtime_error(
            "LP_XMLConverter.exe was not found next to Archicad (" + xmlConverterPath +
            ") — it is required to receive models.");
    }

    std::string token = CONNECTOR.GetAccountDatabase().GetTokenByAccountId(card.accountId);

    // Phases: download, read, generate, convert + LibpartPlacer's register + place.
    CONNECTOR.GetProcessWindow().Init("Receive", 6);

    std::string workingDir;
    try
    {
        auto http = std::make_shared<WinHttpClient>();
        ArtifactReceiver receiver(http, card.serverUrl, token);

        const std::string versionId =
            receiver.ResolveVersionId(card.projectId, card.modelId, card.selectedVersionId);

        ArtifactReceiver::Result received = receiver.Receive(
            card.projectId, card.modelId, versionId, xmlConverterPath, CONNECTOR.GetProcessWindow());
        workingDir = received.rootDir;

        // Replace the previous bake, then register + place the fresh GSMs.
        DeletePreviouslyBakedElements(card.bakedObjectIds);

        std::string baseGroupName =
            RemoveInvalidChars("Project " + card.projectName + " - Model " + card.modelName);

        LibpartPlacer libpartPlacer(baseGroupName);
        auto libpartIndices = libpartPlacer.RegisterLibpartsBatched(received.gsmFolder);
        int toPlace = static_cast<int>(libpartIndices.size());
        CONNECTOR.GetProcessWindow().SetNextProcessPhase("Placing Elements", toPlace);
        libpartPlacer.PlaceLibparts(libpartIndices);
        CONNECTOR.GetProcessWindow().Close();

        ClearDirectory(workingDir);

        card.bakedObjectIds = libpartPlacer.bakedObjectIds;

        nlohmann::json res{};
        res["modelCardId"] = modelCardId;
        res["bakedObjectIds"] = libpartPlacer.bakedObjectIds;
        res["conversionResults"] = received.conversionResults;
        args.eventSource->Send("setModelReceiveResult", res);
    }
    catch (const UserCancelledException&)
    {
        CONNECTOR.GetProcessWindow().Close();
        if (!workingDir.empty())
            ClearDirectory(workingDir);
        args.eventSource->Send("triggerCancel", modelCardId);
    }
    catch (...)
    {
        CONNECTOR.GetProcessWindow().Close();
        if (!workingDir.empty())
            ClearDirectory(workingDir);
        throw; // Binding::RunMethod turns this into a toast
    }
}
