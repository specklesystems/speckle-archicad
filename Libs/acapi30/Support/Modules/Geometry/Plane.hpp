/****************************************************************************/
/*																			*/
/*					3D plane surface										*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (PLANE_HPP)
#define PLANE_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "Vector3D.hpp"
#include "Channel.hpp"

#include "AngleData.h"

struct Sector3D;
struct TRANMAT;
struct PlaneEq;
struct HalfPlane2DData;

namespace Geometry {
class Matrix34;
class Plane3D;
}


namespace Geometry {

template<USize RowCount, USize ColumnCount, class ElementType> class Matrix;
typedef	Matrix<4, 4, double>	Matrix44d;

//------------------------------------------------------------------------------
// CLASS   : Plane
//------------------------------------------------------------------------------
// DESCRIPTION :
// The 'Plane' represents a 3D Plane with a base point and X, Y Z axis vectors
// Useful as a coordinate system
//------------------------------------------------------------------------------
class GEOMETRY_DLL_EXPORT Plane
{
		Point3D		m_basePoint;						// base point of the plane
		Vector3D	m_X_axis, m_Y_axis, m_Z_axis;		// axes ...
		Vector3D	m_InvX, m_InvY, m_InvZ;				// for WorldToPlane conversion (inverse matrix columns)

		void CalcOrthonormalInverse ();
		void CalcInverse ();

		
	public :
		// constructors create orthonormal coordinate frames (see InitPlane, SetPlane)
		Plane (void);
		explicit Plane (const Point3D& in_po);
		explicit Plane (double z);
		Plane (const Point3D& in_po, const Vector3D& in_z_vect);
		Plane (const Point3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect);
		Plane (const Point3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect, const Vector3D& in_y_vect);
		Plane (const PlaneEq& in_plane);
		Plane (const double a, const double b, const double c, const double d);
		explicit Plane (const TRANMAT& tr);
		explicit Plane (const Matrix34& matrix);

		// ---- member functions ----------------------------------------
		// access functions
		const Point3D&	GetBasePoint (void)  const				{ return m_basePoint; }
		void			SetBasePoint (const Point3D& in_po)		{ m_basePoint = in_po; }
		const Vector3D&	GetXAxis (void) const					{ return m_X_axis; }
		const Vector3D&	GetYAxis (void) const					{ return m_Y_axis; }
		const Vector3D&	GetZAxis (void) const					{ return m_Z_axis; }
		Vector3D		GetNormalVector (void) const			{ return m_X_axis ^ m_Y_axis; }

		// functions for creating orthonormal coordinate frame:
		void	InitPlane (void);
		void	SetPlane (const Point3D& in_po, const Vector3D& in_z_vect);	// with a base point and a normal
		void	SetPlane (const Point3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect);  // -"- + X axis
		void	SetPlane (const Point3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect, const Vector3D& in_y_vect);
		void	SetPlane (const Matrix34& tr);

		// create general x-y coordinate frame (though x-y-z is always counterclockwise):
		void	SetPlaneXY (const Point3D& base, const Vector3D& x, const Vector3D& y);

		// if plane is not vertical (its normal is not in the global X-Y plane), then these functions create a coordinate frame
		// in which each point's two coordinates are the same as the point's first two coordinates in the global 3D space:
		void	SetPlaneEq (const PlaneEq& in_plane);
		void	SetUpHorPlane (double z);
		void	SetUpPlane2D3DTransf (const Point3D& c, const Vector3D& n);

		void	Transform (const Matrix34& tran);
		void	Transform (const TRANMAT& tran);
		void	InverseTransformWTrafo (const Matrix44d& trafo);
		void	InverseTransformWTransposedTrafo (const Matrix44d& transposedTrafo);

		PlaneEq	GetPlaneEq (void) const;
		TRANMAT	ToTranMat (void) const;
		TRANMAT	InvToTranMat (void) const;

		// tests if the planes are parallel
		bool IsParallelPlane (const Plane& in_plane) const;

		// tests if the planes are coplanar
		bool IsCoplanarPlane (const Plane& in_plane) const;

		// tests if the point is on the plane
		bool IsPlaneCoord3D (const Point3D& in_po) const;

		double DistFromPlane (const Point3D& point) const;

		// conversions from world to plane and back
		Point3D		WorldToPlane	(const Point3D& in_po) const;
		Vector3D	WorldToPlaneV	(const Vector3D& in_ve) const;
		Vector3D	WorldToPlaneCv	(const Vector3D& in_ve) const;
		Point3D		PlaneToWorld	(const Point3D& in_po) const;
		Vector3D	PlaneToWorldV	(const Vector3D& in_ve) const;
		Vector3D	PlaneToWorldCv	(const Vector3D& in_ve) const;
		Point3D		PlaneToWorld	(const Point2D& in_po) const;
		Vector3D	PlaneToWorldV	(const Vector2D& in_po) const;
		Point3D		PlaneToWorld	(double x, double y) const;
		Vector3D	PlaneToWorldV	(double x, double y) const;
		Point3D		PlaneToWorld	(double x, double y, double z) const;
		Vector3D	PlaneToWorldV	(double x, double y, double z) const;
		Vector3D	PlaneToWorldCv	(double x, double y, double z) const;

		Point3D ProjectToPlane (const Point3D& c) const;
		Vector3D ProjectToPlaneV (const Vector3D& v) const; 
		bool ProjectToPlaneAlongZ (const Point3D& c, Point3D& out_c) const;
		
		static Point3D ProjectToPlane (const Point3D& coord, const Vector3D& planeNormal, const Point3D& planePoint);

		GSErrCode QuickRead (GS::IChannel& ic);
		GSErrCode QuickWrite (GS::OChannel& oc) const;

		GSErrCode ReadXML (GS::XMLIChannel& ic, const char* tagName = nullptr);
		GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;

		GSErrCode Store (GS::ObjectState& os) const;
		GSErrCode Restore (const GS::ObjectState& os);
		GSErrCode Write (GS::OChannel& oc) const;
		GSErrCode Read (GS::IChannel& ic);
};
// Plane } ---------------------------------------------------------------

// ------------------------------ typedefs --------------------------------------------------
typedef Plane* PlanePtr;
typedef Plane const* PlaneConstPtr;

//------------------------------------------------------------------------------
// Function		: CalcCutLineFromPlanes()
// Description  : calculates the cutLine which corresponds to a cutPlane on the selected plane
// Input        : const Plane&		plane
//				: const Plane3D&	cutPlane
// Output       : HalfPlane2DData&	cutLine
// Returns      : false, if the cutPlane is parallel with the selected plane
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool CalcCutLineFromPlanes (const Plane& plane, const Plane3D& cutPlane, HalfPlane2DData& cutLine);

//------------------------------------------------------------------------------
// Function		: XSector3DPlane()
// Description  : intersects a plane with a sector
// Input        : const Sector3D& 	s
//				: const Geometry::Plane&		p
// Output       : Point3D& x_po, double* tRes
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool XSector3DPlane (const Sector3D& 	s, const Geometry::Plane&	p, Point3D& x_po, double* tRes = nullptr);

//------------------------------------------------------------------------------
// Function		: XPlanes()
// Description  : intersects two planes
// Input        : const Geometry::Plane&		p1
//				: const Geometry::Plane&		p2
//				: const double					radeps = RadEps
// Output       : Sector3D	*s
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool XPlanes (const Geometry::Plane&		plane1,
								  const Geometry::Plane&		plane2,
								  Sector3D*						s,
								  double					radEps = RadEps);

//------------------------------------------------------------------------------
// Function		: X3Planes()
// Description  : intersects three planes
// Input        : const Geometry::Plane&		p1
//				: const Geometry::Plane&		p2
//				: const Geometry::Plane&		p3
// Output       : Point3D	*p
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool X3Planes (const Geometry::Plane&		plane1,
	const Geometry::Plane&		plane2,
	const Geometry::Plane&		plane3,
	Point3D*						p);



//------------------------------------------------------------------------------
// Function		: CreatePlane()
// Description  : creates a plane from the points
// Input        : const GS::PagedArray<Point3D>& in_pointArray
// Output       : Geometry::Plane& out_p
// Returns      : returns true if all points are coplanar
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool	CreatePlane (
											const GS::PagedArray<Point3D>& in_pointArray,
											Geometry::Plane& out_p);

//------------------------------------------------------------------------------
// function		: GetRegressionPlane ()
// Description  : creates the regression plane to the given points if possible
// Input        : const GS:PagedArray<Point3D>& points
// Output       : Geometry::Plane& plane - resulted plane
// Returns      : bool status - true if the plane is created
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool	GetRegressionPlane (
											const GS::PagedArray<Point3D>&	points,
											Geometry::Plane& plane);

GEOMETRY_DLL_EXPORT Point2D	PlaneCoordStrict (const Point3D& p, const Plane& plane);

GEOMETRY_DLL_EXPORT bool	AreSamePlanes (const Geometry::Plane& plane1, const Geometry::Plane& plane2);

} // namespace Geometry

#endif
