#include "LoggerFactory.h"

#include <filesystem>
#include <iostream>

int main(int, char** argv)
{
    const auto underAFile = std::filesystem::absolute(argv[0]) / L"Speckle.log";
    try
    {
        GET_LOGGER_F("Unopenable", underAFile.wstring())->Error("must not throw");
    }
    catch (const std::exception& ex)
    {
        std::cerr << "FAIL: logging to an unopenable file threw: " << ex.what() << '\n';
        return 1;
    }
    std::cout << "PASS: logging to an unopenable file is a no-op\n";
}
