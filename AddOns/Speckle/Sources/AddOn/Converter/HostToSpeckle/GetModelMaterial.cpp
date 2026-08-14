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
	// UTF-8 explicitly: bundle parquet strings are UTF-8, CC_Default is the system codepage
	auto name = modelerMaterial.GetName().ToCStr(CC_UTF8).Get();

	Material material;
	material.name = name;
	material.diffuse = ARGBColorConverter::PackARGB(1.0, color.red, color.green, color.blue);
	double transparent = modelerMaterial.GetTransparency();
	double shiny = modelerMaterial.GetShining();
	material.opacity = 1.0 - transparent;
	material.roughness = 1.0 - (shiny / 100.0);

	// Emission is a real Archicad surface property; normalize an unlit (black)
	// surface to 0 so the bundle writes NULL rather than an explicit black.
	auto emission = modelerMaterial.GetEmissionColor();
	if (emission.red > 0.0 || emission.green > 0.0 || emission.blue > 0.0)
		material.emissive = ARGBColorConverter::PackARGB(1.0, emission.red, emission.green, emission.blue);

	return material;
}
