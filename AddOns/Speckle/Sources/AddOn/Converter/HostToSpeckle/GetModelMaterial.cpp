#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <ModelMaterial.hpp>
#include <AttributeIndex.hpp>

Material HostToSpeckleConverter::GetModelMaterial(int materialIndex)
{
	auto acModel = ConverterUtils::GetArchiCadModel();

	ModelerAPI::AttributeIndex attributeIndex(ModelerAPI::AttributeIndex::MaterialIndex, materialIndex);
	ModelerAPI::Material modelerMaterial{};
	acModel.GetMaterial(attributeIndex, &modelerMaterial);

	auto color = modelerMaterial.GetSurfaceColor();
	Material material;
	material.diffuse = Utils::PackARGB(1.0, color.red, color.green, color.blue);
	material.opacity = 1.0 - (static_cast<double>(modelerMaterial.GetTransparency()) / 100.0);
	material.roughness = 1.0 - (static_cast<double>(modelerMaterial.GetShining()) / 10000.0);

	return material;
}
