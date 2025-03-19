#include "ROUnpacker.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "GuidGenerator.h"
#include "Matrix_44.h"
#include "LibpartBuilder.h"
#include "Units.h"

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

ROUnpacker::ROUnpacker(const Node* rootNode, const std::map<std::string, std::string>* materialTable, const std::string& baseGroupName) :
    rootNode(rootNode), 
    materialTable(materialTable),
    baseGroupName(baseGroupName)
{
    auto jstr = rootNode->data->dump();
    jsonSize = static_cast<int>(CountWordInJsonString(jstr, "speckle_type"));
}

void ROUnpacker::Unpack()
{
    int processPhases = 7;
    CONNECTOR.GetProcessWindow().Init("Receive", processPhases);

    // 1. traversing the root object
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Traversing Nodes", jsonSize);
    Traverse(rootNode);
    
    // 2. deserializing relevant items
    int dataSize = static_cast<int>(nodes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Deserializing Data", dataSize);
    Deserialize();

    // 3. expanding instances
    int instanceCount = static_cast<int>(instanceProxies.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Expanding Instances", instanceCount);
    ExpandInstances();


    // 4. processing nodes
    meshCountAfterTraversal = static_cast<int>(meshes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Processing Meshes", meshCountAfterTraversal);
    ProcessNodes();
    
    // 5. unpack elements
    int toUnpack = static_cast<int>(unpackedMeshes.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Unpacking Elements", toUnpack);
    UnpackElements();

    // 6. create LibParts
    LibpartBuilder builder(baseGroupName);
    int toCreate = static_cast<int>(unpackedElements.size());
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Creating Elements", toCreate);
    builder.CreateLibParts(unpackedElements);

    // 7. place LibParts
    CONNECTOR.GetProcessWindow().SetNextProcessPhase("Placing Elements", builder._elementCount);
    builder.PlaceLibparts();

    CONNECTOR.GetProcessWindow().Close();
}

void ROUnpacker::Traverse(const Node* node)
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
        for (const auto& [key, value] : node->data->items())
        {
            Traverse(new Node(value, node));
        }
    }
    else if (node->IsArray())
    {
        for (const auto& item : *node->data)
        {
            Traverse(new Node(item, node));
        }
    }
}

void ROUnpacker::Deserialize()
{
    int processed = 0;    
    
    for (const auto& [id, node] : nodes)
    {
        processed++;
        CONNECTOR.GetProcessWindow().SetProcessValue(processed);

        if (node->IsMesh())
        {
            meshes[node->id] = *node->data;
        }
        else if (node->IsColorProxy())
        {
            // TODO add
            //colors.push_back(*node->data);
        }
        else if (node->IsMaterialProxy())
        {
            renderMaterialProxies.push_back(*node->data);
        }
        else if (node->IsInstanceProxy())
        {
            instanceProxies[node->id] = *node->data;
        }
        else if (node->IsInstanceDefinitionProxy())
        {
            instanceDefinitionProxies[node->appId] = *node->data;
        }
    }
}

void ROUnpacker::ExpandInstances()
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

void ROUnpacker::ExpandInstance(const Node* node, bool addNew)
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
                    ExpandInstance(new Node(*childData, node));
                }
            }
        }
        else
        {
            for (const auto& [key, value] : node->data->items())
            {
                ExpandInstance(new Node(value, node));
            }
        }
    }
    else if (node->IsArray())
    {
        for (const auto& item : *node->data)
        {
            ExpandInstance(new Node(item, node));
        }
    }
}

void ROUnpacker::ProcessNodes()
{
    int processed = 0;
    for (const auto& node : meshNodes)
    {
        ProcessNode(node);
        processed++;
        CONNECTOR.GetProcessWindow().SetProcessValue(processed);
    }
}

void ROUnpacker::ProcessNode(const Node* node)
{
    bool processed = false;
    std::string lastId = "0";
    std::string meshId = "0";
    std::string materialName = "speckle_default_material";
    std::stack<std::vector<double>> transformations;
    
    while (!processed)
    {  
        if (materialName == "speckle_default_material")
        {
            auto it = materialTable->find(node->appId);
            if (it != materialTable->end())
            {
                materialName = it->second;
            }
        }
        
        if (node->IsMesh() && meshId == "0")
        {
            meshId = node->id;
        }

        if (node->IsInstanceProxy())
        {
            transformations.push(instanceProxies[node->id].transform);
        }

        if ((node->IsInstanceProxy() || node->IsGeometryObject()) || node->IsDataObject())
        {
            if (node->appId != "0")
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
    double scaling = Units::GetConversionFactor(mesh.units, hostAppUnits.workingLengthUnits);
    mesh.ApplyTransform(transform.AsVector());
    mesh.ApplyScaling(scaling);
    mesh.materialName = materialName;
    
    if (proxyDefinitionObjects.find(lastId) == proxyDefinitionObjects.end())
    {
        unpackedMeshes[lastId].push_back(mesh);
    }
}

void ROUnpacker::UnpackElements()
{
    std::map<std::string, std::string> mt;
    int unpacked = 0;
    for (const auto& [id, elem] : unpackedMeshes)
    {
        unpackedElements.push_back(UnpackedElement(elem, mt));
        unpacked++;
        CONNECTOR.GetProcessWindow().SetProcessValue(unpacked);
    }
}
