// *****************************************************************************
//
//                                Class ContextAttribs
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGCONTEXTATTRIBS_HPP
#define QGCONTEXTATTRIBS_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "QGBase.hpp"
#include "QGTypes.hpp"

// ============================== class ContextAttribs ==============================

namespace QG {


class QG_DLL_EXPORT ContextAttribs {

private:
	Int32	unit;
	Int32	colorMode;
	Int32	lineMode;
	Int32	lineCap;
	Int32	lineJoin;
	Int32	antiAliasing;
	double	miterLimit;			// in actual unit
	double	bScale;
	double	bAngle;				// in radian
	double	offsetX;			// in actual unit
	double	offsetY;			// in actual unit

	bool	limitResolution;
	short	resolution;
	bool	compressAll;

public:
	enum ContextUnit	{ cuUnknown = -1, cuPixel = 0, cuPoint = 1, cuMM = 2, cuM = 3, cuInch = 4 };
	enum ColorMode		{ cmUnknown = -1, cmDefault = 0, cmGrayScale = 1, cmBlackWhite = 2 };
	enum LineMode		{ lmUnknown = -1, lmDefault = 0, lmHairLine = 1 };
	enum LineCap		{ lcUnknown = -1, lcButt  = 0, lcRound = 1, lcSquare = 2 };
	enum LineJoin		{ ljUnknown = -1, ljMiter = 0, ljRound = 1, ljBevel = 2 };
	enum CoordSpace		{ csUser = 0, csDevice };

	ContextAttribs (void);

	void		SetUnit (ContextUnit cUnit);
	ContextUnit GetUnit (void) const;
	void		SetColorMode (ColorMode cMode);
	ColorMode	GetColorMode (void) const;
	void		SetLineMode (LineMode lMode);
	LineMode	GetLineMode (void) const;
	void		SetLineProps (LineCap lCap, LineJoin lJoin = ljRound, double miterLimit = 3.0 );
	void		GetLineProps (LineCap *lCap, LineJoin *lJoin = nullptr, double *miterLimit = nullptr) const;
	void		SetBaseTranslate (double x, double y);
	void		GetBaseTranslate (double *x, double *y = nullptr) const;
	void		SetBaseRotate (double angle);
	double		GetBaseRotate (void) const;
	void		SetBaseScale (double scale);
	double		GetBaseScale (void) const;
	void		SetAntiAliasing (bool flag);
	bool		AntiAliasingIsOn (void) const;

	void		SetLimitResolution (bool limit);
	bool		IsResolutionLimited (void) const;
	void		SetResolution (short resolutionValue);
	short		GetResolution (void) const;
	void		SetCompressAll (bool compress);
	bool		IsCompressAll (void) const;
};

}	// namespace QG
// ______________________________ class ContextAttribs ______________________________

#endif	// QGCONTEXTATTRIBS_HPP
