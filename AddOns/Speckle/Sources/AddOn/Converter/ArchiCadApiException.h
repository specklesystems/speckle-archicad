#pragma once

#include <exception>
#include <string>
#include "ErrorMessages.h"

class ArchiCadApiException : public std::exception
{
private:
    int errorCode;
    std::string message;

public:
    ArchiCadApiException(int code) 
        : errorCode(code), message(ErrorMessages::Get(code)) {}

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }

    int getErrorCode() const noexcept
    {
        return errorCode;
    }
};
