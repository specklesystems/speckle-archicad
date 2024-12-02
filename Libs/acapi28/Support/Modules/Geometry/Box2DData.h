// *****************************************************************************
// C style struct for 2D Box
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY, MV
//
// *****************************************************************************
#if !defined (GS_BOX_2D_DATA_H)
#define GS_BOX_2D_DATA_H

#pragma once

#include "Point2DData.h"
#include "Sector2DData.h"

// from GSRoot
#include "GSDebug.hpp"

struct Sector;
struct TRANMAT;

/* Rectangle in World coordinates*/
class GEOMETRY_DLL_EXPORT Box2DData {
public:
	Box2DData (double xMin, double yMin, double xMax, double yMax);
	Box2DData (const Point2D& bottomLeft, const Point2D& topRight);
	static Box2DData CreateEmpty ();
	static Box2DData CreateBoundBox (const GS::Array<Box2DData>& boxes);
	static Box2DData CreateBoundBox (const GS::Array<Point2D>& points);

	void Extend (const GS::Array<Box2DData>& boxes);
	void Extend (const Box2DData& box);
	void Extend (const GS::Array<Point2D>& points);
	void Extend (const Point2D& point);

	void Set (double xMin, double yMin, double xMax, double yMax);
	void Set (const Point2D& bottomLeft, const Point2D& topRight);

	Box2DData& SetWidth (double width);
	Box2DData& SetHeight (double height);
	Box2DData& SetMinX (double minX);
	Box2DData& SetMinY (double minY);
	Box2DData& SetMaxX (double maxX);
	Box2DData& SetMaxY (double maxY);
	Box2DData& Offset (const Vector2D& offset);

	bool IsEqual (const Box2DData& other, double eps = EPS) const;
	bool IsEmpty (Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included, double eps = EPS) const;

	bool Contains (const Point2D& point,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool Contains (const GS::Array<Point2D>& points,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool Contains (const Box2DData& box,
				   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
				   double eps = EPS) const;

	bool IsIntersect (const Box2DData& box,
					  Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
					  double eps = EPS) const;

	double GetWidth () const;
	double GetHeight () const;

	Point2D GetBottomLeftCorner () const;
	Point2D GetBottomRightCorner () const;
	Point2D GetTopRightCorner () const;
	Point2D GetTopLeftCorner () const;
	Point2D GetMidPoint () const;

	Sector GetBottomSide () const;
	Sector GetRightSide () const;
	Sector GetTopSide () const;
	Sector GetLeftSide () const;

	double GetMinX () const;
	double GetMinY () const;
	double GetMaxX () const;
	double GetMaxY () const;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);


	//Use the setters/getters instead of these
	double	xMin;
	double	yMin;
	double	xMax;
	double	yMax;

//#MV_TODO, #MV_REFACTOR Make the default constructor private
//private:
	Box2DData ();
};


namespace Geometry {

GEOMETRY_DLL_EXPORT GS::Optional<Box2DData> Intersect (const Box2DData box1,
													   const Box2DData box2, 
													   Geometry::Boundary boundary = Geometry::Boundary::Boundary_Included,
													   double eps = EPS);

//#MV_REFACTOR Old code, don't Use these functions,
// Use the Box2DData member functions or the upper static functions!

GEOMETRY_DLL_EXPORT Box2DData CreateBox (double hSize, double vSize);

GEOMETRY_DLL_EXPORT GSErrCode ReadXMLBox (GS::XMLIChannel& ic, Box2DData& box, const char* tagName = nullptr);

GEOMETRY_DLL_EXPORT GSErrCode WriteXMLBox (GS::XMLOChannel& oc, const Box2DData& box, const char* tagName = nullptr);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Box2DData& box, const char* tagName = nullptr)
{
	return Geometry::ReadXMLBox (ic, box, tagName);
}

inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Box2DData& box, const char* tagName = nullptr)
{
	return Geometry::WriteXMLBox (oc, box, tagName);
}


inline				void SetBox (
	Box2DData*	abox,
	double 		xMin,
	double 		yMin,
	double 		xMax,
	double 		yMax);

GEOMETRY_DLL_EXPORT void  CoordToBox (const Point2D& c, Box2DData* abox);

