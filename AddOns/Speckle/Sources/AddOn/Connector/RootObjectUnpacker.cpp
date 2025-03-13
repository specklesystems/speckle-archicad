#include "RootObjectUnpacker.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "GuidGenerator.h"


static void CollectMaterialProxies(const nlohmann::json& data, std::vector<RenderMaterialProxy>& proxies)
{
    if (data.is_object())
    {
        auto it = data.find("speckle_type");
        if (it != data.end() && it->is_string() && *it == "Objects.Other.RenderMaterialProxy")
        {
            proxies.push_back(data);
        }

        for (const auto& [key, value] : data.items())
        {
            CollectMaterialProxies(value, proxies);
        }
    }
    else if (data.is_array())
    {
        for (const auto& item : data)
        {
            CollectMaterialProxies(item, proxies);
        }
    }
}

std::vector<RenderMaterialProxy> RootObjectUnpacker::UnpackRenderMaterialProxies(const nlohmann::json& rootObject)
{
    std::vector<RenderMaterialProxy> proxies;
    CollectMaterialProxies(rootObject, proxies);
    return proxies;
}

static void CollectInstanceProxies(const nlohmann::json& data, std::vector<InstanceProxy>& proxies)
{
    if (data.is_object())
    {
        auto it = data.find("speckle_type");
        if (it != data.end() && it->is_string() && *it == "Speckle.Core.Models.Instances.InstanceProxy")
        {
            proxies.push_back(data);
        }

        for (const auto& [key, value] : data.items())
        {
            CollectInstanceProxies(value, proxies);
        }
    }
    else if (data.is_array())
    {
        for (const auto& item : data)
        {
            CollectInstanceProxies(item, proxies);
        }
    }
}

std::map<std::string, InstanceProxy> RootObjectUnpacker::UnpackInstanceProxies(const nlohmann::json& rootObject)
{
    std::vector<InstanceProxy> proxies;
    CollectInstanceProxies(rootObject, proxies);

    std::map<std::string, InstanceProxy> proxyMap;
    for (const auto& p : proxies)
    {
        proxyMap[p.applicationId] = p;
    }
    return proxyMap;
}

static void CollectInstanceDefinitionProxies(const nlohmann::json& data, std::vector<InstanceDefinitionProxy>& proxies)
{
    if (data.is_object())
    {
        auto it = data.find("speckle_type");
        if (it != data.end() && it->is_string() && *it == "Speckle.Core.Models.Instances.InstanceDefinitionProxy")
        {
            proxies.push_back(data);
        }

        for (const auto& [key, value] : data.items())
        {
            CollectInstanceDefinitionProxies(value, proxies);
        }
    }
    else if (data.is_array())
    {
        for (const auto& item : data)
        {
            CollectInstanceDefinitionProxies(item, proxies);
        }
    }
}

std::map<std::string, InstanceDefinitionProxy> RootObjectUnpacker::UnpackInstanceDefinitionProxies(const nlohmann::json& rootObject)
{
    std::vector<InstanceDefinitionProxy> proxies;
    CollectInstanceDefinitionProxies(rootObject, proxies);

    std::map<std::string, InstanceDefinitionProxy> proxyMap;
    for (const auto& p : proxies)
    {
        proxyMap[p.applicationId] = p;
    }
    return proxyMap;
}

static void CollectMeshesFlat(const nlohmann::json& data, std::vector<Mesh>& meshes)
{
    if (data.is_object())
    {
        auto it = data.find("speckle_type");
        if (it != data.end() && it->is_string() && *it == "Objects.Geometry.Mesh")
        {
            meshes.push_back(data);
        }

        for (const auto& [key, value] : data.items())
        {
            CollectMeshesFlat(value, meshes);
        }
    }
    else if (data.is_array())
    {
        for (const auto& item : data)
        {
            CollectMeshesFlat(item, meshes);
        }
    }
}

