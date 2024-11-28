// *****************************************************************************
// File:			PCDMatrix.hpp
//
// Description:		Utility classes for point and matrix types, double precision
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	PCDMATRIX_HPP
#define	PCDMATRIX_HPP

#include "PointCloudDefinitions.hpp"

namespace	PC	{

class DMatrix;

// --- Point class using double floating precision -----------------------------

class	POINTCLOUD_DLL_EXPORT	DPoint
{
public:
	double	x, y, z, w;

	DPoint ();
	DPoint (double x, double y, double z, double w);

	DPoint	operator* (const DMatrix& rightOp) const;
	
	DPoint	operator- (const DPoint& rightOp) const;
	DPoint	operator* (const DPoint& rightOp) const;

	void	Project ();
	DPoint	CalcProjected () const;
	double	Dot3 (const DPoint& rightOp) const;
	double	Length3 () const;
};


// --- Matrix class using double floating precision ----------------------------

class POINTCLOUD_DLL_EXPORT		DMatrix
{
public:
	double		data[4*4];

	DMatrix ();
	DMatrix (const float (&matrix)[4*4]);
	DMatrix (const double (&matrix)[4*4]);

	DMatrix			operator* (const DMatrix& rightOp) const;
	PC::DPoint		operator* (const PC::DPoint& rightOp) const;
	
	double			operator ()(int row, int col) const;

	bool			operator== (const DMatrix& rightOp) const;
	bool			operator!= (const DMatrix& rightOp) const;

	bool			Invert ();
};


}


#endif