#include "HostObjectBuilder.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "RootObjectUnpacker.h"
#include "ReceiveConversionResult.h"
#include "UnpackedElement.h"
#include "LibpartBuilder.h"
#include "JsonFileWriter.h"
#include "Matrix_44.h"
#include "Units.h"
#include "ARGBColorConverter.h"
#include <set>

static std::string RemoveInvalidChars(const std::string& input) 
{
	std::string output;
	const std::string invalidChars = "<>:\"/\\|?*";

	for (char c : input) 
	{
		if (invalidChars.find(c) == std::string::npos) 
		{
			output += c;
		}
	}

	return output;
}

HostObjectBuilderResult HostObjectBuilder::Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName)
{
	std::ostringstream oss;
	oss << "Project " << projectName << " - Model " << modelName;
	std::string baseGroupName = oss.str();
	baseGroupName = RemoveInvalidChars(baseGroupName);

	//JsonFileWriter::WriteJsonToFile(rootObject, "C:\\t\\navis.json");

	auto bakedMaterials = BakeMaterials(rootObject, baseGroupName);
	auto buildResult = BakeObjects(rootObject, baseGroupName, bakedMaterials);

	return buildResult;
}

std::map<std::string, std::string> HostObjectBuilder::BakeMaterials(const nlohmann::json& rootObject, const std::string& baseGroupName)
{
	std::map<std::string, std::string> materialTable;
	std::map<std::string, int> createdMaterials;

	RootObjectUnpacker unpacker{};
	std::vector<RenderMaterialProxy> unpackedMaterialProxies;

	try
	{
		unpackedMaterialProxies = unpacker.UnpackRenderMaterialProxies(rootObject);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to unpack material proxies: " << ex.what();
	}

	for (const auto& proxy : unpackedMaterialProxies)
	{
		std::ostringstream oss;
		oss << baseGroupName << "_" << std::to_string(proxy.value.diffuse);
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
	}

	// create default mateiral
	std::string materialName = "speckle_default_material";
	int materialIndex = 0;
	Material defaultMaterial;
	defaultMaterial.diffuse = ARGBColorConverter::PackARGB(1, 0.6, 0.6, 0.6);
	try
	{
		materialIndex = CONNECTOR.GetSpeckleToHostConverter().CreateMaterial(defaultMaterial, materialName);
		createdMaterials[materialName] = materialIndex;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to create Archicad material: " << ex.what();
	}

	return materialTable;
}

static void CollectMeshesForInstance(const InstanceProxy& instance, std::vector<Mesh>& meshes, const std::map<std::string, UnpackedObject>& unpackedObjects, const std::map<std::string, InstanceProxy>& unpackedInstanceProxies, const std::map<std::string, InstanceDefinitionProxy>& unpackedInstanceDefinitionProxies, Matrix_44 trafo)
{
	trafo *= Matrix_44(instance.transform);
	auto appid = instance.applicationId;

	if (unpackedInstanceDefinitionProxies.find(instance.definitionId) != unpackedInstanceDefinitionProxies.end())
	{
		auto def = unpackedInstanceDefinitionProxies.at(instance.definitionId);	
		for (const auto& objectId : def.objects)
		{
			if (unpackedInstanceProxies.find(objectId) != unpackedInstanceProxies.end())
			{
				auto inst = unpackedInstanceProxies.at(objectId);
				CollectMeshesForInstance(inst, meshes, unpackedObjects, unpackedInstanceProxies, unpackedInstanceDefinitionProxies, trafo);
			}

			if (unpackedObjects.find(objectId) != unpackedObjects.end())
			{
				auto obj = unpackedObjects.at(objectId);
				for (auto& mesh : obj.displayValue)
				{
					if (mesh.applicationId == "0")
					{
						// hack to map object material to mesh
						mesh.applicationId = obj.applicationId;
					}
					mesh.ApplyTransform(trafo.AsVector());
					meshes.push_back(mesh);
				}
			}
		}
	}
}

HostObjectBuilderResult HostObjectBuilder::BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName, const std::map<std::string, std::string>& materialTable)
{
	LibpartBuilder libpartBuilder(baseGroupName);
	RootObjectUnpacker unpacker{};
	std::vector<UnpackedElement> unpackedElements;

	std::map<std::string, UnpackedObject> unpackedObjects;
	std::map<std::string, InstanceProxy> unpackedInstanceProxies;
	std::map<std::string, InstanceDefinitionProxy> unpackedInstanceDefinitionProxies;

	std::string incomingUnits = "m";

	try
	{
		unpackedObjects = unpacker.UnpackObjects(rootObject);
		unpackedInstanceProxies = unpacker.UnpackInstanceProxies(rootObject);
		unpackedInstanceDefinitionProxies = unpacker.UnpackInstanceDefinitionProxies(rootObject);
	}
	catch (const std::exception& ex)
	{
		std::string msg = ex.what();
		std::cout << "Failed to unpack elements: " << msg << baseGroupName;
	}

	std::set<std::string> instanceObjectIds;
	for (const auto& def : unpackedInstanceDefinitionProxies)
	{
		for (const auto& obj : def.second.objects)
		{
			instanceObjectIds.insert(obj);
		}
	}


	for (const auto& ip : unpackedInstanceProxies)
	{
		if (instanceObjectIds.find(ip.second.applicationId) != instanceObjectIds.end())
		{
			continue;
		}

		std::vector<Mesh> meshes;
		CollectMeshesForInstance(ip.second, meshes, unpackedObjects, unpackedInstanceProxies, unpackedInstanceDefinitionProxies, Matrix_44::Identity());

		if (meshes.size() > 0)
		{
			incomingUnits = meshes[0].units;
			unpackedElements.push_back(UnpackedElement(meshes, materialTable));
		}
	}

	for (auto& obj : unpackedObjects)
	{
		if (instanceObjectIds.find(obj.second.applicationId) != instanceObjectIds.end())
		{
			continue;
		}

		std::vector<Mesh> meshes;
		for (auto& mesh : obj.second.displayValue)
		{
			if (mesh.applicationId == "0")
			{
				// hack to map object material to mesh
				mesh.applicationId = obj.second.applicationId;
			}
			meshes.push_back(mesh);
		}

		if (meshes.size() > 0)
		{
			incomingUnits = meshes[0].units;
			unpackedElements.push_back(UnpackedElement(meshes, materialTable));
		}
	}

	// unit conversion
	auto hostAppUnits = CONNECTOR.GetHostToSpeckleConverter().GetWorkingUnits();
	double scaling = Units::GetConversionFactor(incomingUnits, hostAppUnits.workingLengthUnits);
	for (auto& elem : unpackedElements)
	{
		elem.ApplyScaling(scaling);
	}
	
	libpartBuilder.CreateLibParts(unpackedElements);
	libpartBuilder.PlaceLibparts();
	return { libpartBuilder.bakedObjectIds, libpartBuilder.conversionResults };
}

void HostObjectBuilder::GroupObjects(const std::vector<std::string>& objectIds)
{
	CONNECTOR.GetSpeckleToHostConverter().CreateGroup(objectIds);
}
