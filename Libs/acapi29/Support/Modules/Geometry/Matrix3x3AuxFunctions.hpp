
#ifndef MATRIX3X3AUXFUNCTIONS_HPP
#define MATRIX3X3AUXFUNCTIONS_HPP

#include "Matrix.hpp"
#include "Vector3D.hpp"


namespace Geometry {

	// Calculate the sum of dyadic products, the result is in the second variable
	GEOMETRY_DLL_EXPORT	void		CalcDyadicSumMatrix3x3 (const GS::Array<Point3D>& coords, Geometry::Matrix<3, 3, double>& M);

	// Calculate the Square of the Frobenius norm of the given matrix
	GEOMETRY_DLL_EXPORT	double		Matrix3x3FrobeniusNormSquare (const Geometry::Matrix<3, 3, double>& M);

	// return value is the smallest eigenvalue of a symmetric, positive semidefinite 3x3 matrix
	GEOMETRY_DLL_EXPORT	double		CalcSmallestEigenVal_SymmPosSemiDefMatrix3x3 (const Geometry::Matrix<3, 3, double>& M);

	// return value is the biggest eigenvalue of a symmetric, positive semidefinite 3x3 matrix
	GEOMETRY_DLL_EXPORT	double		CalcLargestEigenVal_SymmPosSemiDefMatrix3x3 (const Geometry::Matrix<3, 3, double>& M);

	// Calculate the induced norm of the given matrix
	// see Wikipedia:  https://en.wikipedia.org/wiki/Matrix_norm
	GEOMETRY_DLL_EXPORT	double		CalcMatrix3x3Norm (const Geometry::Matrix<3, 3, double>& M);

	// Search eigenvector of a symmetric 3x3 matrix for given eigenvalue
	// return value is an eigenvector for the given eigenvector (not unique, neither in direction neither up to scalar multiple)
	GEOMETRY_DLL_EXPORT	Vector3D	CalcEigenVect_SymmMatrix3x3 (const Geometry::Matrix<3, 3, double>& M, const double eigenValue);
}

#endif //MATRIX3X3AUXFUNCTIONS_HPP