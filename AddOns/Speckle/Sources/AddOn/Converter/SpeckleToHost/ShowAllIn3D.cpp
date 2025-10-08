#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <iostream>

void SpeckleToHostConverter::ShowAllIn3D()
{
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
}

void SpeckleToHostConverter::ShowIn3D()
{
	API_WindowInfo currentWindowInfo = {};
	ACAPI_Window_GetCurrentWindow(&currentWindowInfo);
	if (currentWindowInfo.typeID != APIWind_3DModelID)
	{
		API_WindowInfo newWindowInfo = {};
		newWindowInfo.typeID = APIWind_3DModelID;
		CHECK_ERROR(ACAPI_Window_ChangeWindow(&newWindowInfo));
	}
}

void SpeckleToHostConverter::SetLayerVisibility(const std::vector<int>& layerIndices, bool visibility)
{
	for (const auto i : layerIndices)
	{
		API_Attribute layerAttr;
		BNZeroMemory(&layerAttr, sizeof(API_Attribute));
		layerAttr.header.typeID = API_LayerID;
		layerAttr.header.index = ACAPI_CreateAttributeIndex(i);

		GSErrCode err = NoError;
		err = ACAPI_Attribute_Get(&layerAttr);

		if (err == NoError)
		{
			layerAttr.layer.head.flags = visibility ? 0 : APILay_Hidden;
			ACAPI_Attribute_Modify(&layerAttr, nullptr);
		}
	}
}
