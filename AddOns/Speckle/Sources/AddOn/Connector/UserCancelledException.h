#pragma once

#include <exception>
#include <string>

class UserCancelledException : public std::exception
{
private:
    std::string message;

public:
    UserCancelledException(const std::string& message)
        : message(message) {}

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }
};
