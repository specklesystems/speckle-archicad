#include "GuidGenerator.h"
#include <array>
#include <iomanip>
#include <random>
#include <sstream>

std::string GuidGenerator::NewGuid()
{
    std::array<unsigned char, 16> bytes{};
    std::random_device random;
    for (auto& byte : bytes)
        byte = static_cast<unsigned char>(random());

    bytes[6] = static_cast<unsigned char>((bytes[6] & 0x0F) | 0x40); // RFC 4122 version 4
    bytes[8] = static_cast<unsigned char>((bytes[8] & 0x3F) | 0x80); // RFC 4122 variant

    std::ostringstream result;
    result << std::hex << std::setfill('0');
    for (std::size_t index = 0; index < bytes.size(); ++index)
    {
        if (index == 4 || index == 6 || index == 8 || index == 10)
            result << '-';
        result << std::setw(2) << static_cast<unsigned int>(bytes[index]);
    }
    return result.str();
}
