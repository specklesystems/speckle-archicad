#pragma once

#include <optional>
#include <string>
#include <vector>

#include "json.hpp"

// One flattened property leaf, produced by GetElementProperties and consumed
// by BundleWriter::AddProperties. `value` is a scalar or an array of scalars
// (arrays are joined into one comma-separated EAV row at write time) — never
// an object: nesting lives in the dot-separated `path`, and {name, value,
// units} parameter dicts are already collapsed into units/idn here.
//
// The vector preserves the exact emission order of the old nested-json walk
// (depth-first, alphabetical keys per level — nlohmann objects are sorted),
// so the eav/paths tables stay byte-identical to the tree-based pipeline.
struct EavLeaf
{
    std::string path; // full dot path, "properties." prefix included
    nlohmann::json value;
    std::optional<std::string> units;
    std::optional<std::string> internalDefinitionName;
};

using EavLeaves = std::vector<EavLeaf>;
