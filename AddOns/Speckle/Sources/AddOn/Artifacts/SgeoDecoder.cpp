#include "SgeoDecoder.h"
#include "SgeoEncoder.h" // Crc32

#include <cstring>
#include <stdexcept>

namespace
{
    constexpr size_t HEADER_SIZE = 16;
    constexpr std::uint8_t PRIMITIVE_MESH = 0;
    constexpr std::uint16_t FLAG_QUANTIZED = 1 << 0;
    constexpr std::uint16_t FLAG_HAS_NORMALS = 1 << 4;
    constexpr std::uint16_t FLAG_HAS_UVS = 1 << 5;
    constexpr std::uint16_t FLAG_HAS_COLORS = 1 << 6;

    // Units.GetUnitFromEncoding (speckle-sharp-sdk); unknown encodings -> "none".
    std::string UnitsFromCode(std::uint16_t code)
    {
        switch (code)
        {
        case 1: return "mm";
        case 2: return "cm";
        case 3: return "m";
        case 4: return "km";
        case 5: return "in";
        case 6: return "ft";
        case 7: return "yd";
        case 8: return "mi";
        default: return "none";
        }
    }

    // Cursor over the little-endian body, mirroring the SDK decoder's Reader
    // (including the 8-byte alignment rule for f64 arrays after u32 runs).
    struct Reader
    {
        const std::uint8_t* data;
        size_t length;
        size_t pos;

        void Ensure(size_t bytes) const
        {
            if (pos + bytes > length)
                throw std::runtime_error("SGEO buffer truncated");
        }

        std::uint32_t U()
        {
            Ensure(4);
            std::uint32_t v;
            std::memcpy(&v, data + pos, 4);
            pos += 4;
            return v;
        }

        std::int32_t I()
        {
            Ensure(4);
            std::int32_t v;
            std::memcpy(&v, data + pos, 4);
            pos += 4;
            return v;
        }

        double D()
        {
            Ensure(8);
            double v;
            std::memcpy(&v, data + pos, 8);
            pos += 8;
            return v;
        }

        void Align8()
        {
            pos = (pos + 7) & ~static_cast<size_t>(7);
        }
    };
}

namespace SgeoDecoder
{
    bool TryDecodeMesh(const std::uint8_t* data, size_t length, DecodedMesh& mesh)
    {
        if (length < HEADER_SIZE)
            throw std::runtime_error("SGEO buffer too small to contain a header");
        if (std::memcmp(data, "SGEO", 4) != 0)
            throw std::runtime_error("SGEO magic mismatch");
        if (data[4] != 1)
            throw std::runtime_error("SGEO version " + std::to_string(data[4]) + " unsupported");

        const std::uint8_t primitiveType = data[5];
        std::uint16_t flags;
        std::memcpy(&flags, data + 6, 2);
        std::uint16_t unitsCode;
        std::memcpy(&unitsCode, data + 8, 2);
        std::uint32_t crc;
        std::memcpy(&crc, data + 12, 4);

        const std::uint32_t actual = SgeoEncoder::Crc32(data + HEADER_SIZE, length - HEADER_SIZE);
        if (actual != crc)
            throw std::runtime_error("SGEO CRC mismatch");

        if (primitiveType != PRIMITIVE_MESH || (flags & FLAG_QUANTIZED) != 0)
            return false;

        Reader r{ data, length, HEADER_SIZE };
        const std::uint32_t vCount = r.U();
        const std::uint32_t fCount = r.U();

        mesh.units = UnitsFromCode(unitsCode);
        mesh.vertices.resize(static_cast<size_t>(vCount) * 3);
        for (auto& v : mesh.vertices)
            v = r.D();
        mesh.faces.resize(fCount);
        for (auto& f : mesh.faces)
            f = r.I();

        // Normals/uvs are skipped (Align8 before each f64 array, same as the SDK
        // decoder) — colours follow but the XML/GDL path doesn't use them.
        if ((flags & FLAG_HAS_NORMALS) != 0)
        {
            r.Align8();
            r.Ensure(static_cast<size_t>(vCount) * 3 * 8);
            r.pos += static_cast<size_t>(vCount) * 3 * 8;
        }
        if ((flags & FLAG_HAS_UVS) != 0)
        {
            r.Align8();
            r.Ensure(static_cast<size_t>(vCount) * 2 * 8);
            r.pos += static_cast<size_t>(vCount) * 2 * 8;
        }
        (void)FLAG_HAS_COLORS;

        return true;
    }
}
