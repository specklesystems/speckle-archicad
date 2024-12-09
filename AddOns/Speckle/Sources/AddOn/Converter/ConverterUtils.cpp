#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <exp.h>
#include <Sight.hpp>


static GSErrCode GetCurrentWindowSight(void** sightPtr)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_Sight_GetCurrentWindowSight(sightPtr);
#elif defined(AC27)
	err = ACAPI_Sight_GetCurrentWindowSight(sightPtr);
#elif defined(AC26)
	err = ACAPI_3D_GetCurrentWindowSight(sightPtr);
#endif

	return err;
}

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
	CHECK_ERROR(GetCurrentWindowSight(&dummy));
	Modeler::SightPtr currentSightPtr((Modeler::Sight*)dummy); // init the shared ptr with the raw pointer
	ModelerAPI::Model archiCadModel{};
	Modeler::IAttributeReader* attrReader = ACAPI_Attribute_GetCurrentAttributeSetReader();
	CHECK_ERROR(EXPGetModel(currentSightPtr, &archiCadModel, attrReader));

	return archiCadModel;
}
