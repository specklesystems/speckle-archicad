#include "RootObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"


RootObject RootObjectBuilder::GetRootObject(const std::vector<std::string>& elementIds, std::vector<SendConversionResult>& conversionResults, bool includeProperties)
{	
    RootObject rootObject;
    std::vector<ElementBody> bodies;

    CONNECTOR.GetProcessWindow().Init("Converting elements", static_cast<int>(elementIds.size()));
    int elemCount = 0;
    for (const auto& elemId : elementIds)
    {
        elemCount++;
        CONNECTOR.GetProcessWindow().SetProcessValue(elemCount);
        SendConversionResult conversionResult{};   

        try
        {
            auto archicadObject = CONNECTOR.GetHostToSpeckleConverter().GetArchicadObject(elemId, conversionResult, includeProperties);
            
            if (archicadObject.displayValue.meshes.empty())
            {
                for (const auto& subElement : archicadObject.elements)
                {
                    bodies.push_back(subElement.displayValue);
                }
            }
            else
            {
                bodies.push_back(archicadObject.displayValue);
            }

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

        if (CONNECTOR.GetProcessWindow().IsProcessCanceled())
        {
            CONNECTOR.GetProcessWindow().Close();
            throw UserCancelledException("The user cancelled the send operation");
        }
    }

    CONNECTOR.GetProcessWindow().Init("Converting render materials", static_cast<int>(elementIds.size()));
    std::map<int, RenderMaterialProxy> collectedProxies;
    for (const auto& body : bodies)
    {
        for (const auto& mesh : body.meshes)
        {
            int materialIndex = mesh.materialIndex;
            if (collectedProxies.find(materialIndex) == collectedProxies.end())
            {
                RenderMaterialProxy renderMaterialProxy;
                renderMaterialProxy.value = CONNECTOR.GetHostToSpeckleConverter().GetModelMaterial(materialIndex);
                collectedProxies[materialIndex] = renderMaterialProxy;
            }

            collectedProxies[materialIndex].objects.push_back(mesh.applicationId);
        }

        if (CONNECTOR.GetProcessWindow().IsProcessCanceled())
        {
            CONNECTOR.GetProcessWindow().Close();
            throw std::exception("The user cancelled the operation");
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
