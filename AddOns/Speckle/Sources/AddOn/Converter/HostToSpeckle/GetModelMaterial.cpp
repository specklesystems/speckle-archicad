#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "ARGBColorConverter.h"
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
	auto name = modelerMaterial.GetName().ToCStr().Get();

	Material material;
	material.name = name;
	material.diffuse = ARGBColorConverter::PackARGB(1.0, color.red, color.green, color.blue);
	double transparent = modelerMaterial.GetTransparency();
	double shiny = modelerMaterial.GetShining();
	material.opacity = 1.0 - transparent;
	material.roughness = 1.0 - (shiny / 100.0);
	
	return material;
}
