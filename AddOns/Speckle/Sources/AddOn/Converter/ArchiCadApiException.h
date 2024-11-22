#pragma once

#include <exception>
#include <string>

class ArchiCadApiException : public std::exception
{
private:
    int errorCode;
    std::string message;

public:
    ArchiCadApiException(int code) : errorCode(code), message("ArchiCad API Exception: Error code " + std::to_string(errorCode)) {}

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }

    int getErrorCode() const noexcept
    {
        return errorCode;
    }
};
