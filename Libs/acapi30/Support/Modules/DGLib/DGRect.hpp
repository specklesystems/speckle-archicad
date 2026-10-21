// *********************************************************************************************************************
// File:			DGRect.hpp
//
// Description:		Rect related classes
//
// *********************************************************************************************************************

#ifndef DGRECT_HPP
#define DGRECT_HPP

#pragma once


#include "Definitions.hpp"
#include "DGNativeUnit.hpp"
#include "Rect.hpp"


namespace GS {
	class ObjectState;
	class IChannel;
	class OChannel;
}

namespace DG {
	class Rect;
	class NativeRect;
}


namespace DG {

// === class TRect =====================================================================================================

template<typename TYPE>
class TRect
{
protected:
	TYPE	left;
	TYPE	top;
	TYPE	right;
	TYPE	bottom;

	void	Normalize (void);

public:
	TRect ();
	TRect (const TPoint<TYPE>& pt1, const TPoint<TYPE>& pt2);
	TRect (const TPoint<TYPE>& pt, const TYPE& width, const TYPE& height);
	TRect (const TYPE& left, const TYPE& top, const TYPE& right, const TYPE& bottom);
	virtual	~TRect ();

	bool	operator== (const TRect<TYPE>& rightOp) const;
	bool	operator!= (const TRect<TYPE>& rightOp) const;

	void	Set (const TRect<TYPE>& sourceRect);
	void	Set (const TPoint<TYPE>& pt1, const TPoint<TYPE>& pt2);
	void	Set (const TPoint<TYPE>& pt, const TYPE& width, const TYPE& height);
	void	Set (const TYPE& left, const TYPE& top, const TYPE& right, const TYPE& bottom);

	void	SetLeft (const TYPE& left);
	TYPE	GetLeft (void) const;

	void	SetTop (const TYPE& top);
	TYPE	GetTop (void) const;

	void	SetRight (const TYPE& right);
	TYPE	GetRight (void) const;

	void	SetBottom (const TYPE& bottom);
	TYPE	GetBottom (void) const;

	void	SetLeftTop (const TPoint<TYPE>& pt);
	TPoint<TYPE>	GetLeftTop (void) const;

	void	SetLeftBottom (const TPoint<TYPE>& pt);
	TPoint<TYPE>	GetLeftBottom (void) const;

	void	SetRightTop (const TPoint<TYPE>& pt);
	TPoint<TYPE>	GetRightTop (void) const;

	void	SetRightBottom (const TPoint<TYPE>& pt);
	TPoint<TYPE>	GetRightBottom (void) const;

	void	SetCenter (const TPoint<TYPE>& pt);
	TPoint<TYPE>	GetCenter (void) const;

	void	SetWidth (const TYPE& width);
	TYPE	GetWidth (void) const;

	void	SetHeight (const TYPE& height);
	TYPE	GetHeight (void) const;

	void	SetSize (const TYPE& width, const TYPE& height);

	void	Move (const TYPE& dx, const TYPE& dy);
	void	Offset (const  TPoint<TYPE>& pt);
	TRect<TYPE>	GetOffsetedRect (const  TPoint<TYPE>& pt) const;

	void	Resize (const TYPE& dx, const TYPE& dy);
	void	Inflate (const TYPE& dx, const TYPE& dy);

	bool	IsEmpty (void) const;
	bool	Contains (const TPoint<TYPE>& pt) const;
	bool	Contains (const TYPE& x, const TYPE& y) const;

	GS::Rect<TYPE>	ToGSRect (void) const;

	template<typename TOTYPE>
	GS::Rect<TOTYPE> ToGSRect (void) const;

