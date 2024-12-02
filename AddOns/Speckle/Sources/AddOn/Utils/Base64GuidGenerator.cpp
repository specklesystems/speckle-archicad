#include "Base64GuidGenerator.h"
#include <random>


std::string Base64GuidGenerator::NewGuid()
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
