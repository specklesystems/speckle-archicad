#ifndef BOX3DDATA_H
#define BOX3DDATA_H

#pragma once

#include <cmath>

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"
#include "Box2DData.h"


namespace GS {
template<class T> class Array;
} // namespace GS

struct GEOMETRY_DLL_EXPORT F_Box3D {
	float	xMin;
	float	yMin;
	float	xMax;
	float	yMax;
	float	zMin;
	float	zMax;

	F_Box3D () : xMin (0.0), yMin (0.0), xMax (0.0), yMax (0.0), zMin (0.0), zMax (0.0) {}
	F_Box3D (float xMi, float yMi, float xMa, float yMa, float zMi, float zMa) : xMin (xMi), yMin (yMi), xMax (xMa), yMax (yMa), zMin (zMi), zMax (zMa) {}
	void WriteXML (GS::XMLOChannel& outXML, const char* tagName = "F_Box") const;
	void ReadXML (GS::XMLIChannel& inXML, const char* tagName = "F_Box");

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);

};


class GEOMETRY_DLL_EXPORT Box3D {
public:
	//#MV_REFACTOR Ez a parameterlistaja lehetne konzisztens
	Box3D (double xMi, double yMi, double xMa, double yMa, double zMi, double zMa);
	Box3D (const Point3D& bottomLeftRearCorner, const Point3D& topRightFrontCorner);
	Box3D (const Box2DData& box, double elevation = 0.0);
	Box3D (const F_Box3D& fBox);

	static Box3D CreateEmpty ();
	static Box3D CreateBoundBox (const GS::Array<Box3D>& boxes);
	static Box3D CreateBoundBox (const GS::Array<Point3D>& points);

	void Extend (const GS::Array<Box3D>& boxes);
	void Extend (const Box3D& box);
	void Extend (const GS::Array<Point3D>& points);
	void Extend (const Point3D& point);

	void Set (double xMin, double yMin, double xMax, double yMax, double zMin, double zMax);

	Box3D& SetMinX (double minX);
	Box3D& SetMinY (double minY);
	Box3D& SetMinZ (double minZ);
	Box3D& SetMaxX (double maxX);
	Box3D& SetMaxY (double maxY);
	Box3D& SetMaxZ (double maxZ);
	Box3D& Offset (const Vector3D& offset);

	bool IsValid (Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included, double eps = EPS) const;
	bool IsEqual (const Box3D& other, double eps = EPS) const;
	bool IsEmpty (Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included, double eps = EPS) const;

