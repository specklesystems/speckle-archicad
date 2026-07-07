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

    void AppendU32(std::vector<std::uint8_t>& out, std::uint32_t v)
    {
        out.push_back(static_cast<std::uint8_t>(v));
        out.push_back(static_cast<std::uint8_t>(v >> 8));
        out.push_back(static_cast<std::uint8_t>(v >> 16));
        out.push_back(static_cast<std::uint8_t>(v >> 24));
    }

    void AppendI32(std::vector<std::uint8_t>& out, std::int32_t v)
    {
        AppendU32(out, static_cast<std::uint32_t>(v));
    }

    void AppendF64(std::vector<std::uint8_t>& out, double v)
    {
        std::uint64_t bits;
        static_assert(sizeof(bits) == sizeof(v), "double must be 64-bit");
        std::memcpy(&bits, &v, sizeof(bits));
        for (int i = 0; i < 8; i++)
            out.push_back(static_cast<std::uint8_t>(bits >> (8 * i)));
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

        std::vector<std::uint8_t> body;
        body.reserve(8 + vertices.size() * 8 + faces.size() * 4 + colors.size() * 4);
        AppendU32(body, static_cast<std::uint32_t>(vertices.size() / 3));
        AppendU32(body, static_cast<std::uint32_t>(faces.size()));
        for (double v : vertices)
            AppendF64(body, v);
        for (int f : faces)
            AppendI32(body, f);
        if (hasColors)
        {
            for (int c : colors)
                AppendI32(body, c);
        }

        const std::uint32_t crc = Crc32(body.data(), body.size());
        const std::uint16_t unitsCode = UnitsCode(units);

        std::vector<std::uint8_t> blob;
        blob.reserve(HEADER_SIZE + body.size());
        blob.push_back('S');
        blob.push_back('G');
        blob.push_back('E');
        blob.push_back('O');
        blob.push_back(SGEO_VERSION);
        blob.push_back(PRIMITIVE_MESH);
        blob.push_back(static_cast<std::uint8_t>(flags));
        blob.push_back(static_cast<std::uint8_t>(flags >> 8));
        blob.push_back(static_cast<std::uint8_t>(unitsCode));
        blob.push_back(static_cast<std::uint8_t>(unitsCode >> 8));
        blob.push_back(0); // reserved
        blob.push_back(0);
        AppendU32(blob, crc);
        blob.insert(blob.end(), body.begin(), body.end());
        return blob;
    }
}
