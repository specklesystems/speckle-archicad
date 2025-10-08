#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <iostream>

std::vector<LayerData> HostToSpeckleConverter::GetLayers()
{
	std::vector<LayerData> layers;

	GS::UInt32 layerCount;
	CHECK_ERROR(ACAPI_Attribute_GetNum(API_LayerID, layerCount));

    GSErrCode err = NoError;
    // i <= 32768 is a hack because AC does not retrieve layerCount corretcly
    // there are layer attributes on much higher indices than layerCount
    for (UInt32 i = 1; i <= 32768; i++) 
    {
        API_Attribute layerAttr;
        BNZeroMemory(&layerAttr, sizeof(API_Attribute));
        layerAttr.header.typeID = API_LayerID;
        layerAttr.header.index = ACAPI_CreateAttributeIndex(i);

        err = ACAPI_Attribute_Get(&layerAttr);

        if (err == NoError)
        {
            LayerData layerData;
            GS::UniString layerName = layerAttr.header.name;
            std::string stdLayerName = layerName.ToCStr().Get();
            layerData.name = stdLayerName;
            layerData.id = std::to_string(i);
            layerData.hidden = layerAttr.layer.head.flags & APILay_Hidden;
            layers.push_back(layerData);
        }
    }

	return layers;
}
