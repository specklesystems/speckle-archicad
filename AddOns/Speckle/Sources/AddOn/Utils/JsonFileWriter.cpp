#include "JsonFileWriter.h"
#include <iostream>
#include <fstream>

void JsonFileWriter::WriteJsonToFile(const nlohmann::json json, const std::string filePath)
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