GEOMETRY_DLL_EXPORT Box2DData SectorBox (const Sector *s);

GEOMETRY_DLL_EXPORT void IVBoxType (GS::PlatformSign inplatform, Box2DData *b);
GEOMETRY_DLL_EXPORT void IVBoxType (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Box2DData *b);

GEOMETRY_DLL_EXPORT bool Coord1InBox (Int32				nCoords,			/* sm298 */
									  const Point2D*		c,
									  const Box2DData*	b,
									  bool				rot,
									  double			angle);

GEOMETRY_DLL_EXPORT bool CoordsInBox (Int32				nCoords,
									  const Point2D*		c,
									  const Box2DData*	b,
									  bool				rot,
									  double				angle,
									  Boundary			boundaries = Boundary_Closed,
									  double				eps = Eps);

GEOMETRY_DLL_EXPORT bool IsEmptyBox (const Box2DData&	pCBox,
									 Boundary			boundaries = Boundary_Opened,
									 double				eps = SmallEps);

GEOMETRY_DLL_EXPORT bool IsEqualBox (const Box2DData& a, const Box2DData& b, double epsilon);

GEOMETRY_DLL_EXPORT void BoxBound (Box2DData* boundbox, const Point2D* c);

GEOMETRY_DLL_EXPORT void BoxBound (Box2DData* boundbox, const Point2D& c);

template<typename CoordType>
void BoxBoundCoords (Int32 nCoords, const CoordType* c, Box2DData* boundbox, bool setFirst);

GEOMETRY_DLL_EXPORT void BoxBoundCoords (const GS::Array<Point2D>& c, Box2DData* boundbox, bool setFirst = true);

GEOMETRY_DLL_EXPORT void CoordsBound (Int32				nCoords,
									  const Point2D*	c,
									  Box2DData*		boundbox,
									  bool				rot,
									  double			angle);

template<class ConstIterator>
void GetPointsBound (
	ConstIterator	begCoordIt,
	ConstIterator	endCoordIt,	// one after last
	Box2DData*		boundbox);

template<class ConstIterator>
void GetPointsBound (
	ConstIterator	begCoordIt,
	ConstIterator	endCoordIt,	// one after last
	double			pointRotation, // around origo
	Box2DData*		boundbox);

GEOMETRY_DLL_EXPORT void BoxBoundR (Box2DData* boundbox, const Point2D	*c, double radius);

GEOMETRY_DLL_EXPORT void BoxBoundR (Box2DData* boundbox, const Point2D& c, double radius);

inline				void InsetBox (Box2DData* b, double dx, double dy);

GEOMETRY_DLL_EXPORT void OffsetBox (Box2DData* b, double dx, double dy);

GEOMETRY_DLL_EXPORT Box2DData ScaleToFit (const Box2DData& targetRect, double srcH, double srcV);
GEOMETRY_DLL_EXPORT Box2DData ScaleToFill (const Box2DData& targetRect, double srcH, double srcV);

inline				bool IsBoxPointIntersect (
	const Box2DData&	box,
	const Point2D&		pt,
	Boundary			boundaries,
	double				epsilon);

inline				bool IsBoxesIntersect (
	const Box2DData&	srcBox1,
	const Box2DData&	srcBox2,
	Boundary			boundaries,
	double				eps);

GEOMETRY_DLL_EXPORT	bool BoxInBox (
	const Box2DData&	box1,
	const Box2DData&	box2,
	Boundary			boundaries,
	double				eps);

GEOMETRY_DLL_EXPORT bool SectBox (const Box2DData* pCSrcBox1, const Box2DData* srcBox2, Box2DData* pDstBox);

GEOMETRY_DLL_EXPORT void UnionBox (const Box2DData* addbox, Box2DData* destBox);

GEOMETRY_DLL_EXPORT void UnionBox (const Box2DData& addbox, Box2DData* destBox);

GEOMETRY_DLL_EXPORT void UnionBoxPtr (const Box2DData* pCSrcBox1, const Box2DData* pCSrcBox2, Box2DData* pDstBox);

GEOMETRY_DLL_EXPORT void BoxToCoords (Point2D*			c4,				/* sm299 */
									  const Box2DData*	aBox);

