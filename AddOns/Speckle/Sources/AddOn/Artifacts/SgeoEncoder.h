#pragma once

#include <cstdint>
#include <string>
#include <vector>

// SGEO v1 encoder (mesh primitive) — the C++ mirror of the SDK's
// Speckle.Objects/Utils/SgeoEncoder.cs / SgeoFormat.cs. One opaque blob per
// geometry: a fixed 16-byte little-endian header ("SGEO", version 1,
// primitive type, flags, units code, CRC32 of the body) followed by the
// per-primitive body. Archicad sends meshes only, so only the Mesh primitive
// (type 0) is implemented; add the other primitives on demand.
//
// Mesh body layout (all little-endian, doubles IEEE-754):
//   u32 vertexCount (vertices.size()/3)
//   u32 faceCount   (faces.size() — the raw Speckle ngon face-list length)
//   f64 vertices[]  (x,y,z interleaved)
//   i32 faces[]     (Speckle ngon format: n, i0..i(n-1), ...)
//   i32 colors[]    (optional, flag HasColors; one ARGB int per vertex)
namespace SgeoEncoder
{
    // units: semantic Speckle unit string ("m", "mm", ...); encoded per Units.GetEncodingFromUnit.
    std::vector<std::uint8_t> EncodeMesh(
        const std::vector<double>& vertices,
        const std::vector<int>& faces,
        const std::vector<int>& colors,
        const std::string& units);

    // CRC-32 (IEEE 802.3, reflected 0xEDB88320) — the SGEO body integrity check.
    std::uint32_t Crc32(const std::uint8_t* data, size_t length);
}
