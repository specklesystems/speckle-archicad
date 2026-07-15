#pragma once
// nlohmann::json → PDict adapter — the bridge between Archicad's property JSON and the
// shared canonical EAV flatten (bundle-spec cpp/core/eav_flatten.h). The shared PVal
// model has no array type on purpose: Archicad's genuinely multi-valued properties
// (native List / Multiple-Choice Enumeration collections, IFC List / Enumerated) are
// collapsed HERE into one comma-separated string — same semantics as the retired
// DuckDB writer's JoinArrayScalars (skip null/non-scalar elements, drop the property
// when nothing scalar remains), but with the canonical cross-producer number
// formatting (eav::numToR, .NET "R") instead of std::to_chars.

#include "eav_flatten.h"
#include "json.hpp"

#include <memory>
#include <string>

namespace JsonToPDict
{
    inline bool IsScalar(const nlohmann::json& v)
    {
        return v.is_boolean() || v.is_string() || v.is_number();
    }

    inline PVal ScalarToPVal(const nlohmann::json& v)
    {
        if (v.is_boolean())
            return PVal::Bool(v.get<bool>());
        if (v.is_string())
            return PVal::Str(v.get<std::string>());
        if (v.is_number_float())
            return PVal::Dbl(v.get<double>());
        if (v.is_number_unsigned())
            return PVal::Long(static_cast<long long>(v.get<unsigned long long>()));
        return PVal::Long(v.get<long long>());
    }

    // Joins an array's scalar elements into one comma-separated string. Returns ""
    // for an empty / all-non-scalar array so the caller drops the property instead
    // of emitting a blank row.
    inline std::string JoinArrayScalars(const nlohmann::json& arr)
    {
        std::string out;
        bool first = true;
        for (const auto& el : arr)
        {
            if (el.is_null() || !IsScalar(el))
                continue;
            if (!first)
                out += ", ";
            out += eav::toText(ScalarToPVal(el));
            first = false;
        }
        return out;
    }

    inline std::shared_ptr<PDict> Convert(const nlohmann::json& obj)
    {
        auto dict = std::make_shared<PDict>();
        if (!obj.is_object())
            return dict;
        for (auto it = obj.begin(); it != obj.end(); ++it)
        {
            const nlohmann::json& val = it.value();
            if (val.is_null())
                continue; // the shared walk skips Null anyway
            if (val.is_object())
            {
                dict->set(it.key(), PVal::Map(Convert(val)));
                continue;
            }
            if (val.is_array())
            {
                const std::string joined = JoinArrayScalars(val);
                if (!joined.empty())
                    dict->set(it.key(), PVal::Str(joined));
                continue;
            }
            if (IsScalar(val))
                dict->set(it.key(), ScalarToPVal(val));
            // remaining non-scalars: nothing representable — skip
        }
        return dict;
    }
}
