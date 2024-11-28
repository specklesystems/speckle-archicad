// *****************************************************************************
//
//                                QGTypes - Base type for QGDrawing
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGTYPES_HPP
#define QGTYPES_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

// from GSRoot
#include "GSException.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Color.hpp"

#include "QGBase.hpp"

namespace QG {

// --- Point class -------------------------------------------------------------

class Point : public GS::Point<double> {
public:
	Point () : GS::Point<double> () { };
	Point (double x, double y) : GS::Point<double> (x, y) {};
	inline	Point (const Point& p);
	inline	QG::Point&	operator= (const Point&);
};

inline	Point::Point (const Point& p)
{
	this->Set (p.GetX (), p.GetY ());
}

inline QG::Point& Point::operator= (const Point& p)
{
	this->Set (p.GetX (), p.GetY ());
	return *this;
}

// --- Rect class --------------------------------------------------------------

class Rect : public GS::Rect<double> {
};

// --- Color class -------------------------------------------------------------

class Color : public Gfx::Color {
private:
	bool transparent;
public:
	Color () : Gfx::Color () { transparent = false; }
	explicit Color (const Gfx::Color& c) : Gfx::Color (c) { transparent = false; }

	void SetTransparent (bool transparentColor) { transparent = transparentColor; }
	bool GetTransparent () const { return transparent; }
};

// --- Pen class ---------------------------------------------------------------

class Pen {
private:
	double		width;
	QG::Color	color;

public:
	inline Pen ();
	inline Pen (const double& lineWidth, const QG::Color& lineColor);

	inline void			SetLineWidth (double lineWidth);
	inline double		GetLineWidth (void) const;

	inline void			SetColor (const QG::Color& lineColor);
	inline QG::Color*	GetColor (void) const;
};
// --- Pen class definition ----------------------------------------------------

inline Pen::Pen ()
: width (0.0)
{
}

inline	Pen::Pen (const double& lineWidth, const QG::Color& lineColor)
: width (lineWidth)
{
	this->SetColor (lineColor);
}

inline void			Pen::SetLineWidth (double lineWidth)
{
	width = lineWidth;
}

inline double		Pen::GetLineWidth (void) const
{
	return width;
}

inline void			Pen::SetColor (const QG::Color& lineColor)
{
	color.SetRed   (lineColor.GetRed ());
	color.SetGreen (lineColor.GetGreen ());
	color.SetBlue  (lineColor.GetBlue ());
	color.SetAlpha (lineColor.GetAlpha ());
}

inline QG::Color*	Pen::GetColor (void) const
{
	return const_cast <QG::Color*>(&color);
}

DECLARE_EXCEPTION_CLASS (QGException,	GS::RootException, Error, QG_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (QGInvalidObjectException,	QGException, GS::OutOfMemoryException, ErrMemoryFull, QG_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (QGInternalErrorException,	QGException, GS::InternalErrorException, Error,	QG_DLL_EXPORT)


}	// namespace QG

#endif	// QGTYPES_HPP
