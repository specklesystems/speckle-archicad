#pragma once

#include "json.hpp"
#include "EavLeaf.h"
#include "ElementBody.h"
#include "ArchicadLevel.h"
#include "ArchicadLayer.h"
#include "ObjectInstance.h"

struct ArchicadObject
{
    std::string name = "";
    std::string type = "";
    std::string level = "";
    std::string speckle_type = "Objects.Data.DataObject:Objects.Data.ArchicadObject";
    std::string applicationId = "";
    ElementBody displayValue;
    EavLeaves properties; // pre-flattened EAV rows (no nested json tree)
    std::vector<ArchicadObject> elements;
    ArchicadLevel levelInfo;
    ArchicadLayer layerInfo;

    // Populated (valid == true) only for GDL/library-part "Object" leaves that were
    // extracted as an instance. When valid, displayValue is left empty and the object
    // is emitted as an INSTANCE of a shared DEFINITION rather than baked geometry.
    ObjectInstance instance;
};
