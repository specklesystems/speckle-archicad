#include "RootObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"


RootObject RootObjectBuilder::GetRootObject(const std::vector<std::string>& elementIds, std::vector<SendConversionResult>& conversionResults)
{	
    RootObject rootObject;
    std::vector<ElementBody> bodies;

    for (const auto& elemId : elementIds)
    {
        SendConversionResult conversionResult{};
        

        ElementBody body{};
        std::string levelName;
        std::string elementType;

        try
        {
            conversionResult.sourceId = elemId;
            elementType = CONNECTOR.hostToSpeckleConverter->GetElementType(elemId);
            conversionResult.sourceType = elementType;
            body = CONNECTOR.hostToSpeckleConverter->GetElementBody(elemId);
            // TODO resultType, resultId
            conversionResult.resultType = "Mesh";
            conversionResult.resultId = "0";
            levelName = CONNECTOR.hostToSpeckleConverter->GetElementLevel(elemId);
        }
        catch (const ArchiCadApiException& e)
        {
            conversionResult.status = ConversionResultStatus::ERROR;
            conversionResult.error.message = e.what();
        }

        bodies.push_back(body);
        ModelElement modelElement;
        modelElement.displayValue = body;

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
        elementTypeCollection.elements.push_back(modelElement);

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
                renderMaterialProxy.value = CONNECTOR.hostToSpeckleConverter->GetModelMaterial(materialIndex);
                collectedProxies[materialIndex] = renderMaterialProxy;
            }

            collectedProxies[materialIndex].objects.push_back(mesh.second.applicationId);
        }
    }

    for (const auto& renderMaterialProxy : collectedProxies)
    {
        rootObject.renderMaterialProxies.push_back(renderMaterialProxy.second);
    }

    return rootObject;
}
