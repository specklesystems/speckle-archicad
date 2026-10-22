// Contact person: KiP

#ifndef LINE_PATTERN_PRIMITIVES_DRAWER_HPP
#define LINE_PATTERN_PRIMITIVES_DRAWER_HPP

#pragma once


// from Pattern
#include "PatternExport.h"

namespace Geometry {
	class PolyId;
}

struct Sector;


namespace GX {
namespace Pattern {


class PATTERN_DLL_EXPORT LinePatternPrimitivesDrawer
{
public:
	virtual ~LinePatternPrimitivesDrawer ();
	virtual	GSErrCode DrawLine (const Geometry::PolyId* edgeId, const Sector* sector) = 0;
};


typedef GSErrCode CCALL DrawLineCallBackProc (void* userDataPtr, const Geometry::PolyId* edgeId, const Sector* sector);

class PATTERN_DLL_EXPORT LinePatternCallBackProcDrawer : public LinePatternPrimitivesDrawer
{
protected:
	DrawLineCallBackProc* drawLineCB;
	void* userDataPtr;

public:
	LinePatternCallBackProcDrawer (DrawLineCallBackProc drawLineCB, void* userDataPtr);
	virtual	~LinePatternCallBackProcDrawer ();

	virtual	GSErrCode DrawLine (const Geometry::PolyId* edgeId, const Sector* sector) override;
};


}
}

#endif
