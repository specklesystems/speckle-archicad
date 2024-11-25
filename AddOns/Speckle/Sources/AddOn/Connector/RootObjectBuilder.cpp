#include "RootObjectBuilder.h"
#include "Connector.h"

RootObject RootObjectBuilder::GetRootObject(const std::vector<std::string>& elementIds)
{	
    RootObject rootObject;
    std::vector<ElementBody> bodies;

    for (const auto& elemId : elementIds)
    {
        auto body = CONNECTOR.hostToSpeckleConverter->GetElementBody(elemId);
        auto levelName = CONNECTOR.hostToSpeckleConverter->GetElementLevel(elemId);
        auto elementType = CONNECTOR.hostToSpeckleConverter->GetElementType(elemId);

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
