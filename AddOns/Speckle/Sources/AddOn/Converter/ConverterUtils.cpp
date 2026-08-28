#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <exp.h>
#include <Sight.hpp>
#include <ModelElement.hpp>

#include <algorithm>
#include <codecvt>
#include <cstring>
#include <locale>
#include <unordered_map>

namespace
{
    // ── per-send cache state (ACAPI main thread only) ────────────────────────

    struct ApiGuidHash
    {
        size_t operator()(const API_Guid& g) const
        {
            std::uint64_t a, b;
            std::memcpy(&a, &g, 8);
            std::memcpy(&b, reinterpret_cast<const char*>(&g) + 8, 8);
            return std::hash<std::uint64_t>()(a ^ (b * 0x9E3779B97F4A7C15ull));
        }
    };
    struct ApiGuidEqual
    {
        bool operator()(const API_Guid& x, const API_Guid& y) const
        {
            return std::memcmp(&x, &y, sizeof(API_Guid)) == 0;
        }
    };

    struct StoryRecord
    {
        short index = 0;
        short floorId = 0;
        double level = 0.0;
        std::string name;
    };

    bool g_cacheActive = false;
    unsigned g_cacheGeneration = 0;

    // cached 3D model (EXPGetModel once per send)
    bool g_modelValid = false;
    ModelerAPI::Model g_model{};

    // GUID -> 1-based model element index, built lazily on first geometry lookup
    bool g_modelIndexBuilt = false;
    std::unordered_map<API_Guid, Int32, ApiGuidHash, ApiGuidEqual> g_modelIndex;

    // last-element memo: the ~10 sub-extractors of one element each re-fetch it
    bool g_lastElemValid = false;
    std::string g_lastElemId;
    API_Element g_lastElem{};

    // attribute names by (type, index)
    std::unordered_map<std::uint64_t, std::string> g_attributeNames;

    // story table
    bool g_storiesValid = false;
    std::vector<StoryRecord> g_stories;

    void ClearSendCaches()
    {
        g_modelValid = false;
        g_model = ModelerAPI::Model{};
        g_modelIndexBuilt = false;
        g_modelIndex.clear();
        g_lastElemValid = false;
        g_lastElemId.clear();
        g_attributeNames.clear();
        g_storiesValid = false;
        g_stories.clear();
    }

#pragma warning(push)
#pragma warning(disable : 4996) // codecvt is deprecated but has no std replacement
    std::string WstringToString(const std::wstring& wideString)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wideString);
    }
#pragma warning(pop)

    std::vector<StoryRecord> FetchStories()
    {
        API_StoryInfo storyInfo{};
        CHECK_ERROR(ACAPI_ProjectSetting_GetStorySettings(&storyInfo));

        std::vector<StoryRecord> stories;
        const auto storyCount = storyInfo.lastStory - storyInfo.firstStory + 1;
        if (storyInfo.data != nullptr)
        {
            stories.reserve(storyCount);
            for (auto i = 0; i < storyCount; i++)
            {
                const auto& storyData = (*storyInfo.data)[i];
                StoryRecord record;
                record.index = storyData.index;
                record.floorId = storyData.floorId;
                record.level = storyData.level;
                record.name = WstringToString(std::wstring(storyData.uName));
                stories.push_back(std::move(record));
            }
            BMKillHandle(reinterpret_cast<GSHandle*>(&storyInfo.data));
        }
        return stories;
    }
}

ConverterUtils::SendCacheScope::SendCacheScope()
{
    ClearSendCaches();
    g_cacheActive = true;
    ++g_cacheGeneration;
}

ConverterUtils::SendCacheScope::~SendCacheScope()
{
    g_cacheActive = false;
    ClearSendCaches();
}

bool ConverterUtils::SendCacheActive()
{
    return g_cacheActive;
}

unsigned ConverterUtils::SendCacheGeneration()
{
    return g_cacheActive ? g_cacheGeneration : 0;
}

API_Element ConverterUtils::GetElement(const std::string elemId)
{
    if (g_cacheActive && g_lastElemValid && elemId == g_lastElemId)
        return g_lastElem;

    API_Element apiElem{};
    apiElem.header.guid = APIGuidFromString(elemId.c_str());
    ACAPI_Element_Get(&apiElem);

    if (g_cacheActive)
    {
        g_lastElemId = elemId;
        g_lastElem = apiElem;
        g_lastElemValid = true;
    }
    return apiElem;
}

