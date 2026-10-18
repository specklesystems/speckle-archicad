// *****************************************************************************
//
//                                Pattern Classes
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGPATTERN_HPP
#define QGPATTERN_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "QGBase.hpp"
#include "QGTypes.hpp"
#include "QGPath.hpp"
#include "QGImage.hpp"
#include "Array.hpp"

// ============================== class Pattern ================================

namespace QG {

class Context;
class IPattern;

class QG_DLL_EXPORT Pattern {
	friend	class Context;

protected:
	virtual IPattern*	GetPatternImp (void) const = 0;

public:
	virtual ~Pattern ();
};

// ============================== class SolidPattern ===========================

class ISolidPattern;

class QG_DLL_EXPORT SolidPattern : public QG::Pattern {

private:
	ISolidPattern*	imp;

protected:
	virtual IPattern*	GetPatternImp (void) const override;

public:
	SolidPattern (void);
	SolidPattern (const QG::Color& fillColor);
	virtual ~SolidPattern (void);

	virtual void		SetColor (const QG::Color& fillColor);
	virtual QG::Color	GetColor (void);
};


// ============================== class VectorPattern ===========================

class IVectorPattern;

// We doesn't use the VectorPattern yet, because of the difficulty of the conversion from ARCHICAD vector fill to other brush or pattern
class QG_DLL_EXPORT VectorPattern : public QG::Pattern {
public:
	struct FillLine {
		double		lFreq;			// frequency of the line
		double		lDir;			// angle of the line
		double		lOffsetLine;	// offset of the line (parallel...)
		QG::Point		lOffset;		// offset of the line
	};

private:
	IVectorPattern*	imp;

protected:
	virtual IPattern*	GetPatternImp (void) const override;

public:
	VectorPattern (void);
	VectorPattern (const QG::Color& fillColor);
	virtual ~VectorPattern (void);

	virtual void		SetColor (const QG::Color& fillColor);
	virtual QG::Color	GetColor (void);

	virtual void		SetSpacingFactor (const double hXSpac, const double hYSpac);
	virtual void		GetSpacingFactor (double& hXSpac, double& hYSpac) const;

	virtual void		SetAngle (const double angle);
	virtual double		GetAngle (void) const ;

	virtual void		SetSolidFillSize (const short sizeInPixel);
	virtual short		GetSolidFillSize (void) const;

	virtual void		ClearFillLines (void);
	virtual USize		GetNumberOfFillLines (void) const;
	virtual void		SetFillLines (const GS::Array<QG::VectorPattern::FillLine>& fillLines);
	virtual void		SetFillLines (const QG::VectorPattern::FillLine* fillLines, const USize count);
	virtual void		GetFillLines (GS::Array<QG::VectorPattern::FillLine>& fillLines) const;
	virtual void		GetFillLines (QG::VectorPattern::FillLine* fillLines, const USize count) const;
	virtual void		AddFillLine (const QG::VectorPattern::FillLine& fillLine);
	virtual void		GetFillLine (const USize lineIdx, QG::VectorPattern::FillLine& fillLine) const;

	virtual void		SetLinePart (const USize lineIdx, const GS::Array<double>& lineParts);
	virtual void		SetLinePart (const USize lineIdx, const double* lineParts, const USize count);
	virtual USize		GetNumOfLinePart (const USize lineIdx) const;
	virtual void		GetLinePart (const USize lineIdx, GS::Array<double>& lineParts) const;
	virtual void		GetLinePart (const USize lineIdx, double* lineParts, const USize count) const;
};


// ============================== class SymbolPattern ===========================

class ISymbolPattern;

class QG_DLL_EXPORT SymbolPattern : public QG::Pattern {

private:
	ISymbolPattern*	imp;

protected:
	virtual IPattern*	GetPatternImp (void) const override;

public:
	SymbolPattern (void);
	SymbolPattern (const QG::Color& fillColor);
	virtual ~SymbolPattern (void);

	virtual void				SetColor (const QG::Color& fillColor);
	virtual const QG::Color&	GetColor (void) const;

	virtual void			SetPen (const QG::Pen& fillPen);
	virtual void			GetPen (QG::Pen& fillPen) const;
	virtual const QG::Pen&	GetPen () const;

	virtual void		SetSpacingFactor (const double hXSpac, const double hYSpac);
	virtual void		GetSpacingFactor (double& hXSpac, double& hYSpac) const;

	virtual void		SetAngle (const double angle);
	virtual double		GetAngle (void) const ;

	virtual void		SetSolidFillSize (const short sizeInPixel);
	virtual short		GetSolidFillSize (void) const;

	virtual void		SetBigPattern (bool bigPat);
	virtual bool		GetBigPattern (void) const;

	virtual void		SetStrokes (const QG::Point& strokeXDir, const QG::Point& strokeYDir);
	virtual void		GetStrokes (QG::Point& strokeXDir, QG::Point& strokeYDir) const;

