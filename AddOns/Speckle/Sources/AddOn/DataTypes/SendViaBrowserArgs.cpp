#include "SendViaBrowserArgs.h"

void to_json(nlohmann::json& j, const SendViaBrowserArgs& args)
{
    j["modelCardId"] = args.modelCardId;
    j["projectId"] = args.projectId;
    j["modelId"] = args.modelId;
    j["token"] = args.token;
    j["serverUrl"] = args.serverUrl;
    j["accountId"] = args.accountId;
    //j["message"] = args.message;
    //j["sendObject"] = args.sendObject;
    //j["sendConversionResults"] = args.sendConversionResults;
    j["totalBatch"] = args.totalBatch;
    j["currentBatch"] = args.currentBatch;
    j["referencedObjectId"] = args.referencedObjectId;
    j["batch"] = args.batch;
}

void from_json(const nlohmann::json& j, SendViaBrowserArgs& args)
{
    args.modelCardId = j.at("modelCardId").get<std::string>();
    args.projectId = j.at("projectId").get<std::string>();
    args.modelId = j.at("modelId").get<std::string>();
    args.token = j.at("token").get<std::string>();
    args.serverUrl = j.at("serverUrl").get<std::string>();
    args.accountId = j.at("accountId").get<std::string>();
    //args.message = j.at("message").get<std::string>();
    //args.sendObject = j.at("sendObject");;
    //args.sendConversionResults = j.at("sendConversionResults");
    args.totalBatch = j.at("totalBatch").get<int>();
    args.currentBatch = j.at("currentBatch").get<int>();
    args.referencedObjectId = j.at("referencedObjectId").get<std::string>();
    args.batch = j.at("batch").get<std::string>();
}
