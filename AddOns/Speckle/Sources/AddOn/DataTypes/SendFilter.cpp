#include "SendFilter.h"

bool SendFilter::IsArchicadSelectionFilter()
{
    return typeDiscriminator == "ArchicadSelectionFilter";
}

bool SendFilter::IsArchicadElementTypeFilter()
{
    return typeDiscriminator == "ArchicadElementTypeFilter";
}

ArchicadSelectionFilter SendFilter::AsArchicadSelectionFilter()
{
    if (IsArchicadSelectionFilter())
    {
        return data.get<ArchicadSelectionFilter>();
    }
    else
    {
        throw std::runtime_error("SendFilter is not an ArchicadSelectionFilter");
    }
}

ArchicadElementTypeFilter SendFilter::AsArchicadElementTypeFilter()
{
    if (IsArchicadElementTypeFilter())
    {
        return data.get<ArchicadElementTypeFilter>();
    }
    else
    {
        throw std::runtime_error("SendFilter is not an ArchicadElementTypeFilter");
    }
}

std::vector<std::string> SendFilter::GetSelectedObjectIds()
{
    if (IsArchicadSelectionFilter())
    {
        return AsArchicadSelectionFilter().selectedObjectIds;
    }
    else if (IsArchicadElementTypeFilter())
    {
        auto filter = AsArchicadElementTypeFilter();
        filter.UpdateSelectedObjectIds();
        return filter.selectedObjectIds;
    }
    else
    {
        throw std::runtime_error("SendFilter has invalid typeDiscriminator");
    }
}

void to_json(nlohmann::json& j, const SendFilter& filter)
{
    j = filter.data;
}

void from_json(const nlohmann::json& j, SendFilter& filter)
{
    filter.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    filter.data = j;
}