std::vector<Mesh> RootObjectUnpacker::UnpackMeshesFlat(const nlohmann::json& rootObject)
{
    std::vector<Mesh> meshes;
    CollectMeshesFlat(rootObject, meshes);
    return meshes;
}

static void CollectMeshes(const nlohmann::json& j, std::vector<std::vector<Mesh>>& result)
{
    if (j.is_object()) 
    {
        if (j.contains("displayValue") && j["displayValue"].is_array()) 
        {
            std::vector<Mesh> meshes;
            for (const auto& item : j["displayValue"]) 
            {
                if (item.is_object() && item.contains("speckle_type") && item["speckle_type"].is_string()) 
                {
                    if (item["speckle_type"] == "Objects.Geometry.Mesh") 
                    {
                        meshes.emplace_back(item);
                    }
                }
            }
            if (!meshes.empty()) 
            {
                result.push_back(std::move(meshes));
            }
        }

        for (const auto& [key, value] : j.items()) 
        {
            CollectMeshes(value, result);
        }
    }
    else if (j.is_array()) 
    {
        for (const auto& item : j)
        {
            CollectMeshes(item, result);
        }
    }
}

std::vector<std::vector<Mesh>> RootObjectUnpacker::UnpackMeshes(const nlohmann::json& rootObject)
{
    std::vector<std::vector<Mesh>> meshes;
    CollectMeshes(rootObject, meshes);
    return meshes;
}

std::vector<UnpackedElement> RootObjectUnpacker::UnpackElements(const nlohmann::json& rootObject, const std::map<std::string, std::string>& materialTable)
{
    auto unpackedObjects = UnpackObjects(rootObject);
    std::vector<UnpackedElement> unpackedElements;

    for (auto& obj : unpackedObjects)
    {
        try
        {
            unpackedElements.push_back(UnpackedElement(obj.second.displayValue, materialTable));
        }
        catch (const std::exception& ex)
        {
            std::string msg = ex.what();
            std::cout << msg;
        }
    }

    return unpackedElements;
}

static void CollectObjects(const nlohmann::json& j, std::vector<UnpackedObject>& collected)
{
    if (j.is_object())
    {
        if (j.contains("displayValue") && j["displayValue"].is_array())
        {
            UnpackedObject unpackedObj;

            if (j.contains("applicationId") && j["applicationId"].is_string()) 
            {
                unpackedObj.applicationId = j["applicationId"].get<std::string>();
            }
            else
            {
                unpackedObj.applicationId = GuidGenerator::NewGuid();
            }

            for (const auto& item : j["displayValue"])
            {
                if (item.is_object() && item.contains("speckle_type") && item["speckle_type"].is_string())
                {
                    if (item["speckle_type"] == "Objects.Geometry.Mesh")
                    {
                        unpackedObj.displayValue.emplace_back(item);
                    }
                }
            }

            if (!unpackedObj.displayValue.empty())
            {
                collected.push_back(std::move(unpackedObj));
            }
        }

        for (const auto& [key, value] : j.items())
        {
            CollectObjects(value, collected);
        }
    }
    else if (j.is_array())
    {
        for (const auto& item : j)
        {
            CollectObjects(item, collected);
        }
    }
}

std::map<std::string, UnpackedObject> RootObjectUnpacker::UnpackObjects(const nlohmann::json& rootObject)
{
    std::vector<UnpackedObject> objects;
    CollectObjects(rootObject, objects);

    if (objects.size() == 0)
    {
        // Hack for SketchUp
        // TODO remove when C# graph traversal is implemented in C++
        auto meshes = UnpackMeshesFlat(rootObject);
        for (const auto& m : meshes)
        {
            UnpackedObject u;
            u.applicationId = m.applicationId;
            u.displayValue.push_back(m);
            objects.push_back(u);
        }
    }
    
    std::map<std::string, UnpackedObject> objectsMap;
    for (const auto& obj : objects)
    {
        objectsMap[obj.applicationId] = obj;
    }
    return objectsMap;
}