template<class RandIterator>
void GetBoxCorners (
	const Box2DData& box,
	RandIterator	 cornersIt);	// will overwrite first 4 elems


template <typename RectType>
Box2DData							ConvertToBox2DData (const RectType& rect);

template <typename RectType>
RectType							ConvertToRect (const Box2DData& rect);

template <typename RectType1, typename RectType2>
RectType1							ConvertToRect (const RectType2& rect);

GEOMETRY_DLL_EXPORT void CoordsToBox (Box2DData*		aBox,
									  const Point2D*	c4);

GEOMETRY_DLL_EXPORT void RotBoxToCoords (const Box2DData*	aBox,
										 const Point2D*		origo,
										 double				angle,
										 Point2D*			corners);

/* The following three functions are for the same operations (must be united): */

GEOMETRY_DLL_EXPORT bool ClipLineBox (
	Point2D*				co1,
	Point2D*				co2,
	const Box2DData*	bounds,
	bool 				changeClipCoords);

GEOMETRY_DLL_EXPORT bool LineCut (
	Point2D*				co1,
	Point2D*				co2,
	const Box2DData*	boundBox,
	bool				insetBounds,
	bool				changeClipCoords);

GEOMETRY_DLL_EXPORT bool ClipLine (Box2DData* clip, Point2D* pBeg, Point2D* pEnd);

GEOMETRY_DLL_EXPORT bool ClipLineOutBox (Box2DData *clip, Point2D *pBeg, Point2D *pEnd, Int32 *npart);

inline void SetBox (
	Box2DData*	abox,
	double 		xMin,
	double 		yMin,
	double 		xMax,
	double 		yMax)
{
	abox->Set (xMin, yMin, xMax, yMax);
}

inline void InsetBox (
	Box2DData	*b,
	double		dx,
	double		dy)
{
	b->Set (b->GetMinX () + dx,
			b->GetMinY () + dy,
			b->GetMaxX () - dx,
			b->GetMaxY () - dy);
}

inline bool IsBoxPointIntersect (
	const Box2DData&	box,
	const Point2D&		pt,
	Boundary			boundaries,
	double				eps)

{
	return box.Contains (pt, boundaries, eps);
}

inline bool IsBoxesIntersect (
	const Box2DData&	srcBox1,
	const Box2DData&	srcBox2,
	Boundary			boundaries,
	double				epsilon)
{
	if (boundaries == Boundary_Opened) {
		if (IsGreater (srcBox1.xMax, srcBox2.xMin, epsilon) &&
			IsGreater (srcBox2.xMax, srcBox1.xMin, epsilon) &&
			IsGreater (srcBox1.yMax, srcBox2.yMin, epsilon) &&
			IsGreater (srcBox2.yMax, srcBox1.yMin, epsilon)) {
			return true;
		} else {
			return false;
		}
	}

	if (boundaries == Boundary_Closed) {
		if (IsGreaterOrNear (srcBox1.xMax, srcBox2.xMin, epsilon) &&
			IsGreaterOrNear (srcBox2.xMax, srcBox1.xMin, epsilon) &&
			IsGreaterOrNear (srcBox1.yMax, srcBox2.yMin, epsilon) &&
			IsGreaterOrNear (srcBox2.yMax, srcBox1.yMin, epsilon)) {
			return true;
		} else {
			return false;
		}
	}
	DBBREAK_STR ("Unknown interval boundary!");
	return false;

}


template<class RandIterator>
void GetBoxCorners (
	const Box2DData& box,
	RandIterator	 cornersIt)	// will overwrite first 4 elems
{
	cornersIt[0].x = box.GetBottomLeftCorner  ().x;
	cornersIt[1].x = box.GetBottomRightCorner ().x;
	cornersIt[2].x = box.GetTopRightCorner	  ().x;
	cornersIt[3].x = box.GetTopLeftCorner	  ().x;

	cornersIt[0].y = box.GetBottomLeftCorner  ().y;
	cornersIt[1].y = box.GetBottomRightCorner ().y;
	cornersIt[2].y = box.GetTopRightCorner	  ().y;
	cornersIt[3].y = box.GetTopLeftCorner     ().y;

}

