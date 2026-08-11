#include "SgeoEncoder.h"

#include <cstring>
#include <stdexcept>

namespace
{
    constexpr std::uint8_t SGEO_VERSION = 1;
    constexpr size_t HEADER_SIZE = 16;
    constexpr std::uint8_t PRIMITIVE_MESH = 0;
    constexpr std::uint16_t FLAG_HAS_COLORS = 1 << 6;

    // Units.GetEncodingFromUnit (speckle-sharp-sdk): mm=1 cm=2 m=3 km=4 in=5 ft=6 yd=7 mi=8, else 0.
    std::uint16_t UnitsCode(const std::string& units)
    {
        if (units == "mm") return 1;
        if (units == "cm") return 2;
        if (units == "m") return 3;
        if (units == "km") return 4;
        if (units == "in") return 5;
        if (units == "ft") return 6;
        if (units == "yd") return 7;
        if (units == "mi") return 8;
        return 0;
    }

    // Little-endian writers into a pre-sized buffer (single pass, no per-byte
    // push_back). x64/arm64 are little-endian, so the value memcpys are exact.
    std::uint8_t* WriteU32(std::uint8_t* out, std::uint32_t v)
    {
        std::memcpy(out, &v, 4);
        return out + 4;
    }

    std::uint8_t* WriteI32(std::uint8_t* out, std::int32_t v)
    {
        return WriteU32(out, static_cast<std::uint32_t>(v));
    }

    std::uint8_t* WriteF64(std::uint8_t* out, double v)
    {
        static_assert(sizeof(std::uint64_t) == sizeof(v), "double must be 64-bit");
        std::memcpy(out, &v, 8);
        return out + 8;
    }
}

namespace SgeoEncoder
{
    std::uint32_t Crc32(const std::uint8_t* data, size_t length)
    {
        static const auto table = []
        {
            std::vector<std::uint32_t> t(256);
            for (std::uint32_t i = 0; i < 256; i++)
            {
                std::uint32_t c = i;
                for (int k = 0; k < 8; k++)
                    c = (c & 1) != 0 ? 0xEDB88320u ^ (c >> 1) : c >> 1;
                t[i] = c;
            }
            return t;
        }();

        std::uint32_t crc = 0xFFFFFFFFu;
        for (size_t i = 0; i < length; i++)
            crc = table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
        return crc ^ 0xFFFFFFFFu;
    }

    std::vector<std::uint8_t> EncodeMesh(
        const std::vector<double>& vertices,
        const std::vector<int>& faces,
        const std::vector<int>& colors,
        const std::string& units)
    {
        if (vertices.size() % 3 != 0)
            throw std::runtime_error("SGEO mesh: vertices length must be a multiple of 3");

        const bool hasColors = !colors.empty();
        std::uint16_t flags = 0;
        if (hasColors)
            flags |= FLAG_HAS_COLORS;

        // Single pre-sized allocation: header + body written in place, one CRC
        // pass over the body region — no intermediate body buffer or re-copy.
        const size_t bodySize = 8 + vertices.size() * 8 + faces.size() * 4 + (hasColors ? colors.size() * 4 : 0);
        std::vector<std::uint8_t> blob(HEADER_SIZE + bodySize);

        std::uint8_t* p = blob.data() + HEADER_SIZE;
        p = WriteU32(p, static_cast<std::uint32_t>(vertices.size() / 3));
        p = WriteU32(p, static_cast<std::uint32_t>(faces.size()));
        for (double v : vertices)
            p = WriteF64(p, v);
        for (int f : faces)
            p = WriteI32(p, f);
        if (hasColors)
        {
            for (int c : colors)
                p = WriteI32(p, c);
        }

        const std::uint32_t crc = Crc32(blob.data() + HEADER_SIZE, bodySize);
        const std::uint16_t unitsCode = UnitsCode(units);

        std::uint8_t* h = blob.data();
        h[0] = 'S';
        h[1] = 'G';
        h[2] = 'E';
        h[3] = 'O';
        h[4] = SGEO_VERSION;
        h[5] = PRIMITIVE_MESH;
        h[6] = static_cast<std::uint8_t>(flags);
        h[7] = static_cast<std::uint8_t>(flags >> 8);
        h[8] = static_cast<std::uint8_t>(unitsCode);
        h[9] = static_cast<std::uint8_t>(unitsCode >> 8);
        h[10] = 0; // reserved
        h[11] = 0;
        WriteU32(h + 12, crc);
        return blob;
    }
}
