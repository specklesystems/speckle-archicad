#include "Matrix_44.h"
#include <stdexcept>

Matrix_44::Matrix_44() : _data(16, 0.0)
{
    for (int i = 0; i < 4; ++i)
    {
        _data[i * 4 + i] = 1.0;
    }
}

Matrix_44::Matrix_44(const std::vector<double>& values)
{
    if (values.size() != 16)
    {
        throw std::invalid_argument("Matrix_44 must be initialized with 16 values.");
    }
    _data = values;
}

std::vector<double> Matrix_44::AsVector() const
{
    return _data;
}

Matrix_44 Matrix_44::operator*(const Matrix_44& other) const
{
    std::vector<double> result(16, 0.0);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            for (int k = 0; k < 4; ++k)
            {
                result[row * 4 + col] += _data[row * 4 + k] * other._data[k * 4 + col];
            }
        }
    }

    return Matrix_44(result);
}

Matrix_44& Matrix_44::operator*=(const Matrix_44& other)
{
    *this = *this * other;
    return *this;
}

Matrix_44 Matrix_44::Identity()
{
    return Matrix_44();
}
