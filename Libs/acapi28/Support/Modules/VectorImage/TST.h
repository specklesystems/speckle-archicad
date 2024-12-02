#ifndef _TST_H_
#define _TST_H_

#pragma once

#include	"GSRoot.hpp"
#include	"FixArray.hpp"
#include	"VectorImageExport.h"
#include	"CoordTypedef.hpp"
#include	"WordAnchor.hpp"
#include	"VBUtilRichText.hpp"

class Box2DData;


class VI_DLL_EXPORT WordAnchorCalculator {
	const WordAnchor	anchor;
	double				firstRowHeight;
	double				lastRowHeight;
	double				lastLineSpacingHeight;
	double				xDir;
	double				yDir;

public:
	WordAnchorCalculator (const WordAnchor& inAnchor, bool xMirrored = false, bool yMirrored = false);
	WordAnchorCalculator (const WordAnchor& inAnchor, const VBUtil::RichText& wordContent, double scale, bool xMirrored = false, bool yMirrored = false);
	WordAnchorCalculator (const WordAnchor& inAnchor, double inFirstRowHeight, double inLastRowHeight, double inLastLineSpacingHeight, bool xMirrored = false, bool yMirrored = false);

	Coord		GetAnchorLocation (const GS::FixArray<Coord, 4>& square) const;
	Coord		GetAnchorLocation (const Box2DData& box) const;
	Coord		GetTopLeftCornerPosition (const Coord& anchorLocation, double xSize, double ySize, double offset) const;
	Coord		GetCenterPosition (const Coord& anchorLocation, double xSize, double ySize, double offset) const;
	Box2DData	GetWordContentBox (const Coord& anchorLocation, double xSize, double ySize, double offset) const;
	Box2DData	GetWordBox (const Coord& anchorLocation, double xSize, double ySize, double offset) const;
};

#endif
