// *****************************************************************************
// File:			PCMatrix.hpp
//
// Description:		Utility classes for point and matrix types, single precision
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	PCMATRIX_HPP
#define	PCMATRIX_HPP

#include "PointCloudDefinitions.hpp"

namespace	PC	{

class	Matrix;

// --- Point class using single floating precision -----------------------------

class	POINTCLOUD_DLL_EXPORT	Point
{
public:
	float	x, y, z, w;

	Point ();
	Point (float x, float y, float z, float w);

	Point	operator* (const Matrix& rightOp) const;
	Point	operator- (const Point& rightOp) const;

	void	Project ();
	Point	CalcProjected () const;
	float	Dot3 (const Point& rightOp) const;
	float	Length3 () const;

	// Fast
	void	GS_FORCE_INLINE Mul3 (const float (&rightOp)[4*4])
	{
		float tx = x*rightOp[0] + y*rightOp[1] + z*rightOp[2] + rightOp[3];
		float ty = x*rightOp[4] + y*rightOp[5] + z*rightOp[6] + rightOp[7];
		z = x*rightOp[8] + y*rightOp[9] + z*rightOp[10] + rightOp[11];
		x = tx;
		y = ty;
	}

	void	GS_FORCE_INLINE Mul4 (const float (&rightOp)[4*4])
	{
		float tx = x*rightOp[0] + y*rightOp[1] + z*rightOp[2] + rightOp[3];
		float ty = x*rightOp[4] + y*rightOp[5] + z*rightOp[6] + rightOp[7];
		float tz = x*rightOp[8] + y*rightOp[9] + z*rightOp[10] + rightOp[11];
		w = /*x*rightOp.data[12] + y*rightOp.data[13] +*/ z*rightOp[14] + rightOp[15];
		x = tx;
		y = ty;
		z = tz;
	}

	float	GS_FORCE_INLINE MulGetX (const float (rightOp)[4*4])
	{
		return x*rightOp[0] + y*rightOp[1] + z*rightOp[2] + rightOp[3];
	}

	float	GS_FORCE_INLINE MulGetY (const float (rightOp)[4*4])
	{
		return x*rightOp[4] + y*rightOp[5] + z*rightOp[6] + rightOp[7];
	}


	float	GS_FORCE_INLINE MulGetZ (const float (rightOp)[4*4])
	{
		return x*rightOp[8] + y*rightOp[9] + z*rightOp[10] + rightOp[11];
	}


	float	GS_FORCE_INLINE MulGetW (const float (rightOp)[4*4])
	{
		return /*x*rightOp.data[12] + y*rightOp.data[13] +*/ z*rightOp[14] + rightOp[15];
	}
};


// --- Matrix class using single floating precision ----------------------------

class	POINTCLOUD_DLL_EXPORT Matrix
{
public:
	float		data[4*4];

	Matrix ();
	Matrix (const float (&matrix)[4*4]);

	Matrix			operator* (const Matrix& rightOp) const;
	
	bool			operator== (const Matrix& rightOp) const;
	bool			operator!= (const Matrix& rightOp) const;

	bool			Invert ();
	void			Transpose ();
	bool			IsProjective () const;

	// static methods
	static Matrix	UnitMatrix ();
};

}


#endif