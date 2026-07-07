#pragma once

#include <cstdint>
#include <string>
#include <vector>

// SGEO v1 decoder (mesh primitive) — the inverse of SgeoEncoder and the C++
// mirror of the SDK's SgeoDecoder.TryDecodeMesh. Only the Mesh primitive
// (type 0) is decoded; other primitives (lines/curves/points) return false —
// the Archicad receive bakes surface geometry only, matching the old
// desktop-service behaviour.
namespace SgeoDecoder
{
    struct DecodedMesh
    {
        std::vector<double> vertices; // flat x,y,z
        std::vector<int> faces;       // Speckle ngon format: n, i0..i(n-1), ...
        std::string units;            // semantic Speckle unit string ("m", "mm", ...)
    };

    // Returns false for non-SGEO buffers, non-mesh primitives, or the (unsupported)
    // quantized layout. Throws std::runtime_error on a corrupt buffer (bad magic/
    // version/CRC/truncation).
    bool TryDecodeMesh(const std::uint8_t* data, size_t length, DecodedMesh& mesh);
}
