#include "RootObjectUnpacker.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "GuidGenerator.h"
#include "Matrix_44.h"
#include "Units.h"
#include "ARGBColorConverter.h"

#include <stack>

size_t CountWordInJsonString(const std::string& jsonStr, const std::string& word) 
{
    size_t count = 0;
    size_t pos = jsonStr.find(word, 0);

    while (pos != std::string::npos) 
    {
        count++;
        pos = jsonStr.find(word, pos + word.length());
    }

    return count;
}

RootObjectUnpacker::RootObjectUnpacker(const std::shared_ptr<Node> rootNode, const std::string& baseGroupName) :
    rootNode(rootNode), 
    materialTable(materialTable),
    baseGroupName(baseGroupName),
    libPartBuilder(baseGroupName)
{
    // TODO remove this data->dump() later, adds noticable time to receive
    // only added this to implement process feedback on traversal
    // we need to know how many objects we have to traverse
    auto jstr = rootNode->data.dump();
    jsonSize = static_cast<int>(CountWordInJsonString(jstr, "speckle_type"));
}

HostObjectBuilderResult RootObjectUnpacker::GetHostObjectBuilderResult()
{
    return { libPartBuilder.bakedObjectIds, libPartBuilder.conversionResults };
}

void RootObjectUnpacker::Unpack()
{
    int processPhases = 8;
    CONNECTOR.GetProcessWindow().Init("Receive", processPhases);

    // 1. traversing the root object
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Traversing Nodes", jsonSize);
    Traverse(rootNode);
    
    // 2. deserializing relevant items
    int dataSize = static_cast<int>(nodes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Deserializing Data", dataSize);
    Deserialize();

    // 3. bake materials
    int materialProxyCount = static_cast<int>(renderMaterialProxies.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Baking Materials", materialProxyCount);
    BakeDefaultMaterial();
    BakeMaterials();
    // we don't support colorproxies in archicad for now
    // meshes will always have the material assigned or the default material
    //int colorProxyCount = static_cast<int>(colorProxies.size());
    //BakeColors();

    // 4. expanding instances
    int instanceCount = static_cast<int>(instanceProxies.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Expanding Instances", instanceCount);
    ExpandInstances();

    // 5. processing nodes
    meshCountAfterTraversal = static_cast<int>(meshes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Processing Meshes", meshCountAfterTraversal);
    ProcessNodes();
    
    // 6. unpack elements
    int toUnpack = static_cast<int>(unpackedMeshes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Unpacking Elements", toUnpack);
    UnpackElements();

    // 7. create LibParts
    int toCreate = static_cast<int>(unpackedElements.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Creating Elements", toCreate);
    libPartBuilder.CreateLibParts(unpackedElements);

    // 8. place LibParts
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Placing Elements", libPartBuilder._elementCount);
    libPartBuilder.PlaceLibparts();

    CONNECTOR.GetProcessWindow().Close();
}

void RootObjectUnpacker::Traverse(const std::shared_ptr<Node>& node)
{
    if (node->IsSpeckleType())
    {
        nodes[node->id] = node;
        nodesByAppId[node->appId] = node;

        if (node->IsMesh())
        {
            meshNodes.push_back(node);
        }

        traversed++;
        CONNECTOR.GetProcessWindow().SetProcessValue(traversed);

        for (const auto& [key, value] : node->data.items())
        {
            Traverse(std::make_shared<Node>(value, node));
        }
    }
    else if (node->IsArray())
    {
        for (const auto& item : node->data)
        {
            Traverse(std::make_shared<Node>(item, node));
        }
    }
}

void RootObjectUnpacker::Deserialize()
{
    int processed = 0;    
    
    for (const auto& [id, node] : nodes)
    {
        processed++;
        CONNECTOR.GetProcessWindow().SetProcessValue(processed);

        if (node->IsMesh())
        {
            meshes[node->id] = node->data;
        }
        // we don't support colorproxies in archicad for now
        // meshes will always have the material assigned or the default material
        /*else if (node->IsColorProxy())
        {
            colorProxies.push_back(node->data);
        }*/
        else if (node->IsMaterialProxy())
        {
            renderMaterialProxies.push_back(node->data);
        }
        else if (node->IsInstanceProxy())
        {
            instanceProxies[node->id] = node->data;
        }
        else if (node->IsInstanceDefinitionProxy())
        {
            instanceDefinitionProxies[node->appId] = node->data;
        }
    }
}

void RootObjectUnpacker::BakeMaterials()
{
    std::map<std::string, int> createdMaterials;
    int baked = 0;

    for (const auto& proxy : renderMaterialProxies)
    {
        std::ostringstream oss;
        oss << baseGroupName << "_" << proxy.value.name;
        std::string materialName = oss.str();

        int materialIndex = 0;
        if (createdMaterials.find(materialName) != createdMaterials.end())
        {
            materialIndex = createdMaterials[materialName];
        }
        else
        {
            try
            {
                materialIndex = CONNECTOR.GetSpeckleToHostConverter().CreateMaterial(proxy.value, materialName);
                createdMaterials[materialName] = materialIndex;
            }
            catch (const std::exception& ex)
            {
                std::cout << "Failed to create Archicad material: " << ex.what();
            }
        }

        for (const auto& elementId : proxy.objects)
        {
            materialTable[elementId] = materialName;
        }

        baked++;
        CONNECTOR.GetProcessWindow().SetProcessValue(baked);
    } 
}

void RootObjectUnpacker::BakeColors()
{
    std::map<std::string, int> createdColors;
    int baked = 0;

    for (const auto& proxy : colorProxies)
    {
        std::ostringstream oss;
        oss << baseGroupName << "_" << std::to_string(proxy.value);
        std::string materialName = oss.str();

        int materialIndex = 0;
        if (createdColors.find(materialName) != createdColors.end())
        {
            materialIndex = createdColors[materialName];
        }
        else
        {
            try
            {
                materialIndex = CONNECTOR.GetSpeckleToHostConverter().CreateMaterial(proxy, materialName);
                createdColors[materialName] = materialIndex;
            }
            catch (const std::exception& ex)
            {
                std::cout << "Failed to create Archicad material: " << ex.what();
            }
        }

        for (const auto& elementId : proxy.objects)
        {
            colorTable[elementId] = materialName;
        }

        baked++;
        CONNECTOR.GetProcessWindow().SetProcessValue(baked);
    }
}

void RootObjectUnpacker::BakeDefaultMaterial()
{
    std::string materialName = "speckle_default_material";
    Material defaultMaterial;
    defaultMaterial.diffuse = ARGBColorConverter::PackARGB(1, 0.6, 0.6, 0.6);
    try
    {
        CONNECTOR.GetSpeckleToHostConverter().CreateMaterial(defaultMaterial, materialName);
    }
    catch (const std::exception& ex)
    {
        std::cout << "Failed to create Archicad material: " << ex.what();
    }
}

void RootObjectUnpacker::ExpandInstances()
{
    int expanded = 0;
    for (const auto& [id, node] : nodes)
    {
        if (node->IsInstanceProxy())
        {
            ExpandInstance(node, false);
            expanded++;
            CONNECTOR.GetProcessWindow().SetProcessValue(expanded);
        }
    }
}

void RootObjectUnpacker::ExpandInstance(const std::shared_ptr<Node>& node, bool addNew)
{
    if (node->IsSpeckleType())
    {
        if (addNew && node->IsMesh())
        {
            meshNodes.push_back(node);
        }

        if (node->IsInstanceProxy())
        {
            InstanceProxy proxy = instanceProxies[node->id];
            auto definitionId = proxy.definitionId;
            InstanceDefinitionProxy defProxy = instanceDefinitionProxies[definitionId];

            for (const auto& obj : defProxy.objects)
            {
                proxyDefinitionObjects.insert(obj);

                auto it = nodesByAppId.find(obj);
                if (it != nodesByAppId.end() && it->second)
                {
                    auto childData = it->second->data;
                    ExpandInstance(std::make_shared<Node>(childData, node));
                }
            }
        }
        else
        {
            for (const auto& [key, value] : node->data.items())
            {
                ExpandInstance(std::make_shared<Node>(value, node));
            }
        }
    }
    else if (node->IsArray())
    {
        for (const auto& item : node->data)
        {
            ExpandInstance(std::make_shared<Node>(item, node));
        }
    }
}

void RootObjectUnpacker::ProcessNodes()
{
    int processed = 0;
    for (const auto& node : meshNodes)
    {
        ProcessNode(node);
        processed++;
        CONNECTOR.GetProcessWindow().SetProcessValue(processed);
    }
}

void RootObjectUnpacker::ProcessNode(const std::shared_ptr<Node>& child)
{
    const std::string defaultMaterialName = "speckle_default_material";
    const std::string defaultId = "0";
    bool processed = false;
    std::string lastId = defaultId;
    std::string meshId = defaultId;
    std::string materialName = defaultMaterialName;
    //std::string colorName = defaultMaterialName;
    std::stack<std::vector<double>> transformations;
    std::shared_ptr<Node> node = child;
    
    while (!processed)
    {  
        if (materialName == defaultMaterialName)
        {
            auto it = materialTable.find(node->appId);
            if (it != materialTable.end())
            {
                materialName = it->second;
            }
        }

        /*if (colorName == defaultMaterialName)
        {
            auto it = colorTable.find(node->appId);
            if (it != colorTable.end())
            {
                colorName = it->second;
            }
        }*/
        
        if (node->IsMesh() && meshId == defaultId)
        {
            meshId = node->id;
        }

        if (node->IsInstanceProxy())
        {
            transformations.push(instanceProxies[node->id].transform);
        }

        if ((node->IsInstanceProxy() || node->IsGeometryObject()) || node->IsDataObject())
        {
            if (node->appId != defaultId)
            {
                lastId = node->appId;
            }
        }

        node = node->parent;
        if (node == nullptr)
        {
            processed = true;
        }
    }

    auto transform = Matrix_44::Identity();

    while (!transformations.empty())
    {
        transform *= Matrix_44(transformations.top());
        transformations.pop();
    }

    Mesh mesh = meshes[meshId];
    auto hostAppUnits = CONNECTOR.GetHostToSpeckleConverter().GetWorkingUnits();
    double scaling = Units::GetConversionFactor(mesh.units, "m");
    mesh.ApplyTransform(transform.AsVector());
    mesh.ApplyScaling(scaling);
    // we don't support colorproxies in archicad for now
    // meshes will always have the material assigned or the default material
    //mesh.materialName = (materialName != defaultMaterialName) ? materialName : colorName;
    mesh.materialName = materialName;
    
    if (proxyDefinitionObjects.find(lastId) == proxyDefinitionObjects.end())
    {
        unpackedMeshes[lastId].push_back(mesh);
    }
}

void RootObjectUnpacker::UnpackElements()
{
    int unpacked = 0;
    for (const auto& [id, elem] : unpackedMeshes)
    {
        unpackedElements.push_back(ArchicadElement(elem));
        unpacked++;
        CONNECTOR.GetProcessWindow().SetProcessValue(unpacked);
    }
}
