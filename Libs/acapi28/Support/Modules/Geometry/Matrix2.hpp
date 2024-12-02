// *********************************************************************************************************************
// Description:		Matrix2 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX2_HPP)
#define GS_MATRIX2_HPP

#pragma once

#include <cstddef>

// from GSRoot
#include "GSDebug.hpp"
#include "Channel.hpp"
#include "XMLChannel.hpp"

// from Geometry
#include "Real.hpp"
#include "Length.hpp"
#include "Vector2D.hpp"
#include "Point2D.hpp"


namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix22 final {
private:

	double m_storage[2][2];		// first index: raw, second index: column

public:

	Matrix22 (void);
	Matrix22 (const Vector2D& vec1, const Vector2D& vec2);			// two column vectors

	static void IdentMatrix (Matrix22& result);
	static void RowVectorsMatrix (const Vector2D& vec1, const Vector2D& vec2, Matrix22& result);
	static void ColVectorsMatrix (const Vector2D& vec1, const Vector2D& vec2, Matrix22& result);
	static Matrix22 OuterProduct (const Vector2D& left, const Vector2D& right); //left * Transpose (right)
	static void RotationMatrix (double alpha, Matrix22& result);
	static void ScalingMatrix (double scalx, double scaly, Matrix22& result);
	static void MirrorXMatrix (Matrix22& result);
	static void MirrorYMatrix (Matrix22& result);

	void GetRowVectors (Vector2D& vec1, Vector2D& vec2) const;
	void GetColVectors (Vector2D& vec1, Vector2D& vec2) const;
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, double x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix22& dest) const;
	GSErr RootMatrix (Matrix22& dest) const;			// https://en.wikipedia.org/wiki/Square_root_of_a_2_by_2_matrix

	enum class EigenFactorRetType { RealSolutionExists, OnlyComplexSolution, SolutionProcessFailed };
	EigenFactorRetType EigenFactor (Vector2D& eVect1, Vector2D& eVect2, double& eval1, double& eVal2) const;  // http://www.math.harvard.edu/archive/21b_fall_04/exhibits/2dmatrices/
	Vector2D TransfV (const Vector2D& v) const;
	Point2D TransfC (const Point2D& v) const;

	void Transpose (void);
	void Transpose (Matrix22& dest) const;

	Matrix22		operator- () const;
	Matrix22		operator+ (const Matrix22&) const;
	Matrix22		operator- (const Matrix22&) const;
	Matrix22		operator* (double) const;
	Vector2D		operator* (const Vector2D&) const;
	Point2D			operator* (const Point2D&) const;

	Matrix22		operator* (const Matrix22&) const;

	Matrix22&		operator+= (const Matrix22&);
	Matrix22&		operator-= (const Matrix22&);
	Matrix22&		operator*= (double);
	Matrix22&		operator*= (const Matrix22&);

	bool	operator== (const Matrix22&) const;
	bool	operator!= (const Matrix22&) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix22 operator* (double skal, Matrix22& mm) {  Matrix22 res = mm * skal; return res; }

} // namespace Geometry


#endif