template<typename CoordType>
void BoxBoundCoords (Int32 nCoords, const CoordType* c, Box2DData* boundbox, bool setFirst)
{
	Int32 n;
	GS::Array<CoordType> coords;
	if(setFirst && nCoords > 0) {
		boundbox->Set (*c, *c);
		n = 1;
	}
	else {
		n = 0;
	}

	for(Int32 i = n; i < nCoords; i++) {
		coords.Push (c[i]);
	}
	boundbox->Extend (coords);
}


template<class ConstIterator>
inline void GetPointsBound (
	ConstIterator	begCoordIt,
	ConstIterator	endCoordIt,	// one after last
	Box2DData*		boundbox)
{
	*boundbox = Box2DData ();
	for(; begCoordIt != endCoordIt; ++begCoordIt) {
		Point2D cc = *begCoordIt;
		boundbox->xMin = MIN (boundbox->xMin, cc.x);
		boundbox->xMax = MAX (boundbox->xMax, cc.x);
		boundbox->yMin = MIN (boundbox->yMin, cc.y);
		boundbox->yMax = MAX (boundbox->yMax, cc.y);
	}
}

template<class ConstIterator>
inline void GetPointsBound (
	ConstIterator	begCoordIt,
	ConstIterator	endCoordIt,	// one after last
	double			pointRotation, // around origo
	Box2DData*		boundbox)
{
	double co = cos (pointRotation);
	double si = sin (pointRotation);
	*boundbox = Box2DData ();
	for(; begCoordIt != endCoordIt; ++begCoordIt) {
		Point2D cc = *begCoordIt;
		cc = Geometry::RotCoord0 (cc, si, co);
		boundbox->xMin = MIN (boundbox->xMin, cc.x);
		boundbox->xMax = MAX (boundbox->xMax, cc.x);
		boundbox->yMin = MIN (boundbox->yMin, cc.y);
		boundbox->yMax = MAX (boundbox->yMax, cc.y);
	}
}

template <typename RectType>
inline Box2DData ConvertToBox2DData (const RectType& rect)
{
	Box2DData re;

	re.yMin = rect.top;
	re.yMax = rect.bottom;
	re.xMin = rect.left;
	re.xMax = rect.right;

	return re;
}

#pragma warning (push)
#pragma warning (disable : 4244)

template <typename RectType>
inline RectType ConvertToRect (const Box2DData& rect)
{
	RectType re;

	re.top = rect.yMin;
	re.bottom = rect.yMax;
	re.left = rect.xMin;
	re.right = rect.xMax;

	return re;
}

#pragma warning (pop)

template <typename RectType1, typename RectType2>
inline RectType1 ConvertToRect (const RectType2& rect)
{
	RectType1 re;

	re.top = rect.top;
	re.bottom = rect.bottom;
	re.left = rect.left;
	re.right = rect.right;

	return re;
}


GEOMETRY_DLL_EXPORT void   SyBoxTranToCoord (const Box2DData	*aBox,
											 const TRANMAT		*tran,
											 Point2D			*co);


} // namespace Geometry


typedef struct F_Box {
	float	xMin;
	float	yMin;
	float	xMax;
	float	yMax;
} F_Box;				/* 16 */			/* Rectangle in World coordinates	*/

#define	F_BoxType	F_Box		/* temporary */

namespace Geometry {

GEOMETRY_DLL_EXPORT void F_BoxToBox (Box2DData* dBox, const F_BoxType* fBox);

GEOMETRY_DLL_EXPORT void BoxToF_Box (F_BoxType* fBox, const Box2DData* dBox);

GEOMETRY_DLL_EXPORT void IVF_BoxType (GS::PlatformSign inplatform, F_BoxType *b);
GEOMETRY_DLL_EXPORT void IVF_BoxType (GS::PlatformSign inplatform, GS::PlatformSign toplatform, F_BoxType *b);
GEOMETRY_DLL_EXPORT GSErrCode ReadXMLFBox (GS::XMLIChannel& ic, F_BoxType& fBox);
GEOMETRY_DLL_EXPORT GSErrCode WriteXMLFBox (GS::XMLOChannel& oc, const F_BoxType& fBox);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, F_Box& fBox)
{
	return Geometry::ReadXMLFBox (ic, fBox);
}
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const F_Box& fBox)
{
	return Geometry::WriteXMLFBox (oc, fBox);
}
}

#endif
