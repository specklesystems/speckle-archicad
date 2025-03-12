#pragma once

#include <vector>

class Matrix_44
{
private:
    std::vector<double> _data;

public:
    Matrix_44();
    Matrix_44(const std::vector<double>& values);

    std::vector<double> AsVector() const;

    Matrix_44 operator*(const Matrix_44& other) const;
    Matrix_44& operator*=(const Matrix_44& other);

    static Matrix_44 Identity();
};
