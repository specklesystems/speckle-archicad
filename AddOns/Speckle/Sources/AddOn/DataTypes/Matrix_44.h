#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix_44 
{
private:
    std::vector<double> data;

public:
    // Default constructor - creates identity matrix
    Matrix_44() : data(16, 0.0) {
        for (int i = 0; i < 4; ++i) {
            data[i * 4 + i] = 1.0;
        }
    }

    // Constructor
    Matrix_44(const std::vector<double>& values) {
        if (values.size() != 16) {
            throw std::invalid_argument("Matrix44 must be initialized with 16 values.");
        }
        data = values;
    }

    // Getter function
    std::vector<double> get() const {
        return data;
    }

    // Overloaded multiplication operator
    Matrix_44 operator*(const Matrix_44& other) const {
        std::vector<double> result(16, 0.0);

        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                for (int k = 0; k < 4; ++k) {
                    result[row * 4 + col] += data[row * 4 + k] * other.data[k * 4 + col];
                }
            }
        }

        return Matrix_44(result);
    }

    // Overloaded *= operator
    Matrix_44& operator*=(const Matrix_44& other) {
        *this = *this * other;
        return *this;
    }

    // Print function for debugging
    void print() const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << data[i * 4 + j] << " ";
            }
            std::cout << std::endl;
        }
    }
};