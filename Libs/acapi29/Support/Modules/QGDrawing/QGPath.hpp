// *****************************************************************************
//
//                                Class Path
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGPATH_HPP
#define QGPATH_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGBase.hpp"
#include "QGTypes.hpp"
#include "QGMatrix.hpp"

#include "Array.hpp"


// ============================== class Path ===========================+++++===

namespace QG {

class IPath;
class Context;

class QG_DLL_EXPORT Path {

friend class Context;

private:
	IPath*	imp;

public:
	Path ();
	Path (const Path& src);
	virtual ~Path ();

	Path& operator=(const Path & source);

	virtual	Int32		NewPath (const QG::Matrix* matrix = nullptr);
	virtual	Int32		EndPath (void);

	virtual	Int32		AddSegments (const QG::Point* points, Int32 count);
	virtual	Int32		AddSegments (const GS::Array<QG::Point>& points);
	virtual	Int32		AddPolyLine (const QG::Point* points, Int32 count);
	virtual	Int32		AddPolyLine (const GS::Array<QG::Point>& points);
	virtual	Int32		AddRect (const QG::Rect& rect);
	virtual	Int32		AddPath (const QG::Path& path);
	virtual	Int32		AddLine (const QG::Point& fromPt, const QG::Point& toPt);
	virtual	Int32		AddLine (double fromPtX, double fromPtY, double toPtX, double toPtY);

	virtual	bool		IsEmpty (void) const;
	virtual	QG::Rect	GetBoundingBox (void) const;

	IPath*				GetIPath (void) const;
};


}	// namespace QG
// ______________________________ class Path ______________________________

#endif	// QGPATH_HPP
