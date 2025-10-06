#pragma once

#include "json.hpp"
#include "ArchicadLevel.h"
#include "GuidGenerator.h"

struct LevelProxy
{
    std::string speckle_type = "Objects.Other.LevelProxy";
    std::string applicationId = GuidGenerator::NewGuid();
    ArchicadLevel value;
    std::vector<std::string> objects;
};

void to_json(nlohmann::json& j, const LevelProxy& proxy);
void from_json(const nlohmann::json& j, LevelProxy& proxy);
