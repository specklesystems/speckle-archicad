// *****************************************************************************
//
//								Rect class
//
// Module:			AC
// Namespace:		-
// Contact person:	AZS
//
// SG compatible
//
// *****************************************************************************

#ifndef RECT_HPP
#define RECT_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "Point.hpp"
#include "BaseAlgorithms.hpp"

// --- Declarations ------------------------------------------------------------

namespace GS {

// --- Class declarations ------------------------------------------------------

// --- Rect --------------------------------------------------------------------

template<class TYPE>
class Rect {
private:
	TYPE	left;
	TYPE	top;
	TYPE	right;
	TYPE	bottom;

	void	Normalize (void);

public:
	Rect ();
	Rect (const TYPE& newLeft, const TYPE& newTop, const TYPE& newRight, const TYPE& newBottom);
	Rect (const Point<TYPE>& p);

	void	Reset (void);
	void	Set (const TYPE& newLeft, const TYPE& newTop, const TYPE& newRight, const TYPE& newBottom);
	void	Set (const Point<TYPE>& p);
	void	SetWithSize (const TYPE& newLeft, const TYPE& newTop, const TYPE& height, const TYPE& width);

	TYPE	GetLeft (void) const;
	TYPE	GetTop (void) const;
	TYPE	GetRight (void) const;
	TYPE	GetBottom (void) const;
	TYPE	GetWidth (void) const;
	TYPE	GetHeight (void) const;

	void	SetLeft (const TYPE& newLeft);
	void	SetTop (const TYPE& newTop);
	void	SetRight (const TYPE& newRight);
	void	SetBottom (const TYPE& newBottom);
	void	SetWidth (const TYPE& newWidth);
	void	SetHeight (const TYPE& newHeight);
	void	SetSize (const TYPE& newWidth, const TYPE& newHeight);
	void	Resize (const TYPE& deltaW, const TYPE& deltaH);
	void	Inset (const TYPE& deltaX, const TYPE& deltaY);
	void	Offset (const TYPE& deltaX, const TYPE& deltaY);

	bool	operator== (const Rect<TYPE>&) const;
	bool	operator!= (const Rect<TYPE>&) const;
	inline  bool	IsOverlapping (const Rect<TYPE>&) const;
	bool	IsInside (const TYPE& xPosition, const TYPE& yPosition) const;
	bool	IsInside (const Point<TYPE>& p) const;
	bool	IsInside (const Rect<TYPE>&) const;
	bool	IsOutside (const Rect<TYPE>&) const;
	bool	IsEmpty (void) const;

	Rect	Union (const Rect&) const;
	Rect	Union (const Point<TYPE>& p) const;
	Rect	Intersection (const Rect&) const;

