#include <exception>
#include <string>

class SpeckleConversionException : public std::exception {
private:
    std::string message;

public:
    // Constructor that accepts a custom error message
    explicit SpeckleConversionException(const std::string& msg)
        : message(msg) {}

    // Override the what() function to return the error message
    const char* what() const noexcept override {
        return message.c_str();
    }

    // Optionally, provide a default destructor
    ~SpeckleConversionException() override = default;
};
