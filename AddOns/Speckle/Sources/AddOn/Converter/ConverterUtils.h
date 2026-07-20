#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ArchicadLevel.h"

#include <Model.hpp>
#include <set>
#include <string>
#include <vector>

class ConverterUtils
{
public:
    static API_Element GetElement(const std::string elemId);
    static ModelerAPI::Model GetArchiCadModel();
    static std::string GetAttributeName(API_AttributeIndex attributeIndex, API_AttrTypeID attributeType);

    // 1-based Modeler element indices whose GUID is in partIDs, ascending (model
    // iteration order — geometry emission order depends on it). With an active
    // SendCacheScope this is an index lookup per GUID; without one it falls back
    // to the full model scan the extractors used to inline.
    static std::vector<Int32> GetModelElementIndices(ModelerAPI::Model& model, const std::set<API_Guid>& partIDs);

    // Level info for an element's floor index. The story table (one
    // ACAPI_ProjectSetting_GetStorySettings + name conversions) is cached per send.
    static ArchicadLevel GetStoryLevel(short floorInd);

    // Per-send cache scope (RAII). While one is active, the accessors above plus
    // GetElement (last-element memo) and GetAttributeName reuse per-send caches
    // instead of re-fetching invariant state per element. The converters run on
    // the ACAPI main thread only, and the model/attributes/stories cannot change
    // mid-send (the process window is modal) — so caching them is safe.
    // Other file-local converter caches key off SendCacheGeneration().
    class SendCacheScope
    {
    public:
        SendCacheScope();
        ~SendCacheScope();
        SendCacheScope(const SendCacheScope&) = delete;
        SendCacheScope& operator=(const SendCacheScope&) = delete;
    };
    static bool SendCacheActive();
    // 0 when no scope is active; otherwise a value unique to the current scope.
    static unsigned SendCacheGeneration();
};
