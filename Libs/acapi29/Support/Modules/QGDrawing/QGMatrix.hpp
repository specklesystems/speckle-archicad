// *****************************************************************************
//
//                                Class Matrix
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGMATRIX_HPP
#define QGMATRIX_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGBase.hpp"
#include "QGTypes.hpp"

// ============================== class Matrix ==============================

namespace QG {

class IMatrix;
class Context;

class QG_DLL_EXPORT Matrix {

friend class Context;
friend class Path;

private:
	IMatrix*	imp;
	friend		IMatrix* GetMatrixImp (QG::Matrix& matrix);

public:
	Matrix ();
	Matrix (const Matrix& src);
	Matrix (double elems[6]);
	Matrix (double a, double b, double c, double d, double tx, double ty);
	virtual	~Matrix ();

	virtual Matrix& operator= (const Matrix& src);

	virtual	void	Translate (double x, double y);
	virtual	void	Translate (const Point& point);
	virtual	void	Rotate (double angle);
	virtual	void	Scale (double scaleX, double scaleY);
	virtual	void	ConcatFromRight (const Matrix& rightOp);
	virtual	void	ConcatFromLeft (const Matrix& leftOp);
	virtual	bool	Invert (void);
	virtual	bool	IsIdentity (void) const;

	virtual void	GetElements (double& a, double& b, double& c, double& d, double& tx, double& ty) const;
	virtual void	SetElements (double a, double b, double c, double d, double tx, double ty);

	virtual void	GetElements (double elems[6]) const;
	virtual void	SetElements (double elems[6]);

	virtual void	TransformPoints (Point& point) const;

	virtual void	TransformRectBoundigBox (Rect& rect) const;

	virtual bool	IsKeepingAngles (double& scaleX, double& scaleY) const;
};


}	// namespace QG
// ______________________________ class Matrix ______________________________

#endif	// QGMATRIX_HPP
