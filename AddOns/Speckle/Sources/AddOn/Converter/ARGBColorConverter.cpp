#include "ARGBColorConverter.h"
#include <algorithm>

uint32_t ARGBColorConverter::PackARGB(double A, double R, double G, double B)
{
    // Clamp the values to the range [0, 1]
    A = std::clamp(A, 0.0, 1.0);
    R = std::clamp(R, 0.0, 1.0);
    G = std::clamp(G, 0.0, 1.0);
    B = std::clamp(B, 0.0, 1.0);

    // Scale to the 0-255 range
    uint8_t a = static_cast<uint8_t>(A * 255);
    uint8_t r = static_cast<uint8_t>(R * 255);
    uint8_t g = static_cast<uint8_t>(G * 255);
    uint8_t b = static_cast<uint8_t>(B * 255);

    // Combine into a single 4-byte integer
    return (a << 24) | (r << 16) | (g << 8) | b;
}
