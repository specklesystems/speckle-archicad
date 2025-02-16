#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

int SpeckleToHostConverter::CreateMaterial(const std::string& materialName, const Material& material)
{
    short transp = 100 - (short)(material.opacity * 100);

    API_Attribute materialAttr;
    BNZeroMemory(&materialAttr, sizeof(API_Attribute));

    materialAttr.header.typeID = API_MaterialID;
    CHCopyC(materialName.c_str(), materialAttr.header.name);

    // Define material properties
    materialAttr.material.ambientPc = 50;  // Ambient reflection
    materialAttr.material.diffusePc = 100;  // Diffuse reflection
    materialAttr.material.specularPc = 0; // Specular reflection
    materialAttr.material.transpPc = transp;   // Transparency
    materialAttr.material.shine = 0;     // Shininess
    materialAttr.material.emissionAtt = 0; // Emission
    materialAttr.material.surfaceRGB.f_red = 0.8;  // Red component
    materialAttr.material.surfaceRGB.f_green = 0.8; // Green component
    materialAttr.material.surfaceRGB.f_blue = 0.8; // Blue component

    // Optional: Add a texture (set materialAttr.material.texture file path)

    CHECK_ERROR(ACAPI_Attribute_Create(&materialAttr, nullptr));
    return materialAttr.header.index.ToInt32_Deprecated();
}
