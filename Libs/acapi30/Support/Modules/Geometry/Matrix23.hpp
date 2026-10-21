// *********************************************************************************************************************
// Description:		Matrix2 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX23_HPP)
#define GS_MATRIX23_HPP

#pragma once

// from Geometry
#include "Matrix2.hpp"

struct TRANMAT;

namespace Geometry {

class Transformation2D;

class GEOMETRY_DLL_EXPORT Matrix23 final
{
private:

	double		m_storage[2][3];	// first index: row, second index: column

public:

	Matrix23 (void);
	Matrix23 (const Vector2D& vec1, const Vector2D& vec2, const Vector2D& vec3);		// three column vectors
	Matrix23 (const Matrix22& matr, const Vector2D& vec);

	static void IdentMatrix (Matrix23& result);
	static void RowVectorsMatrix (const Vector2D& vec1, const Vector2D& vec2, Matrix23& result);
	static void ColVectorsMatrix (const Vector2D& vec1, const Vector2D& vec2, const Vector2D& vec3, Matrix23& result);
	static void RotationMatrix (double alpha, Matrix23& result);
	static void ScalingMatrix (double scalx, double scaly, Matrix23& result);
	static GSErrCode Transformation2DMatrix (const Point2D& originalPoint1,
											 const Point2D& originalPoint2,
											 const Point2D& originalPoint3,
											 const Point2D& transformedPoint1,
											 const Point2D& transformedPoint2,
											 const Point2D& transformedPoint3,
											 Matrix23& result);

	static void MirrorXMatrix (Matrix23& result);
	static void MirrorYMatrix (Matrix23& result);

	void GetOffsetVector (Vector2D& vec) const;
	void SetOffsetVector (const Vector2D& vec);
	void GetRowVectors (Vector2D& vec1, Vector2D& vec2) const;
	void GetColVectors (Vector2D& vec1, Vector2D& vec2, Vector2D& vec3) const;
	void GetMatrix22 (Matrix22& matr, Vector2D& vec) const;
	void SetMatrix22 (const Matrix22& matr, const Vector2D& vec);
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, double x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix23& dest) const;
	Vector2D TransfV (const Vector2D& v) const;
	Point2D TransfC (const Point2D& v) const;

	Matrix23		operator- () const;
	Matrix23		operator+ (const Matrix23&) const;
	Matrix23		operator- (const Matrix23&) const;
	Matrix23		operator+ (const Vector2D&) const;
	Matrix23		operator* (double) const;
	Point2D			operator* (const Point2D&) const;

	Matrix23		operator* (const Matrix23&) const;

	Matrix23&		operator+= (const Matrix23&);
	Matrix23&		operator+= (const Vector2D&);
	Matrix23&		operator-= (const Matrix23&);
	Matrix23&		operator*= (double);
	Matrix23&		operator*= (const Matrix23&);

	bool	operator== (const Matrix23&) const;
	bool	operator!= (const Matrix23&) const;

	GSErrCode Read_array (GS::IChannel& ic);
	GSErrCode Write_array (GS::OChannel& oc) const;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML (GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	void IVMatrix (GS::PlatformSign inplatform);
	void IVMatrix (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	TRANMAT ToTranMat () const;
	Geometry::Transformation2D ToTransformation () const;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix23 operator* (double skal, Matrix23& mm) { Matrix23 res = mm * skal; return res; }

} // namespace Geometry


#endif

