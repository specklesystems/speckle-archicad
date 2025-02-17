#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <iostream>
#include <string>

/*int SpeckleToHostConverter::CreateMaterial(const Material& material, const std::string& baseGroupName)
{
    short transp = 100 - (short)(material.opacity * 100);

    API_Attribute materialAttr;
    BNZeroMemory(&materialAttr, sizeof(API_Attribute));

    materialAttr.header.typeID = API_MaterialID;
    std::string materialName = baseGroupName;
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
}*/

static void UnpackARGB(uint32_t argb, double& A, double& R, double& G, double& B)
{
    A = ((argb >> 24) & 0xFF) / 255.0;
    R = ((argb >> 16) & 0xFF) / 255.0;
    G = ((argb >> 8) & 0xFF) / 255.0;
    B = (argb & 0xFF) / 255.0;
}

int SpeckleToHostConverter::CreateMaterial(const Material& material, const std::string& materialName)
{
    short transp = 100 - static_cast<short>(material.opacity * 100);
    short shine = static_cast<short>((1.0 - material.roughness) * 100);

    API_Attribute materialAttr;
    BNZeroMemory(&materialAttr, sizeof(API_Attribute));
    materialAttr.header.typeID = API_MaterialID;

    CHCopyC(materialName.c_str(), materialAttr.header.name);

    // Unpack the color from ARGB format
    double A, R, G, B;
    UnpackARGB(material.diffuse, A, R, G, B);

    // Assign material properties
    materialAttr.material.ambientPc = 50;
    materialAttr.material.diffusePc = 100;
    materialAttr.material.specularPc = 0;
    materialAttr.material.transpPc = transp;
    materialAttr.material.shine = shine;
    materialAttr.material.emissionAtt = static_cast<short>(material.emissive * 100);

    materialAttr.material.surfaceRGB.f_red = static_cast<float>(R);
    materialAttr.material.surfaceRGB.f_green = static_cast<float>(G);
    materialAttr.material.surfaceRGB.f_blue = static_cast<float>(B);

    // Create the material
    CHECK_ERROR(ACAPI_Attribute_Create(&materialAttr, nullptr));
    return materialAttr.header.index.ToInt32_Deprecated();
}
