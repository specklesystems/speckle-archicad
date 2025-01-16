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
        ArchicadObject archicadObject;

        try
        {
            archicadObject.applicationId = elemId;
            archicadObject.name = CONNECTOR.GetHostToSpeckleConverter().GetElementName(elemId);
            archicadObject.type = CONNECTOR.GetHostToSpeckleConverter().GetElementType(elemId);
            conversionResult.sourceType = archicadObject.type;
            conversionResult.sourceId = elemId;
            body = CONNECTOR.GetHostToSpeckleConverter().GetElementBody(elemId);
            bodies.push_back(body);
            archicadObject.displayValue = body;
            conversionResult.resultId = "";
            conversionResult.resultType = "Mesh";
            archicadObject.level = CONNECTOR.GetHostToSpeckleConverter().GetElementLevel(elemId);
            archicadObject.properties = CONNECTOR.GetHostToSpeckleConverter().GetElementProperties(elemId);

            if (rootObject.elements.find(archicadObject.level) == rootObject.elements.end())
            {
                Level level{};
                level.name = archicadObject.level;
                rootObject.elements[archicadObject.level] = level;
            }

            Level& level = rootObject.elements[archicadObject.level];
            if (level.elements.find(archicadObject.type) == level.elements.end())
            {
                ElementTypeCollection collection{};
                collection.name = archicadObject.type;
                level.elements[archicadObject.type] = collection;
            }

            ElementTypeCollection& elementTypeCollection = level.elements[archicadObject.type];
            elementTypeCollection.elements.push_back(archicadObject);
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
