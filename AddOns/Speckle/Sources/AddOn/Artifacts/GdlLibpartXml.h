#pragma once

#include <map>
#include <string>
#include <vector>

// GDL library-part XML generation for LP_XMLConverter (`x2l`) — a verbatim C++
// port of the desktop service's ArchicadElement/ArchicadMesh/ArchicadMaterial
// (speckle-desktop-services/ArchicadReceive). One Speckle object becomes one
// <Symbol> XML whose 3D script carries the mesh as GDL VERT/EDGE/PGON commands
// and whose master (1D) script defines the referenced materials. Geometry is
// world-space, meters, fully baked — the resulting GSM is placed at the origin.
namespace GdlLibpartXml
{
    struct XmlMaterial
    {
        std::string name; // sanitized, unique per element
        double r = 0.8, g = 0.8, b = 0.8;
        double ambient = 0.5;
        double diffuse = 1.0;
        double specular = 0.0;
        double transparent = 0.0;             // 1 - opacity
        int shining = 0;                      // (1 - roughness) * 100
        int transparencyAttenuation = 0;
    };

    // Mesh in final coordinates (meters, world space). Faces use the Speckle
    // ngon format (n, i0..i(n-1), ...); ngons are fan-triangulated on emit.
    struct XmlMesh
    {
        std::vector<double> vertices;
        std::vector<int> faces;
        std::string materialName;
    };

    // Sanitize a name for GDL/material use: <>:"/\|?* -> '_' (matches the
    // desktop service's RemoveInvalidChars).
    std::string SanitizeName(const std::string& input);

    // The full <Symbol> XML for one object.
    std::string BuildSymbolXml(const std::vector<XmlMaterial>& materials, const std::vector<XmlMesh>& meshes);
}
