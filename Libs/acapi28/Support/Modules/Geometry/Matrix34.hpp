// *********************************************************************************************************************
// Description:		Matrix3 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX34_HPP)
#define GS_MATRIX34_HPP

#pragma once

#include <cstddef>

// from GSRoot
#include "GSDebug.hpp"
#include "Channel.hpp"
#include "XMLChannel.hpp"

// from Geometry
#include "Real.hpp"
#include "Length.hpp"
#include "Vector3D.hpp"
#include "Matrix3.hpp"

namespace Geometry {
	class Matrix23;
}

namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix34 final {
private:

	double m_storage[3][4] = {};	// first index: row, second index: column

public:
			  Matrix34 () = default;
	constexpr Matrix34 (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3);								// three row vectors
	constexpr Matrix34 (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, const Vector3D& vec4);		// four column vectors

	Matrix34 (const Matrix33& matr, const Vector3D& vec1);

	static constexpr	Matrix34	CreateIdentity ();
	static constexpr	Matrix34	CreateTranslation (const Vector3D& vec);
	static constexpr	Matrix34	CreateScaling (double scalx, double scaly, double scalz);
	static constexpr	Matrix34	CreateMirrorXY ();
	static constexpr	Matrix34	CreateMirrorYZ ();
	static constexpr	Matrix34	CreateMirrorZX ();

	static constexpr	Matrix34	CreateFromRowVectors (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3);
	static constexpr	Matrix34	CreateFromColVectors (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, const Vector3D& vec4);

	static inline		Matrix34	CreateRotationX (double alpha);
	static inline		Matrix34	CreateRotationY (double alpha);
	static inline		Matrix34	CreateRotationZ (double alpha);

	static Matrix34		CreateFrom2DTransformationMatrix (const Matrix23& transformation2d);


	Vector3D	GetOffsetVector3d	() const;
	void		SetOffsetVector3d	(const Vector3D& vec1);
	void		GetRowVectors3d		(Vector3D& vec1, Vector3D& vec2, Vector3D& vec3) const;
	void		GetColVectors3d		(Vector3D& vec1, Vector3D& vec2, Vector3D& vec3, Vector3D& vec4) const;

	Matrix33	GetMatrix33 () const;
	Matrix33	GetMatrix33 (Vector3D& vec) const;
	void		GetMatrix33 (Matrix33& matr, Vector3D& vec) const;
	void		SetMatrix33 (const Matrix33& matr, const Vector3D& vec);

	double		Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	void		Set (UIndex i, UIndex j, const double x) { m_storage[i][j] = x; }

	double		DetMatrix () const;
	GSErr		InvMatrix (Matrix34& dest) const;
	Vector3D	TransfV (const Vector3D& v) const;
	Point3D		TransfC (const Point3D& v) const;

	Matrix34		operator- () const;
	Matrix34		operator+ (const Matrix34&) const;
	Matrix34		operator- (const Matrix34&) const;
	Matrix34		operator+ (const Vector3D&) const;
	Matrix34		operator- (const Vector3D&) const;
	Matrix34		operator* (double) const;
	Point3D			operator* (const Point3D&) const;

	Matrix34		operator* (const Matrix34&) const;

	Matrix34&		operator+= (const Matrix34&);
	Matrix34&		operator+= (const Vector3D&);
	Matrix34&		operator-= (const Matrix34&);
	Matrix34&		operator-= (const Vector3D&);
	Matrix34&		operator*= (double);
	Matrix34&		operator*= (const Matrix34&);

	bool	operator== (const Matrix34&) const;
	bool	operator!= (const Matrix34&) const;

	GSErrCode Read_array	(GS::IChannel& ic);
	GSErrCode Write_array	(GS::OChannel& oc) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	void IVMatrix (GS::PlatformSign inplatform);
	void IVMatrix (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);

private:
	GSErrCode			ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

inline Matrix34 operator* (double skal, Matrix34& mm) { return mm * skal; }

constexpr Geometry::Matrix34::Matrix34 (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3) :
	m_storage {
		{ vec1.x, vec1.y, vec1.z, 0.0 },
		{ vec2.x, vec2.y, vec2.z, 0.0 },
		{ vec3.x, vec3.y, vec3.z, 0.0 }
	}
{
}


constexpr Matrix34::Matrix34 (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, const Vector3D& vec4) :
	m_storage {
		{ vec1.x, vec2.x, vec3.x, vec4.x },
		{ vec1.y, vec2.y, vec3.y, vec4.y },
		{ vec1.z, vec2.z, vec3.z, vec4.z }
	}
{
}


constexpr Matrix34	Matrix34::CreateIdentity ()
{
	return Matrix34 (Vector3D (1.0, 0.0, 0.0), Vector3D (0.0, 1.0, 0.0), Vector3D (0.0, 0.0, 1.0));
}


constexpr Matrix34	Matrix34::CreateTranslation (const Vector3D& vec)
{
	return Matrix34 (Vector3D (1.0, 0.0, 0.0), Vector3D (0.0, 1.0, 0.0), Vector3D (0.0, 0.0, 1.0), vec);
}


constexpr Matrix34	Matrix34::CreateScaling (const double scalx, const double scaly, const double scalz)
{
	return Matrix34 (Vector3D (scalx, 0.0, 0.0), Vector3D (0.0, scaly, 0.0), Vector3D (0.0, 0.0, scalz));
}


constexpr Matrix34	Matrix34::CreateMirrorXY ()
{
	return Matrix34 (Vector3D (1.0, 0.0, 0.0), Vector3D (0.0, 1.0, 0.0), Vector3D (0.0, 0.0, -1.0));
}


constexpr Matrix34	Matrix34::CreateMirrorYZ ()
{
	return Matrix34 (Vector3D (-1.0, 0.0, 0.0), Vector3D (0.0, 1.0, 0.0), Vector3D (0.0, 0.0, 1.0));
}


constexpr Matrix34	Matrix34::CreateMirrorZX ()
{
	return Matrix34 (Vector3D (1.0, 0.0, 0.0), Vector3D (0.0, -1.0, 0.0), Vector3D (0.0, 0.0, 1.0));
}


constexpr Matrix34	Matrix34::CreateFromRowVectors (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3)
{
	return Matrix34 (vec1, vec2, vec3);
}


constexpr Matrix34	Matrix34::CreateFromColVectors (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, const Vector3D& vec4)
{
	return Matrix34 (vec1, vec2, vec3, vec4);
}


inline Matrix34		Matrix34::CreateRotationX (const double alpha)
{
	return Matrix34 (Vector3D (1.0, 0.0, 0.0), Vector3D (0.0, cos (alpha), -sin (alpha)), Vector3D (0.0, sin (alpha), cos (alpha)));
}


inline Matrix34		Matrix34::CreateRotationY (const double alpha)
{
	return Matrix34 (Vector3D (cos (alpha), 0.0, sin (alpha)), Vector3D (0.0, 1.0, 0.0), Vector3D (-sin (alpha), 0.0, cos (alpha)));
}


inline Matrix34		Matrix34::CreateRotationZ (const double alpha)
{
	return Matrix34 (Vector3D (cos (alpha), -sin (alpha), 0.0), Vector3D (sin (alpha), cos (alpha), 0.0), Vector3D (0.0, 0.0, 1.0));
}


} // namespace Geometry


#endif

