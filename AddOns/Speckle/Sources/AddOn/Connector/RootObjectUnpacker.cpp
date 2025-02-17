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

static void CollectMeshes(const nlohmann::json& data, std::vector<Mesh>& meshes)
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
            CollectMeshes(value, meshes);
        }
    }
    else if (data.is_array())
    {
        for (const auto& item : data)
        {
            CollectMeshes(item, meshes);
        }
    }
}

std::vector<Mesh> RootObjectUnpacker::UnpackMeshes(const nlohmann::json& rootObject)
{
    std::vector<Mesh> meshes;
    CollectMeshes(rootObject, meshes);
    return meshes;
}