ModelerAPI::Model ConverterUtils::GetArchiCadModel()
{
    if (g_cacheActive && g_modelValid)
        return g_model;

    void* dummy = nullptr;
    CHECK_ERROR(ACAPI_Sight_GetCurrentWindowSight(&dummy));
    Modeler::SightPtr currentSightPtr((Modeler::Sight*)dummy); // init the shared ptr with the raw pointer
    ModelerAPI::Model archiCadModel{};
    Modeler::IAttributeReader* attrReader = ACAPI_Attribute_GetCurrentAttributeSetReader();
    CHECK_ERROR(EXPGetModel(currentSightPtr, &archiCadModel, attrReader));

    if (g_cacheActive)
    {
        g_model = archiCadModel;
        g_modelValid = true;
    }
    return archiCadModel;
}

std::vector<Int32> ConverterUtils::GetModelElementIndices(ModelerAPI::Model& model, const std::set<API_Guid>& partIDs)
{
    std::vector<Int32> indices;

    if (g_cacheActive)
    {
        if (!g_modelIndexBuilt)
        {
            const Int32 nElements = model.GetElementCount();
            g_modelIndex.reserve(static_cast<size_t>(nElements));
            for (Int32 iElement = 1; iElement <= nElements; iElement++)
            {
                ModelerAPI::Element elem{};
                model.GetElement(iElement, &elem);
                // emplace keeps the first occurrence, matching the scan order below
                g_modelIndex.emplace(GSGuid2APIGuid(elem.GetElemGuid()), iElement);
            }
            g_modelIndexBuilt = true;
        }

        indices.reserve(partIDs.size());
        for (const auto& guid : partIDs)
        {
            const auto it = g_modelIndex.find(guid);
            if (it != g_modelIndex.end())
                indices.push_back(it->second);
        }
        std::sort(indices.begin(), indices.end()); // restore model iteration order
        return indices;
    }

    const Int32 nElements = model.GetElementCount();
    for (Int32 iElement = 1; iElement <= nElements; iElement++)
    {
        ModelerAPI::Element elem{};
        model.GetElement(iElement, &elem);
        const API_Guid apiGuid{ GSGuid2APIGuid(elem.GetElemGuid()) };
        if (partIDs.find(apiGuid) != partIDs.end())
            indices.push_back(iElement);
    }
    return indices;
}

ArchicadLevel ConverterUtils::GetStoryLevel(short floorInd)
{
    const std::vector<StoryRecord>* stories;
    std::vector<StoryRecord> local;
    if (g_cacheActive)
    {
        if (!g_storiesValid)
        {
            g_stories = FetchStories();
            g_storiesValid = true;
        }
        stories = &g_stories;
    }
    else
    {
        local = FetchStories();
        stories = &local;
    }

    ArchicadLevel level;
    std::string floorName;
    for (const auto& story : *stories)
    {
        if (story.index == floorInd)
        {
            floorName = story.name;
            level.elevation = story.level;
            level.floorId = story.floorId;
            break;
        }
    }

    level.name = std::to_string(floorInd) + ". " + (floorName.empty() ? "Story" : floorName);
    return level;
}

std::string ConverterUtils::GetAttributeName(API_AttributeIndex attributeIndex, API_AttrTypeID attributeType)
{
    const std::uint64_t key =
        (static_cast<std::uint64_t>(attributeType) << 32) |
        static_cast<std::uint32_t>(attributeIndex.ToInt32_Deprecated());
    if (g_cacheActive)
    {
        const auto it = g_attributeNames.find(key);
        if (it != g_attributeNames.end())
            return it->second;
    }

    API_Attribute attr;
    BNZeroMemory(&attr, sizeof(attr));
    attr.header.typeID = attributeType;
    attr.header.index = attributeIndex;
    ACAPI_Attribute_Get(&attr);

    std::string name = attr.header.name;
    if (g_cacheActive)
        g_attributeNames.emplace(key, name);
    return name;
}
