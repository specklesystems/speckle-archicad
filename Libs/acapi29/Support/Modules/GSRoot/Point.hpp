// *****************************************************************************
//
//								Point class
//
// Module:			AC
// Namespace:		-
// Contact person:	AZS
//
// SG compatible
//
// *****************************************************************************

#ifndef POINT_HPP
#define POINT_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

// --- Declarations ------------------------------------------------------------

namespace GS {

// --- Class declarations ------------------------------------------------------

// --- Point -------------------------------------------------------------------

template<class TYPE>
class Point {
private:
	TYPE	x;
	TYPE	y;

public:
	Point ();
	Point (const TYPE& newX, const TYPE& newY);

	void	Set (const TYPE& newX, const TYPE& newY);

	TYPE	GetX (void) const;
	TYPE	GetY (void) const;

	void	SetX (const TYPE& newX);
	void	SetY (const TYPE& newY);

	void	Offset (const TYPE& deltaX, const TYPE& deltaY);

	bool	operator== (const Point<TYPE>&) const;
	bool	operator!= (const Point<TYPE>&) const;
};


// --- Public methods ----------------------------------------------------------

template <class TYPE>
Point<TYPE>::Point ():
	x (0),
	y (0)
{
}


template <class TYPE>
Point<TYPE>::Point (const TYPE& newX, const TYPE& newY):
	x (newX),
	y (newY)
{
}


template <class TYPE>
void	Point<TYPE>::Set (const TYPE& newX, const TYPE& newY)
{
	x = newX;
	y = newY;
}


template <class TYPE>
TYPE	Point<TYPE>::GetX (void) const
{
	return x;
}


template <class TYPE>
TYPE	Point<TYPE>::GetY (void) const
{
	return y;
}


template <class TYPE>
void	Point<TYPE>::SetX (const TYPE& newX)
{
	x = newX;
}


template <class TYPE>
void	Point<TYPE>::SetY (const TYPE& newY)
{
	y = newY;
}


template <class TYPE>
void	Point<TYPE>::Offset (const TYPE& deltaX, const TYPE& deltaY)
{
	x += deltaX;
	y += deltaY;
}


template <class TYPE>
bool	Point<TYPE>::operator== (const Point<TYPE>& p) const
{
	return x == p.x && y == p.y;
}


template <class TYPE>
bool	Point<TYPE>::operator!= (const Point<TYPE>& p) const
{
	return x != p.x || y != p.y;
}

}

#endif
