#include "ModelCard.h"

bool ModelCard::IsSenderModelCard()
{
    return typeDiscriminator == "SenderModelCard";
}

bool ModelCard::IsReceiverModelCard()
{
    return typeDiscriminator == "ReceiverModelCard";
}

SenderModelCard ModelCard::AsSenderModelCard()
{
    if (IsSenderModelCard())
    {
        return data.get<SenderModelCard>();
    }
    else
    {
        throw std::runtime_error("ModelCard is not a SenderModelCard");
    }
}

ReceiverModelCard ModelCard::AsReceiverModelCard()
{
    if (IsReceiverModelCard())
    {
        return data.get<ReceiverModelCard>();
    }
    else
    {
        throw std::runtime_error("ModelCard is not a ReceiverModelCard");
    }
}

void to_json(nlohmann::json& j, const ModelCard& card)
{
    j["typeDiscriminator"] = card.typeDiscriminator;
    j["modelCardId"] = card.modelCardId;
    j["data"] = card.data;
}

void from_json(const nlohmann::json& j, ModelCard& card)
{
    card.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    card.modelCardId = j.at("modelCardId").get<std::string>();
    card.data = j;
}
