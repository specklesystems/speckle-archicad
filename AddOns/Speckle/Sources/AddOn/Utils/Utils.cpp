#include "Utils.h"

#include <windows.h>
#include <objbase.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#include "LoggerFactory.h"

std::string Utils::GenerateGUID()
{
    GUID guid;
    CoCreateGuid(&guid);

    // Format the GUID as a string
    char guidString[37]; // 36 characters + null terminator
    snprintf(guidString, sizeof(guidString),
        "%08x-%04x-%04x-%04x-%012llx",
        guid.Data1, guid.Data2, guid.Data3,
        (guid.Data4[0] << 8) | guid.Data4[1],
        *((unsigned long long*) & guid.Data4[2]));

    GET_LOGGER("utils")->Info("guidString");
    return std::string(guidString);
}

std::string Utils::GenerateGUID64()
{
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string guid;
    std::random_device rd;  // Non-deterministic random number generator
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(0, 63);

    for (int i = 0; i < 10; ++i)
    {
        guid += base64_chars[dis(gen)];
    }

    return guid;
}

void Utils::WriteJsonToFile(const nlohmann::json json, const std::string filePath)
{
    try
    {
        std::ofstream file(filePath);
        if (file.is_open())
        {
            file << std::setw(4) << json << std::endl; // Pretty-prints with an indent of 4 spaces
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
}

uint32_t Utils::PackARGB(double A, double R, double G, double B)
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
