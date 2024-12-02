// *********************************************************************************************************************
// Description:		Simple data class representing a Bezier spline
//
// Module:			Geometry
// *********************************************************************************************************************

#ifndef BEZIERDETAILS_HPP
#define BEZIERDETAILS_HPP

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "Sector2DData.h"

// from GSRoot
#include "Array.hpp"

namespace Geometry {

class BezierDetailsWithIds;

struct DirType {
	double		lenPrev;			/* Bezier direction length prev/next */
	double		lenNext;
	double		dirAng;				/* Bezier direction Angle */

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);
};


// --- BezierDetails ---------------------------------------------------------------------------------------------------


class GEOMETRY_DLL_EXPORT BezierDetails {
private:
	friend class BezierDetailsWithIds;

	GS::Array<Point2D>		coords;
	GS::Array<DirType>		dirs;
	bool					closed;

public:
	BezierDetails ();
	BezierDetails (GS::Array<Point2D>&&, GS::Array<DirType>&&, bool closed);

	BezierDetails (Int32 nCoords, const Point2D** hCoords, const DirType** hDirs);
	BezierDetails (Int32 nCoords, const Point2D* pCoords, const DirType* pDirs);

	Int32 GetCoordsNum () const { return coords.GetSize (); }

	const Point2D*	GetCoordsPtr () const	{ return coords.GetContent (); }
	const DirType*	GetDirsPtr () const		{ return dirs.GetContent (); }

	bool SetData (Int32 nCoords, const Point2D* pCoords, const DirType* pDirs);
	bool SetData (const GS::Array<Point2D>& aCoords, const GS::Array<DirType>& aDirs);
	bool SetData (GS::Array<Point2D>&& coords, GS::Array<DirType>&& dirs);
	bool GetData (GS::Array<Point2D>& aCoords, GS::Array<DirType>& aDirs) const;

	bool IsClosed () const { return closed; }
	void SetClosed (bool clo) { closed = clo; }

	GS::Array<Point2D>&				GetPoints () &				{ return coords; }
	GS::Array<DirType>&				GetDirTypes () &			{ return dirs; }

	const GS::Array<Point2D>&		GetPoints () const &		{ return coords; }
	const GS::Array<DirType>&		GetDirTypes () const &		{ return dirs; }

	GS::Array<Point2D>&&			GetPoints () &&				{ return std::move (coords); }
	GS::Array<DirType>&&			GetDirTypes () &&			{ return std::move (dirs); }

	void			GetBezierDirPoint (Int32 cIndex, bool forward, Point2D* cc) const;

	GSErrCode		Read  (GS::IChannel& ic);
	GSErrCode		Write (GS::OChannel& oc) const;

	GSErrCode		Store	(GS::ObjectState& os) const;
	GSErrCode		Restore	(const GS::ObjectState& os);

	bool			IsEqual	 (const BezierDetails& other) const;
};


GEOMETRY_DLL_EXPORT void TangentLines (const Point2D& p, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void TangentLines (const Sector& s, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void NormalLines (const Point2D& p, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void NormalLines (const Sector& s, const BezierDetails& bez, SectorResultFn fn);


} // namespace Geometry

#endif // BEZIERDETAILS_HPP
