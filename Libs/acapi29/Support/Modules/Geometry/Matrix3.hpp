// *********************************************************************************************************************
// Description:		Matrix3 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX3_HPP)
#define GS_MATRIX3_HPP

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


namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix33 {
private:

	double m_storage[3][3];	// first index: row, second index: column

public:

	Matrix33 ();
	Matrix33 (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3); // three column vectors

	static const Matrix33 Identity;

	static void IdentMatrix (Matrix33& result);
	static void RowVectorsMatrix (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, Matrix33& result);
	static void ColVectorsMatrix (const Vector3D& vec1, const Vector3D& vec2, const Vector3D& vec3, Matrix33& result);
	static void RotationXMatrix (double alpha, Matrix33& result);
	static void RotationYMatrix (double alpha, Matrix33& result);
	static void RotationZMatrix (double alpha, Matrix33& result);
	static void ScalingMatrix (double scalx, double scaly, double scalz, Matrix33& result);
	static void MirrorXYMatrix (Matrix33& result);
	static void MirrorYZMatrix (Matrix33& result);
	static void MirrorZXMatrix (Matrix33& result);

	void GetRowVectors3d (Vector3D& vec1, Vector3D& vec2, Vector3D& vec3) const;
	void GetColVectors3d (Vector3D& vec1, Vector3D& vec2, Vector3D& vec3) const;

	double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	void	Set (UIndex i, UIndex j, const double x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix33& dest) const;
	Vector3D TransfV (const Vector3D& v) const;
	Point3D TransfC (const Point3D& v) const;

	void Transpose (void);
	void Transpose (Matrix33& dest) const;

	Matrix33		operator- () const;
	Matrix33		operator+ (const Matrix33&) const;
	Matrix33		operator- (const Matrix33&) const;
	Matrix33		operator* (double) const;
	Point3D			operator* (const Point3D&) const;

	Matrix33		operator* (const Matrix33&) const;

	Matrix33&		operator+= (const Matrix33&);
	Matrix33&		operator-= (const Matrix33&);
	Matrix33&		operator*= (double);
	Matrix33&		operator*= (const Matrix33&);

	bool			operator== (const Matrix33&) const;
	bool			operator!= (const Matrix33&) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	GSErrCode Store		(GS::ObjectState& os) const;
	GSErrCode Restore	(const GS::ObjectState& os);

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix33 operator* (double skal, Matrix33& mm) {  Matrix33 res = mm * skal; return res; }

} // namespace Geometry

#endif

