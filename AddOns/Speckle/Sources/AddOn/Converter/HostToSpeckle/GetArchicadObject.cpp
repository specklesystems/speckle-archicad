#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"


ArchicadObject HostToSpeckleConverter::GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult, bool includeProperties)
{
	ArchicadObject archicadObject{};
    
    archicadObject.applicationId = elemId;
    archicadObject.name = GetElementName(elemId);
    archicadObject.type = GetElementType(elemId);
    archicadObject.levelInfo = GetElementLevel(elemId);
    archicadObject.level = archicadObject.levelInfo.name;
    archicadObject.layerInfo = GetElementLayer(elemId);
    conversionResult.sourceType = archicadObject.type;
    conversionResult.sourceId = elemId;

    archicadObject.elements = GetElementChildren(elemId, includeProperties);
    if (archicadObject.elements.empty())
    {
        // GDL/library-part objects are extracted as instances (shared DEFINITION +
        // per-placement transform). Anything else — or an object that fails to extract
        // as an instance — falls back to baked world-coordinate geometry.
        bool instanced = false;
        if (archicadObject.type == "Object")
        {
            ObjectInstance instance = GetObjectInstance(elemId);
            if (instance.valid)
            {
                archicadObject.instance = std::move(instance);
                instanced = true;
            }
        }

        if (!instanced)
            archicadObject.displayValue = GetElementBody(elemId);
    }

    archicadObject.properties = includeProperties ? GetElementProperties(elemId) : EavLeaves{};

    conversionResult.resultId = "";
    conversionResult.resultType = "ArchicadObject";

	return archicadObject;
}
