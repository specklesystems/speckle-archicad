#include <exception>
#include <string>

class SpeckleConversionException : public std::exception {
private:
    std::string message;

public:
    explicit SpeckleConversionException(const std::string& msg)
        : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    ~SpeckleConversionException() override = default;
};