	void	Unify (const Rect&);
	void	Unify (const Point<TYPE>& p);
	void	Intersect (const Rect&);
};


// --- Private methods ---------------------------------------------------------

template <class TYPE>
void	Rect<TYPE>::Normalize (void)
{
	if (top > bottom)
		Swap (top, bottom);

	if (left > right)
		Swap (left, right);
}


// --- Public methods ----------------------------------------------------------

template <class TYPE>
Rect<TYPE>::Rect ():
	left (0),
	top (0),
	right (0),
	bottom (0)
{
}


template <class TYPE>
Rect<TYPE>::Rect (const TYPE& newLeft, const TYPE& newTop, const TYPE& newRight, const TYPE& newBottom):
	left (newLeft),
	top (newTop),
	right (newRight),
	bottom (newBottom)
{
	Normalize ();
}


template <class TYPE>
Rect<TYPE>::Rect (const Point<TYPE>& p):
	left (p.GetX ()),
	top (p.GetY ()),
	right (p.GetX ()),
	bottom (p.GetY ())
{
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::Reset (void)
{
	left	= 0;
	top		= 0;
	right	= 0;
	bottom	= 0;
}


template <class TYPE>
void	Rect<TYPE>::Set (const TYPE& newLeft, const TYPE& newTop, const TYPE& newRight, const TYPE& newBottom)
{
	left	= newLeft;
	top		= newTop;
	right	= newRight;
	bottom	= newBottom;

	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::Set (const Point<TYPE>& p)
{
	left	= p.GetX ();
	top		= p.GetY ();
	right	= left;
	bottom	= top;

	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetWithSize (const TYPE& newLeft, const TYPE& newTop, const TYPE& width, const TYPE& height)
{
	left	= newLeft;
	top		= newTop;
	right	= static_cast<TYPE> (left + width);
	bottom	= static_cast<TYPE> (top + height);

	Normalize ();
}


template <class TYPE>
TYPE	Rect<TYPE>::GetLeft (void) const
{
	return left;
}


template <class TYPE>
TYPE	Rect<TYPE>::GetTop (void) const
{
	return top;
}


template <class TYPE>
TYPE	Rect<TYPE>::GetRight (void) const
{
	return right;
}


template <class TYPE>
TYPE	Rect<TYPE>::GetBottom (void) const
{
	return bottom;
}


template <class TYPE>
TYPE	Rect<TYPE>::GetWidth (void) const
{
	return static_cast<TYPE> (right - left);
}


template <class TYPE>
TYPE	Rect<TYPE>::GetHeight (void) const
{
	return static_cast<TYPE> (bottom - top);
}


template <class TYPE>
void	Rect<TYPE>::SetLeft (const TYPE& newLeft)
{
	left = newLeft;
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetTop (const TYPE& newTop)
{
	top = newTop;
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetRight (const TYPE& newRight)
{
	right = newRight;
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetBottom (const TYPE& newBottom)
{
	bottom = newBottom;
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetWidth (const TYPE& newWidth)
{
	right = static_cast <TYPE> (left + newWidth);
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetHeight (const TYPE& newHeight)
{
	bottom = static_cast <TYPE> (top + newHeight);
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::SetSize (const TYPE& newWidth, const TYPE& newHeight)
{
	SetWidth (newWidth);
	SetHeight (newHeight);
}


template <class TYPE>
void	Rect<TYPE>::Resize (const TYPE& deltaW, const TYPE& deltaH)
{
	SetWidth (static_cast<TYPE> (GetWidth () + deltaW));
	SetHeight (static_cast<TYPE> (GetHeight () + deltaH));
}


template <class TYPE>
void	Rect<TYPE>::Inset (const TYPE& deltaX, const TYPE& deltaY)
{
	left	= static_cast<TYPE> (left + deltaX);
	top		= static_cast<TYPE> (top + deltaY);
	right	= static_cast<TYPE> (right - deltaX);
	bottom	= static_cast<TYPE> (bottom - deltaY);
	Normalize ();
}


template <class TYPE>
void	Rect<TYPE>::Offset (const TYPE& deltaX, const TYPE& deltaY)
{
	left	= static_cast<TYPE> (left + deltaX);
	top		= static_cast<TYPE> (top + deltaY);
	right	= static_cast<TYPE> (right + deltaX);
	bottom	= static_cast<TYPE> (bottom + deltaY);
}






template <class TYPE>
bool	Rect<TYPE>::operator== (const Rect<TYPE>& toCompare) const
{
	return (toCompare.left == left && toCompare.top == top &&
			toCompare.right == right && toCompare.bottom == bottom);
}


template <class TYPE>
bool	Rect<TYPE>::operator!= (const Rect<TYPE>& toCompare) const
{
	return (toCompare.left != left || toCompare.top != top ||
			toCompare.right != right || toCompare.bottom != bottom);
}


template <class TYPE>
inline bool	Rect<TYPE>::IsOverlapping (const Rect<TYPE>& toCompare) const
{
	return (Max (left, toCompare.left) <= Min (right, toCompare.right) && Max (top, toCompare.top) <= Min (bottom, toCompare.bottom));
}


template <class TYPE>
bool	Rect<TYPE>::IsInside (const TYPE& xPosition, const TYPE& yPosition) const
{
	return (IsBetween (xPosition, left, right) &&
			IsBetween (yPosition, top, bottom));
}


template <class TYPE>
bool	Rect<TYPE>::IsInside (const Point<TYPE>& p) const
{
	return (IsBetween (p.GetX (), left, right) &&
			IsBetween (p.GetY (), top, bottom));
}


template <class TYPE>
bool	Rect<TYPE>::IsInside (const Rect<TYPE>& in) const
{
	return (in.left >= left && in.right <= right &&
			in.top >= top && in.bottom <= bottom);
}


template <class TYPE>
bool	Rect<TYPE>::IsOutside (const Rect<TYPE>& out) const
{
	return (out.left > right || out.right < left ||
			out.top > bottom || out.bottom < top);
}


template <class TYPE>
bool	Rect<TYPE>::IsEmpty (void) const
{
	return (left == right && top == bottom);
}


template <class TYPE>
Rect<TYPE>	Rect<TYPE>::Union (const Rect<TYPE>& toUnion) const
{
	Rect<TYPE> t (toUnion);

	if (left != 0 || top != 0 || right != 0 || bottom != 0) {
		t.left = Min (left, t.left);
		t.top = Min (top, t.top);
		t.right = Max (right, t.right);
		t.bottom = Max (bottom, t.bottom);
	}

	return t;
}


template <class TYPE>
Rect<TYPE>	Rect<TYPE>::Union (const Point<TYPE>& p) const
{
	Rect<TYPE> toUnion (p);
	Rect<TYPE> t (toUnion);

	if (left != 0 || top != 0 || right != 0 || bottom != 0) {
		t.left = Min (left, t.left);
		t.top = Min (top, t.top);
		t.right = Max (right, t.right);
		t.bottom = Max (bottom, t.bottom);
	}

	return t;
}


template <class TYPE>
Rect<TYPE>	Rect<TYPE>::Intersection (const Rect<TYPE>& toIntersect) const
{
	if (!IsOverlapping (toIntersect))
		return Rect<TYPE> ();

	Rect<TYPE> t (toIntersect);

	if (left != 0 || top != 0 || right != 0 || bottom != 0) {
		t.left = Max (left, t.left);
		t.top = Max (top, t.top);
		t.right = Min (right, t.right);
		t.bottom = Min (bottom, t.bottom);
	} else {
		t.Reset ();
	}

	return t;
}


template <class TYPE>
void	Rect<TYPE>::Unify (const Rect<TYPE>& toUnify)
{
	if (left != 0 || top != 0 || right != 0 || bottom != 0) {
		left = Min (left, toUnify.left);
		top = Min (top, toUnify.top);
		right = Max (right, toUnify.right);
		bottom = Max (bottom, toUnify.bottom);
	} else {
		Set (toUnify.left, toUnify.top, toUnify.right, toUnify.bottom);
	}

	return;
}


template <class TYPE>
void	Rect<TYPE>::Unify (const Point<TYPE>& p)
{
	if (left != 0 || top != 0 || right != 0 || bottom != 0) {	// TZs SPEED: 16007
		left = Min (left, p.GetX ());
		top = Min (top, p.GetY ());
		right = Max (right, p.GetX ());
		bottom = Max (bottom, p.GetY ());
	} else {
		Set (p.GetX (), p.GetY (), p.GetX (), p.GetY ());
	}

	return;
}


template <class TYPE>
void	Rect<TYPE>::Intersect (const Rect<TYPE>& toIntersect)
{
	if (!IsOverlapping (toIntersect)) {
		*this = Rect <TYPE> ();
	}

	if (left != 0 || top != 0 || right != 0 || bottom != 0) {
		left = Max (left, toIntersect.left);
		top = Max (top, toIntersect.top);
		right = Min (right, toIntersect.right);
		bottom = Min (bottom, toIntersect.bottom);
	} else {
		Reset ();
	}

	return;
}

}	// namespace GS

#endif