	bool		IsIntersecting (const TRect<TYPE>& otherRect) const;
	TRect<TYPE>	Intersect (const TRect<TYPE>& otherRect) const;
	TRect<TYPE> Unify (const TRect<TYPE>& otherRect) const;
};


template <typename TYPE>
void	TRect<TYPE>::Normalize (void)
{
	if (top > bottom) {
		TYPE t = top;
		top = bottom;
		bottom = t;
	}
	if (left > right) {
		TYPE t = left;
		left = right;
		right = t;
	}
}


template <typename TYPE>
TRect<TYPE>::TRect ():
	left (0),
	top (0),
	right (0),
	bottom (0)
{
}


template <typename TYPE>
TRect<TYPE>::TRect (const TPoint<TYPE>& pt1, const TPoint<TYPE>& pt2):
	left (pt1.GetX ()),
	top (pt1.GetY ()),
	right (pt2.GetX ()),
	bottom (pt2.GetY ())
{
	Normalize ();
}


template <typename TYPE>
TRect<TYPE>::TRect (const TPoint<TYPE>& pt, const TYPE& width, const TYPE& height):
	left (pt.GetX ()),
	top (pt.GetY ()),
	right (left + width),
	bottom (top + height)
{
	Normalize ();
}


template <typename TYPE>
TRect<TYPE>::TRect (const TYPE& left, const TYPE& top, const TYPE& right, const TYPE& bottom):
	left (left),
	top (top),
	right (right),
	bottom (bottom)
{
	Normalize ();
}


template <typename TYPE>
TRect<TYPE>::~TRect ()
{
}


template <typename TYPE>
bool	TRect<TYPE>::operator== (const TRect<TYPE>& rightOp) const
{
	return (left == rightOp.left && right == rightOp.right && top == rightOp.top && bottom == rightOp.bottom);
}


template <typename TYPE>
bool	TRect<TYPE>::operator!= (const TRect<TYPE>& rightOp) const
{
	return (left != rightOp.left || right != rightOp.right || top != rightOp.top || bottom != rightOp.bottom);
}

template <typename TYPE>
void	TRect<TYPE>::Set (const TRect<TYPE>& sourceRect)
{
	left   = sourceRect.GetLeft ();
	top    = sourceRect.GetTop ();
	right  = sourceRect.GetRight ();
	bottom = sourceRect.GetBottom ();

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::Set (const TPoint<TYPE>& pt1, const TPoint<TYPE>& pt2)
{
	left   = pt1.GetX ();
	top    = pt1.GetY ();
	right  = pt2.GetX ();
	bottom = pt2.GetY ();

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::Set (const TPoint<TYPE>& pt, const TYPE& width, const TYPE& height)
{
	left   = pt.GetX ();
	top    = pt.GetY ();
	right  = left + width;
	bottom = top + height;

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::Set (const TYPE& left, const TYPE& top, const TYPE& right, const TYPE& bottom)
{
	this->left   = left;
	this->top    = top;
	this->right  = right;
	this->bottom = bottom;

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::SetLeft (const TYPE& left)
{
	this->left = left;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetLeft (void) const
{
	return left;
}


template <typename TYPE>
void	TRect<TYPE>::SetTop (const TYPE& top)
{
	this->top = top;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetTop (void) const
{
	return top;
}


template <typename TYPE>
void	TRect<TYPE>::SetRight (const TYPE& right)
{
	this->right = right;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetRight (void) const
{
	return right;
}


template <typename TYPE>
void	TRect<TYPE>::SetBottom (const TYPE& bottom)
{
	this->bottom = bottom;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetBottom (void) const
{
	return bottom;
}


template <typename TYPE>
void	TRect<TYPE>::SetLeftTop (const TPoint<TYPE>& pt)
{
	left = pt.GetX ();
	top  = pt.GetY ();

	Normalize ();
}


template <typename TYPE>
TPoint<TYPE>	TRect<TYPE>::GetLeftTop (void) const
{
	return TPoint<TYPE> (left, top);
}


template <typename TYPE>
void	TRect<TYPE>::SetLeftBottom (const TPoint<TYPE>& pt)
{
	left   = pt.GetX ();
	bottom = pt.GetY ();

	Normalize ();
}


template <typename TYPE>
TPoint<TYPE>	TRect<TYPE>::GetLeftBottom (void) const
{
	return TPoint<TYPE> (left, bottom);
}


template <typename TYPE>
void	TRect<TYPE>::SetRightTop (const TPoint<TYPE>& pt)
{
	right = pt.GetX ();
	top   = pt.GetY ();

	Normalize ();
}


template <typename TYPE>
TPoint<TYPE>	TRect<TYPE>::GetRightTop (void) const
{
	return TPoint<TYPE> (right, top);
}


template <typename TYPE>
void	TRect<TYPE>::SetRightBottom (const TPoint<TYPE>& pt)
{
	right  = pt.GetX ();
	bottom = pt.GetY ();

	Normalize ();
}


template <typename TYPE>
TPoint<TYPE>	TRect<TYPE>::GetRightBottom (void) const
{
	return TPoint<TYPE> (right, bottom);
}


template <typename TYPE>
void	TRect<TYPE>::SetCenter (const TPoint<TYPE>& pt)
{
	TYPE width = right - left;
	left  = pt.GetX () - width / 2;
	right = left + width;

	TYPE height = bottom - top;
	top    = pt.GetY () - height / 2;
	bottom = top + height;

	Normalize ();
}


template <typename TYPE>
TPoint<TYPE>	TRect<TYPE>::GetCenter (void) const
{
	return TPoint<TYPE> ((left + right) / 2, (top + bottom) / 2);
}


template <typename TYPE>
void	TRect<TYPE>::SetWidth (const TYPE& width)
{
	right = left + width;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetWidth (void) const
{
	return right - left;
}


template <typename TYPE>
void	TRect<TYPE>::SetHeight (const TYPE& height)
{
	bottom = top + height;

	Normalize ();
}


template <typename TYPE>
TYPE	TRect<TYPE>::GetHeight (void) const
{
	return bottom - top;
}


template <typename TYPE>
void	TRect<TYPE>::SetSize (const TYPE& width, const TYPE& height)
{
	right  = left + width;
	bottom = top + height;

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::Move (const TYPE& dx, const TYPE& dy)
{
	left   = left + dx;
	right  = right + dx;
	top    = top + dy;
	bottom = bottom + dy;
}


template <typename TYPE>
void	TRect<TYPE>::Offset (const  TPoint<TYPE>& pt)
{
	Move (pt.GetX (), pt.GetY ());
}


template <typename TYPE>
TRect<TYPE>	TRect<TYPE>::GetOffsetedRect (const TPoint<TYPE>& pt) const
{
	TRect<TYPE>	rect = *this;
	rect.Offset (pt);
	return rect;
}


template <typename TYPE>
void	TRect<TYPE>::Resize (const TYPE& dx, const TYPE& dy)
{
	right  = right + dx;
	bottom = bottom + dy;

	Normalize ();
}


template <typename TYPE>
void	TRect<TYPE>::Inflate (const TYPE& dx, const TYPE& dy)
{
	left   = left - dx;
	right  = right + dx;
	top    = top - dy;
	bottom = bottom + dy;

	Normalize ();
}


template <typename TYPE>
bool	TRect<TYPE>::IsEmpty (void) const
{
	return left == right || top == bottom;
}


template <typename TYPE>
bool	TRect<TYPE>::Contains (const TPoint<TYPE>& pt) const
{
	return left <= pt.GetX () && right >= pt.GetX () && top <= pt.GetY () && bottom >= pt.GetY ();
}


template <typename TYPE>
bool	TRect<TYPE>::Contains (const TYPE& x, const TYPE& y) const
{
	return left <= x && right >= x && top <= y && bottom >= y;
}


template <typename TYPE>
bool	TRect<TYPE>::IsIntersecting (const TRect<TYPE>& other) const
{
	bool horizontalExcluded = left > other.right || right < other.left;
	bool verticalExcluded = top > other.bottom || bottom < other.top;

	return !horizontalExcluded && !verticalExcluded;
}


template <typename TYPE>
TRect<TYPE>		TRect<TYPE>::Intersect (const TRect<TYPE>& other) const
{
	if (!IsIntersecting (other)) {
		return {};
	}

	TRect<TYPE> intersectionRect;

	TYPE interLeft = GS::Max (left, other.left);
	TYPE interRight = GS::Min (right, other.right);
	TYPE interTop = GS::Max (top, other.top);
	TYPE interBottom = GS::Min (bottom, other.bottom);

	intersectionRect.Set (interLeft, interTop, interRight, interBottom);

	return intersectionRect;
}


template <typename TYPE>
TRect<TYPE>		TRect<TYPE>::Unify (const TRect<TYPE>& other) const
{
	TRect<TYPE> unionRect;

	TYPE interLeft = GS::Min (left, other.left);
	TYPE interRight = GS::Max (right, other.right);
	TYPE interTop = GS::Min (top, other.top);
	TYPE interBottom = GS::Max (bottom, other.bottom);

	unionRect.Set (interLeft, interTop, interRight, interBottom);

	return unionRect;
}


template <typename TYPE>
GS::Rect<TYPE>	TRect<TYPE>::ToGSRect (void) const
{
	return GS::Rect<TYPE> (left, top, right, bottom);
}


template <typename TYPE>
template <typename TOTYPE>
GS::Rect<TOTYPE> TRect<TYPE>::ToGSRect (void) const
{
	return GS::Rect<TOTYPE> (static_cast<TOTYPE> (left), static_cast<TOTYPE> (top), static_cast<TOTYPE> (right), static_cast<TOTYPE> (bottom));
}


// === class Rect ======================================================================================================

class DG_DLL_EXPORT Rect: public TRect<short>
{
public:
	Rect () { }
	Rect (const TRect<short>& source): TRect<short> (source) { }
	Rect (const Point& pt1, const Point& pt2): TRect<short> (pt1, pt2) { }
	Rect (const Point& pt, const short width, short height): TRect<short> (pt, width, height) { }
	Rect (short left, short top, short right, short bottom): TRect<short> (left, top, right, bottom) { }
	virtual ~Rect ();

	NativeRect	Scale (double scaleFactor) const;

	GSErrCode	Read (GS::IChannel& ic)
	{
		GSErrCode err = NoError;
		err = ic.Read (left);	if (err != NoError)	return err;
		err = ic.Read (top);	if (err != NoError)	return err;
		err = ic.Read (right);	if (err != NoError)	return err;
		err = ic.Read (bottom);
		return err;
	}

	GSErrCode	Write (GS::OChannel& oc) const
	{
		GSErrCode err = NoError;
		err = oc.Write (left);	if (err != NoError)	return err;
		err = oc.Write (top);	if (err != NoError)	return err;
		err = oc.Write (right);	if (err != NoError)	return err;
		err = oc.Write (bottom);
		return err;
	}

	GSErrCode	Store (GS::ObjectState& os) const
	{
		os.Add ("x", left);
		os.Add ("y", top);
		os.Add ("width", right - left);
		os.Add ("height", bottom - top);

		return NoError;
	}
};


// --- class DG::NativeRect --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT NativeRect: public TRect<NativeUnit>
{
public:
	NativeRect () { }
	NativeRect (const TRect<NativeUnit>& source): TRect<NativeUnit> (source) { }
	NativeRect (const NativePoint& pt1, const NativePoint& pt2): TRect<NativeUnit> (pt1, pt2) { }
	NativeRect (const NativePoint& pt, const NativeUnit& width, const NativeUnit& height): TRect<NativeUnit> (pt, width, height) { }
	NativeRect (const NativeUnit& left, const NativeUnit& top, const NativeUnit& right, const NativeUnit& bottom): TRect<NativeUnit> (left, top, right, bottom) { }
	virtual ~NativeRect ();

	Rect	Scale (double scaleFactor) const;

	GSErrCode	Read (GS::IChannel& ic)
	{
		GSErrCode err = NoError;
		err = left.Read (ic);	if (err != NoError)	return err;
		err = top.Read (ic);	if (err != NoError)	return err;
		err = right.Read (ic);	if (err != NoError)	return err;
		err = bottom.Read (ic);
		return err;
	}

	GSErrCode	Write (GS::OChannel& oc) const
	{
		GSErrCode err = NoError;
		err = left.Write (oc);	if (err != NoError)	return err;
		err = top.Write (oc);	if (err != NoError)	return err;
		err = right.Write (oc);	if (err != NoError)	return err;
		err = bottom.Write (oc);
		return err;
	}

	GSErrCode	Store (GS::ObjectState& os) const
	{
		os.Add ("x", left.GetValue ());
		os.Add ("y", top.GetValue ());
		os.Add ("width", right.GetValue () - left.GetValue ());
		os.Add ("height", bottom.GetValue () - top.GetValue ());

		return NoError;
	}
};

} //namespace DG


#endif