	virtual void				SetOrigo (const QG::Point& orig);
	virtual const QG::Point&	GetOrigo (void) const;

	virtual void				SetMatrix (const double* mtx);
	virtual const double*		GetMatrix (void) const;

	virtual void		ClearFillHotspot (void);
	virtual USize		GetNumberOfFillHotspot (void) const;
	virtual void		AddFillHotspot (QG::Point hotSpot);
	virtual void		SetFillHotspots (const GS::Array<QG::Point>& fillHotspots);
	virtual void		SetFillHotspots (const QG::Point* fillHotspots, const USize count);
	virtual void		GetFillHotspots (GS::Array<QG::Point>& fillHotspots) const;
	virtual void		GetFillHotspots (QG::Point* fillHotspots, const USize count) const;
	virtual void		GetFillHotspot (const USize hotSpotIdx, QG::Point& hotSpot) const;

	virtual void		ClearFillLines (void);
	virtual USize		GetNumberOfFillLines (void) const;
	virtual void		AddFillLine (QG::Point beg, QG::Point end);
	virtual void		SetFillLines (const GS::Array<QG::Point>& fillLinesCoords);
	virtual void		SetFillLines (const QG::Point* fillLinesCoords, const USize countOfPoints);
	virtual void		GetFillLines (GS::Array<QG::Point>& fillLinesCoords) const;
	virtual void		GetFillLines (QG::Point* fillLinesCoords, const USize countOfPoints) const;
	virtual void		GetFillLine (const USize lineIdx, QG::Point& beg, QG::Point& end) const;

	virtual void		ClearFillArcs (void);
	virtual USize		GetNumberOfFillArcs (void) const;
	virtual void		AddFillArc	(QG::Point orig, QG::Point beg, double angle);
	virtual void		SetFillArcs (const GS::Array<QG::Point>& origo, const GS::Array<QG::Point>& begins, const GS::Array<double>& angles);
	virtual void		SetFillArcs (const QG::Point* origo, const QG::Point* begins, const double* angles, const USize countOfPoints);
	virtual void		GetFillArcs (GS::Array<QG::Point>& origo, GS::Array<QG::Point>& begins, GS::Array<double>& angles) const;
	virtual void		GetFillArcs (QG::Point* origo, QG::Point* begins, double* angles, const USize countOfPoints) const;
	virtual void		GetFillArc	(const USize arcIdx, QG::Point& orig, QG::Point& beg, double& angle) const;

	virtual void		ClearFillFill	(void);
	virtual USize		GetNumberOfFillFill (void) const;
	virtual void		AddFillFill		(const QG::Path& path);
	virtual void		SetFillFills	(const GS::Array<QG::Path>& paths);
	virtual void		SetFillFills	(const QG::Path* paths, const USize countOfPath);
	virtual void		GetFillFills	(GS::Array<QG::Path>& paths) const;
	virtual void		GetFillFills	(QG::Path* paths, const USize countOfPaths) const;
	virtual void		GetFillFill		(const USize pathIdx, QG::Path& path) const;

	virtual void		GetPatternSize (QG::Rect& rect) const;
};

// ============================== class ImagePattern ===========================

class IImagePattern;

class QG_DLL_EXPORT ImagePattern : public QG::Pattern {

private:
	IImagePattern*	imp;

protected:
	virtual IPattern*	GetPatternImp (void) const override;

public:
	ImagePattern (void);
	ImagePattern (const QG::Color& fillColor);
	virtual ~ImagePattern (void);

	virtual void				SetColor (const QG::Color& fillColor);
	virtual const QG::Color&	GetColor (void) const;

	virtual	void				SetDrawGray (bool inDrawGray);
	virtual	bool				DrawGrayIsOn (void) const;

	virtual void		SetSpacingFactor (const double hXSpac, const double hYSpac);
	virtual void		GetSpacingFactor (double& hXSpac, double& hYSpac) const;

	virtual void		SetAngle (const double angle);
	virtual double		GetAngle (void) const ;

	virtual void		SetSolidFillSize (const short sizeInPixel);
	virtual short		GetSolidFillSize (void) const;

	virtual void		SetTextureSize (const double& width, const double& height);
	virtual void		GetTextureSize (double& width, double& height) const;

	virtual void		SetTextureStatus (short newTextureStatus);
	virtual short		GetTextureStatus (void) const;

	virtual void				SetOrigo (const QG::Point& orig);
	virtual const QG::Point&	GetOrigo (void) const;

	virtual void				SetMatrix (const double* mtx);
	virtual const double*		GetMatrix (void) const;

	virtual void				SetImage (QG::Image* image);
	virtual const QG::Image*	GetImage () const;

	virtual void				SetTolerance (const double tolerance);
	virtual double				GetTolerance (void) const;
};


}	// namespace QG

#endif	// QGPATTERNS_HPP