	bool Contains (const Point3D& point,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool Contains (const GS::Array<Point3D>& points,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool Contains (const Box3D& box,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool IsIntersect (const Box3D& box,
					  Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
					  double eps = EPS) const;

	double GetWidth () const;
	double GetHeight () const;
	double GetThickness () const;

	Point3D GetMidPoint () const;

	double GetMinX () const;
	double GetMinY () const;
	double GetMinZ () const;
	double GetMaxX () const;
	double GetMaxY () const;
	double GetMaxZ () const;

	double	xMin;
	double	yMin;
	double	xMax;
	double	yMax;
	double	zMin;
	double	zMax;

	//#MV_TODO, #MV_REFACTOR Make the default constructor private
//private:
	Box3D ();

	double	  GetVolume () const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

namespace Geometry {

GS::Optional<Box3D> Intersect (const Box3D box1,
							   const Box3D box2, 
							   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
							   double eps = EPS);

GEOMETRY_DLL_EXPORT void IVF_Box3D (GS::PlatformSign inplatform, F_Box3D *b);

GEOMETRY_DLL_EXPORT void IVBox3DType (GS::PlatformSign inplatform, Box3D *b);

GEOMETRY_DLL_EXPORT void	InitBox3D (Box3D	*abox);

inline	void SetBox3D (
						Box3D*	abox,
						double 		xMin,
						double 		yMin,
						double		zMin,
						double 		xMax,
						double 		yMax,
						double		zMax);

GEOMETRY_DLL_EXPORT bool IsEmptyBox3D (const Box3D	*pCBox, 
												 Boundary			boundaries = Boundary_Opened);

GEOMETRY_DLL_EXPORT bool AreBox3DsEqual (const F_Box3D& box1, const F_Box3D& box2, double eps = SmallEps);
GEOMETRY_DLL_EXPORT bool AreBox3DsEqual (const Box3D& box1, const Box3D& box2, double eps = SmallEps);

GEOMETRY_DLL_EXPORT void InsetBox3D (Box3D	*b,
									 double		dx,
									 double		dy,
									 double		dz);


GEOMETRY_DLL_EXPORT bool SectBox3D (const Box3D	*pCSrcBox1,
								    const Box3D	*srcBox2,
								    Box3D		*pDstBox);

GEOMETRY_DLL_EXPORT void UnionBox3D (const Box3D	*pCSrcBox1,
									 const Box3D	*srcBox2,
									 Box3D			*pDstBox);

// merge a point into the box
GEOMETRY_DLL_EXPORT void Box3DBound (Box3D* boundbox, const Point3D* c);
GEOMETRY_DLL_EXPORT void Box3DBound (Box3D& boundbox, const Point3D& c);

// merges more points into the box
GEOMETRY_DLL_EXPORT void Box3DBoundCoords (Int32 nCoords, const Point3D* c, Box3D* boundbox, bool setFirst);
GEOMETRY_DLL_EXPORT void Box3DBoundCoords (const GS::Array<Point3D>& c, Box3D* boundbox, bool setFirst = true);


GEOMETRY_DLL_EXPORT bool CheckBox3D (const Box3D& box, const double maxXY, const double maxZ);

GEOMETRY_DLL_EXPORT bool IsEqualBox3D (const Box3D& a, const Box3D& b, double epsilon);

GEOMETRY_DLL_EXPORT void CorrigateBox3D (const Box3D& inBox, Box3D& outBox, const double maxXY, const double maxZ);

GEOMETRY_DLL_EXPORT void CorrigateBox3D (Box3D& box, const double maxXY, const double maxZ);

// tests a srcBox1 against being in the srcBox2
GEOMETRY_DLL_EXPORT bool Box3DInBox3D (
										const Box3D&	srcBox1,
										const Box3D&	srcBox2,
										Boundary	boundaries,
										double eps);

GEOMETRY_DLL_EXPORT bool XBox3D (
										const Box3D *box1,
										const Box3D *box2,
										double eps,
										bool loose = false);

GEOMETRY_DLL_EXPORT	bool IsBox3DPointIntersect (
										const Box3D&		box,
										const Point3D&		pt,
										Boundary			boundaries,
										double				epsilon);

GEOMETRY_DLL_EXPORT bool IsBox3DsIntersect (
										const Box3D&		srcBox1,
										const Box3D&		srcBox2,
										Boundary			boundaries,
										double				eps);

inline	Box2DData	ToBox2D (const Box3D& abox);

GEOMETRY_DLL_EXPORT	F_Box3D		ToF_Box3D (const Box3D& box);


GEOMETRY_DLL_EXPORT GSErrCode ReadXMLBox3D (GS::XMLIChannel& ic, Box3D& box, const char* tagName = nullptr);
GEOMETRY_DLL_EXPORT GSErrCode WriteXMLBox3D (GS::XMLOChannel& oc, const Box3D& box, const char* tagName = nullptr);
GEOMETRY_DLL_EXPORT GSErrCode ReadXMLFBox3D (GS::XMLIChannel& ic, F_Box3D& box, const char* tagName = "BOX3D");
GEOMETRY_DLL_EXPORT GSErrCode WriteXMLFBox3D (GS::XMLOChannel& oc, const F_Box3D& box, const char* tagName = "BOX3D");

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Box3D& box, const char* tagName = nullptr)		{ return Geometry::ReadXMLBox3D (ic, box, tagName); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Box3D& box, const char* tagName = nullptr)	{ return Geometry::WriteXMLBox3D (oc, box, tagName); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, F_Box3D& box)										{ return Geometry::ReadXMLFBox3D (ic, box); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const F_Box3D& box)								{ return Geometry::WriteXMLFBox3D (oc, box); }


}	// namespace Geometry


void Geometry::SetBox3D (
						Box3D*	abox,
						double 		xMin,
						double 		yMin,
						double		zMin,
						double 		xMax,
						double 		yMax,
						double		zMax)
{
	abox->xMin = xMin;
	abox->yMin = yMin;
	abox->zMin = zMin;
	abox->xMax = xMax;
	abox->yMax = yMax;
	abox->zMax = zMax;
}


Box2DData Geometry::ToBox2D (const Box3D& abox)
{
	Box2DData tmp;
	SetBox (&tmp, abox.xMin, abox.yMin, abox.xMax, abox.yMax);
	return tmp;
}


#endif
