#include "RootObjectUnpacker.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"


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
    auto unpackedMeshes = UnpackMeshes(rootObject);
    std::vector<UnpackedElement> unpackedElements;

    for (auto& mesh : unpackedMeshes)
    {
        try
        {
            unpackedElements.push_back(UnpackedElement(mesh, materialTable));
        }
        catch (const std::exception& ex)
        {
            std::string msg = ex.what();
            std::cout << msg;
        }
    }

    return unpackedElements;
}
