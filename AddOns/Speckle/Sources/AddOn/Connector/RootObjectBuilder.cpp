#include "RootObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"


RootObject RootObjectBuilder::GetRootObject(const std::vector<std::string>& elementIds, std::vector<SendConversionResult>& conversionResults)
{	
    RootObject rootObject;
    std::vector<ElementBody> bodies;

    for (const auto& elemId : elementIds)
    {
        SendConversionResult conversionResult{};   

        ElementBody body{};
        std::string elementName;
        std::string levelName;
        std::string elementType;
        std::map<std::string, std::string> elementClassifications;
        nlohmann::json dimensionalProperties;
        nlohmann::json materialQuantities;

        try
        {
            elementName = CONNECTOR.GetHostToSpeckleConverter().GetElementName(elemId);
            elementType = CONNECTOR.GetHostToSpeckleConverter().GetElementType(elemId);
            elementClassifications = CONNECTOR.GetHostToSpeckleConverter().GetElementClassifications(elemId);
            conversionResult.sourceType = elementType;
            conversionResult.sourceId = elemId;
            body = CONNECTOR.GetHostToSpeckleConverter().GetElementBody(elemId);
            conversionResult.resultId = "";
            conversionResult.resultType = "Mesh";
            levelName = CONNECTOR.GetHostToSpeckleConverter().GetElementLevel(elemId);
            dimensionalProperties = CONNECTOR.GetHostToSpeckleConverter().GetElementProperties(elemId, PropertyFilter::Dimensional);
            materialQuantities = CONNECTOR.GetHostToSpeckleConverter().GetElementMaterialQuantities(elemId);

        }
        catch (const ArchiCadApiException& ae)
        {
            conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
            conversionResult.error.message = ae.what();
        }
        catch (const SpeckleConversionException& se)
        {
            conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
            conversionResult.error.message = se.what();
        }

        bodies.push_back(body);
        ArchicadObject archicadObject;
        archicadObject.name = elementName;
        archicadObject.type = elementType;
        archicadObject.classifications = elementClassifications;
        archicadObject.level = levelName;
        archicadObject.applicationId = elemId;
        archicadObject.displayValue = body;
        archicadObject.properties["Dimensional Properties"] = dimensionalProperties;
        archicadObject.properties["Material Quantities"] = materialQuantities;

        if (rootObject.elements.find(levelName) == rootObject.elements.end())
        {
            Level level{};
            level.name = levelName;
            rootObject.elements[levelName] = level;
        }

        Level& level = rootObject.elements[levelName];
        if (level.elements.find(elementType) == level.elements.end())
        {
            ElementTypeCollection collection{};
            collection.name = elementType;
            level.elements[elementType] = collection;
        }

        ElementTypeCollection& elementTypeCollection = level.elements[elementType];
        elementTypeCollection.elements.push_back(archicadObject);

        conversionResults.push_back(conversionResult);
    }

    std::map<int, RenderMaterialProxy> collectedProxies;
    for (const auto& body : bodies)
    {
        for (const auto& mesh : body.meshes)
        {
            int materialIndex = mesh.second.materialIndex;
            if (collectedProxies.find(materialIndex) == collectedProxies.end())
            {
                RenderMaterialProxy renderMaterialProxy;
                renderMaterialProxy.value = CONNECTOR.GetHostToSpeckleConverter().GetModelMaterial(materialIndex);
                collectedProxies[materialIndex] = renderMaterialProxy;
            }

            collectedProxies[materialIndex].objects.push_back(mesh.second.applicationId);
        }
    }

    for (const auto& renderMaterialProxy : collectedProxies)
    {
        rootObject.renderMaterialProxies.push_back(renderMaterialProxy.second);
    }

    auto projectInfo = CONNECTOR.GetHostToSpeckleConverter().GetProjectInfo();
    rootObject.name = projectInfo.name;

    return rootObject;
}
