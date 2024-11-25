#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <exp.h>
#include <Sight.hpp>


API_Element ConverterUtils::GetElement(const std::string elemId)
{
	API_Element apiElem{};
	apiElem.header.guid = APIGuidFromString(elemId.c_str());
	ACAPI_Element_Get(&apiElem);

	return apiElem;
}

ModelerAPI::Model ConverterUtils::GetArchiCadModel()
{
	void* dummy = nullptr;
	CHECK_ERROR(ACAPI_Sight_GetCurrentWindowSight(&dummy));
	Modeler::SightPtr currentSightPtr((Modeler::Sight*)dummy); // init the shared ptr with the raw pointer
	ModelerAPI::Model archiCadModel{};
	Modeler::IAttributeReader* attrReader = ACAPI_Attribute_GetCurrentAttributeSetReader();
	CHECK_ERROR(EXPGetModel(currentSightPtr, &archiCadModel, attrReader));

	return archiCadModel;
}
