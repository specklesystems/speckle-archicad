// *********************************************************************************************************************
// File:			DGPoint.hpp
//
// Description:		Point related classes
//
// *********************************************************************************************************************

#ifndef DGPOINT_HPP
#define DGPOINT_HPP

#pragma once

#include "Definitions.hpp"
#include "DGNativeUnit.hpp"


namespace GS {
	class ObjectState;
	class IChannel;
	class OChannel;
}

namespace DG {
	class Point;
	class NativePoint;
}


namespace DG {

// === class TPoint ====================================================================================================

template<typename TYPE>
class TPoint
{
protected:
	TYPE	x;
	TYPE	y;

public:
	TPoint ();
	TPoint (const TYPE& x, const TYPE& y);
	virtual	~TPoint ();

	bool	operator== (const TPoint<TYPE>& rightOp) const;
	bool	operator!= (const TPoint<TYPE>& rightOp) const;

	void	Set (const TYPE& x, const TYPE& y);

	void	SetX (const TYPE& x);
	TYPE	GetX (void) const;

	void	SetY (const TYPE& y);
	TYPE	GetY (void) const;

	void	Offset (const TYPE& dx, const TYPE& dy);
};


template <typename TYPE>
TPoint<TYPE>::TPoint ():
	x (0),
	y (0)
{
}


template <typename TYPE>
TPoint<TYPE>::TPoint (const TYPE& x, const TYPE& y):
	x (x),
	y (y)
{
}


template <typename TYPE>
TPoint<TYPE>::~TPoint ()
{
}


template <typename TYPE>
bool	TPoint<TYPE>::operator== (const TPoint<TYPE>& rightOp) const
{
	return (x == rightOp.x && y == rightOp.y);
}


template <typename TYPE>
bool	TPoint<TYPE>::operator!= (const TPoint<TYPE>& rightOp) const
{
	return (x != rightOp.x || y != rightOp.y);
}


template <typename TYPE>
void	TPoint<TYPE>::Set (const TYPE& x, const TYPE& y)
{
	this->x = x;
	this->y = y;
}


template <typename TYPE>
void	TPoint<TYPE>::SetX (const TYPE& x)
{
	this->x = x;
}


template <typename TYPE>
TYPE	TPoint<TYPE>::GetX (void) const
{
	return x;
}


template <typename TYPE>
void	TPoint<TYPE>::SetY (const TYPE& y)
{
	this->y = y;
}


template <typename TYPE>
TYPE	TPoint<TYPE>::GetY (void) const
{
	return y;
}


template <typename TYPE>
void	TPoint<TYPE>::Offset (const TYPE& dx, const TYPE& dy)
{
	x = x + dx;
	y = y + dy;
}


// === class Point =====================================================================================================

class DG_DLL_EXPORT Point: public TPoint<short>
{
public:
	Point () { }
	Point (const TPoint<short>& source): TPoint<short> (source) { }
	Point (short x, short y): TPoint<short> (x, y) { }
	virtual ~Point ();

	NativePoint	Scale (double scaleFactor) const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);
};


// === class NativePoint ===============================================================================================

class DG_DLL_EXPORT NativePoint: public TPoint<NativeUnit>
{
public:
	NativePoint () { }
	NativePoint (const TPoint<NativeUnit>& source): TPoint<NativeUnit> (source) { }
	NativePoint (const NativeUnit& x, const NativeUnit& y): TPoint<NativeUnit> (x, y) { }
	virtual ~NativePoint ();

	Point	Scale (double scaleFactor) const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);
};

} // namespace DG

#endif
