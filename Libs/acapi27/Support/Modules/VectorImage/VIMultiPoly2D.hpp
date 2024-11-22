#ifndef	PROFILEPOLY2D_HPP
#define	PROFILEPOLY2D_HPP

#pragma once
#include "IrregularPolygon2DClassDefinition.hpp"
// from VectorImage
#include "VectorImageExport.h"


class VI_DLL_CLASS_EXPORT VIMultiPoly2D
{
public:
	VIMultiPoly2D ();
	explicit VIMultiPoly2D (const Geometry::IrregularPolygon2D& src);
	explicit VIMultiPoly2D (const Geometry::MultiIrregularPolygon2D& poly) : mPoly (poly) {}

	virtual ~VIMultiPoly2D (); 

	inline USize									GetNumPoly (void) const { return mPoly.GetSize (); }
	inline Geometry::IrregularPolygon2D&			GetPoly (UIndex polyIndex) { return mPoly.Get (polyIndex); }
	inline const Geometry::IrregularPolygon2D&		GetPoly (UIndex polyIndex) const { return mPoly.Get (polyIndex); }
	void											Clear (void); 

	operator Geometry::MultiIrregularPolygon2D& () { return mPoly; }
	operator const Geometry::MultiIrregularPolygon2D& () const { return mPoly; }
private:

	Geometry::MultiIrregularPolygon2D mPoly;
};

#endif //PROFILEPOLY2D_HPP


