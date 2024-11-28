// *********************************************************************************************************************
// File:			DGUtility.hpp
//
// Description:		Utility classes and functions
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM
//
// *********************************************************************************************************************

#ifndef DGUTILITY_HPP
#define DGUTILITY_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#if defined (WINDOWS)
#include "Win32UxInterface.hpp"
#include "DGWImageCache.hpp"
#endif

#include "Array.hpp"
#include "DG.h"
#include "NativeImage.hpp"
#include "Range.hpp"
#include "Rect.hpp"

// from RS
#include "RSIcon.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace Gfx {
	class Color;
}

namespace IO {
	class Location;
}

namespace NewDisplay {
	class NativeContext;
}

namespace DG {
	class Dialog;
	class Panel;
	class Item;
	class DragDropData;
	class ListBox;
	class ListView;
	class TreeView;
	class CommandDescriptor;
	class ListBoxItemUpdateEvent;
	class ListBoxTabItemUpdateEvent;
	class ShortcutScheme;
	class NativePoint;
	class NativeRect;
}

namespace DG {

// === RichEdit ========================================================================================================

// --- Definitions -----------------------------------------------------------------------------------------------------

namespace EOL {

	enum Type {
		Default	= DG_EOL_DEFAULT,
		CR		= DG_EOL_CR,
		CRLF	= DG_EOL_CRLF
	};

}	// namespace EOL


namespace Search {

	enum Dir {
		Down		= DG_RFT_DOWN,
		Up			= DG_RFT_UP
	};

	enum Case {
		InSensitive	= 0,
		Sensitive	= DG_RFT_MATCHCASE
	};

	enum Word {
		NoMatchWord	= 0,
		MatchWord	= DG_RFT_WHOLEWORD
	};

}	// namespace Search

namespace UC {

	enum UC257CellSkinType {
		FillSkin,
		EmptySkin,
		SurfaceSkin,
		MissingSkin,		// displaying a ? (on Building Materials)
		DefaultSkin			// displaying a -
	};

}	// namespace UC


typedef GS::Range<Int32> CharRange;


// === Key handling ====================================================================================================

// --- Definitions -----------------------------------------------------------------------------------------------------

enum EventHandlerResultType {
	NotProcessedEvent		= 0,
	ProcessedEvent			= 1,
	ForbidDGToHandleEvent	= 2
};

namespace Unit {

	enum Type {
		Unit_MM				= DG_UNIT_MM,
		Unit_CM				= DG_UNIT_CM,
		Unit_DM				= DG_UNIT_DM,
		Unit_M				= DG_UNIT_M,
		Unit_KM				= DG_UNIT_KM,

		Unit_DecInch		= DG_UNIT_DECINCH,
		Unit_FootInch		= DG_UNIT_FOOT_INCH,
		Unit_Inch			= DG_UNIT_INCH,
		Unit_FootDecInch	= DG_UNIT_FOOT_DECINCH,
		Unit_DecFoot		= DG_UNIT_DECFOOT,

		Unit_DecDegree		= DG_UNIT_DECDEGREE,
		Unit_DegMinSec		= DG_UNIT_DEGMINSEC,
		Unit_Grad			= DG_UNIT_GRAD,
		Unit_Radian			= DG_UNIT_RADIAN,
		Unit_Surveyors		= DG_UNIT_SURVEYORS

	};

}	// namespace Unit


namespace Key {

	enum Modifier {
		NoModifier	= 0,
		Command		= DG_MOD_COMMAND,
		Option		= DG_MOD_OPTION,
		Shift		= DG_MOD_SHIFT,
		Ctrl		= DG_MOD_CTRL
	};

	enum Special {
		Empty		= DG_KEY_EMPTY,
		Back		= DG_KEY_BACK,
		Tab			= DG_KEY_TAB,
		Enter		= DG_KEY_ENTER,
		Return		= DG_KEY_RETURN,
		Escape		= DG_KEY_ESCAPE,

		Left		= DG_KEY_LEFT,
		Right		= DG_KEY_RIGHT,
		Up			= DG_KEY_UP,
		Down		= DG_KEY_DOWN,

		Insert		= DG_KEY_INSERT,
		Delete		= DG_KEY_DELETE,
		Home		= DG_KEY_HOME,
		End			= DG_KEY_END,
		PageUp		= DG_KEY_PAGEUP,
		PageDown	= DG_KEY_PAGEDOWN,

		F1			= DG_KEY_F1,
		F2			= DG_KEY_F2,
		F3			= DG_KEY_F3,
		F4			= DG_KEY_F4,
		F5			= DG_KEY_F5,
		F6			= DG_KEY_F6,
		F7			= DG_KEY_F7,
		F8			= DG_KEY_F8,
		F9			= DG_KEY_F9,
		F10			= DG_KEY_F10,
		F11			= DG_KEY_F11,
		F12			= DG_KEY_F12,
		F13			= DG_KEY_F13,
		F14			= DG_KEY_F14,
		F15			= DG_KEY_F15,

		Help		= DG_KEY_HELP
	};


	// --- Code class declaration --------------------------------------------------------------------------------------

	class Code
	{
		Special		code;
		GS::UniChar	uniChar;

	public:
		inline				Code ();
		inline				Code (Special code);
		inline				Code (GS::UniChar code);

		inline bool			IsSpecial (void) const;
		inline GS::UniChar	GetUniChar (void) const;
		inline Special		GetSpecialKey (void) const;

		inline bool			operator== (const Code& op) const;
		inline bool			operator!= (const Code& op) const;

		inline GSErrCode	ReadOld (GS::IChannel& ic);
		inline GSErrCode	Read (GS::IChannel& ic);
		inline GSErrCode	Write (GS::OChannel& oc) const;
	};


	// --- Code class inline implementation ----------------------------------------------------------------------------

	inline Code::Code ()
	{
		this->code = Empty;
	}


	inline Code::Code (Special code)
	{
		this->code = code;
	}


	inline Code::Code (GS::UniChar uniChar)
	{
		this->code = Empty;
		this->uniChar = uniChar;
	}


	inline bool		Code::IsSpecial (void) const
	{
		return (code != Empty);
	}


	inline GS::UniChar		Code::GetUniChar (void) const
	{
		return uniChar;
	}


	inline Special	Code::GetSpecialKey (void) const
	{
		return code;
	}


	inline bool		Code::operator== (const Code& op) const
	{
		return (op.code == code && op.uniChar == uniChar);
	}


	inline bool		Code::operator!= (const Code& op) const
	{
		return (op.code != code || op.uniChar != uniChar);
	}


	inline GSErrCode	Code::ReadOld (GS::IChannel& ic)
	{
		short tmpCode;
		GSErrCode errCode = ic.Read (tmpCode);
		if (tmpCode < 0) {
			code = static_cast<Special> (tmpCode);
		} else {
			char chrStr[2];
			chrStr[0] = static_cast<char> (tmpCode);
			chrStr[1] = 0;
			GS::UniString tmp (chrStr, CC_System);
			if (tmp.GetLength () > 0)
				uniChar = tmp.GetChar (0);
		}
		return errCode;
	}


	inline GSErrCode	Code::Read (GS::IChannel& ic)
	{
		short tmpCode;
		GSErrCode errCode = ic.Read (tmpCode);
		if (errCode != NoError)
			return errCode;
		code = static_cast<Special> (tmpCode);
		GS::UniChar::Layout tmpLayout;
		errCode = ic.Read (tmpLayout);
		if (errCode == NoError)
			uniChar = tmpLayout;
		return errCode;
	}


	inline GSErrCode	Code::Write (GS::OChannel& oc) const
	{
		GSErrCode errCode = oc.Write (static_cast<short> (code));
		if (errCode != NoError)
			return errCode;
		return oc.Write (GS::UniChar::Layout (uniChar));
	}

}	// namespace Key


// --- Image class -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Image
{
protected:
	GSResModule		resModule;
	short			resId;
	const void*		data;

public:
	enum {
		NoImage		= DG_NO_IMAGE
	};
	Image ();
	Image (GSResModule resModule, short resId);
	explicit Image (const void* data);
	virtual	~Image ();

	bool	operator== (const Image& rightOp) const;
	bool	operator!= (const Image& rightOp) const;

	GSResModule		GetResourceModule (void) const;
	short			GetResourceId (void) const;
	const void*		GetData (void) const;

	bool			IsEmpty (void) const;
	virtual bool	IsValid (void) const;

	virtual GSErrCode		Store (GS::ObjectState& os) const;
};


// --- Icon class ------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Icon: public Image
{
public:
	enum {
		NoIcon				= DG_NO_ICON,

		Error				= DG_ERROR_ICON,
		Information			= DG_INFORMATION_ICON,
		Warning				= DG_WARNING_ICON,

		File				= DG_FILE_ICON,
		TextFile			= DG_TEXTFILE_ICON,
		Folder				= DG_FOLDER_ICON,
		OpenedFolder		= DG_FOLDEROPEN_ICON,
		MyDocFolder			= DG_MYDOCFOLDER_ICON,
		Favorites			= DG_FAVORITES_ICON,
		Floppy				= DG_FLOPPY_ICON,
		CDDrive				= DG_CDDRIVE_ICON,
		HDDrive				= DG_HDD_ICON,
		NetDrive			= DG_NETDRIVE_ICON,
		Desktop				= DG_DESKTOP_ICON,
		RecycleBin			= DG_RECYCLEBIN_ICON,
		EntireNetwork		= DG_ENTIRENETWORK_ICON,
		FilledArrowLeft		= DG_FILLED_LEFT_ICON,
		FilledArrowRight	= DG_FILLED_RIGHT_ICON,
		FilledArrowDown		= DG_FILLED_DOWN_ICON,
		FishBoneArrowLeft	= DG_FISHBONE_LEFT_ICON,
		FishBoneArrowRight	= DG_FISHBONE_RIGHT_ICON,
		FishBoneArrowDown	= DG_FISHBONE_DOWN_ICON
	};

			 Icon ();
			 Icon (GSResModule resModule, short resId);
			 Icon (RS::Icon icon);
	explicit Icon (const void* data);
	virtual	~Icon ();

	virtual bool	IsValid (void) const override;

	GSErrCode		Store (GS::ObjectState& os) const override;

#if defined macintosh
	void			GetSize (Int32 *pWidth, Int32 *pHeight) const;
#endif

	static short	GetIdFromString (const GS::UniString& iconIdStr);
};


// --- Picture class ---------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Picture: public Image
{
public:
	enum {
		NoPicture	= DG_NO_IMAGE
	};

	Picture ();
//	explicit Picture (short resId);
	Picture (GSResModule resModule, short resId);
	explicit Picture (const void* data);
	virtual	~Picture ();

	GSErrCode		Store (GS::ObjectState& os) const override;
};


// --- NativeImage class -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT NativeImage
{
private:
	NewDisplay::NativeImage nativeImage;

#if defined (WINDOWS)
	HICON hIcon;
	UInt32 dpi;
	DG::ImageCache::Image image;
#endif

public:
	NativeImage ();
	NativeImage (const void* data, double resolutionFactor);
	NativeImage (GSResModule module, GSResID resID, double resolutionFactor);
	NativeImage (GSResModule module, GSResID resID, UInt32 desiredSizeX, UInt32 desiredSizeY, double resolutionFactor);
	NativeImage (const DG::Image& icon, double resolutionFactor);

	NativeImage (const NativeImage& other);
	NativeImage& operator= (const NativeImage& other);

	virtual ~NativeImage ();

	NewDisplay::NativeImage		GetNativeImage (void);
};


// --- Point class -----------------------------------------------------------------------------------------------------

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


// --- class DG::Point -------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Point: public TPoint<short> // Typedef won't work with DG_DLL_EXPORT
{
public:
	Point () { }
	Point (const TPoint<short>& source): TPoint<short> (source) { }
	Point (short x, short y): TPoint<short> (x, y) { }
	virtual ~Point ();

	NativePoint		Scale (double scaleFactor) const;


	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);
};


// --- class DG::NativePoint -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT NativePoint: public TPoint<NativeUnit> // Typedef won't work with DG_DLL_EXPORT
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


// --- Rect class ------------------------------------------------------------------------------------------------------

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


// --- class DG::Rect --------------------------------------------------------------------------------------------------

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


namespace DG {

// --- MousePosData class ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT MousePosData
{
private:
	DGMousePosData	data;
	bool			valid;

public:
	MousePosData ();

	bool		Retrieve (void);
	bool		Retrieve (const Panel& panel);
	bool		Retrieve (const Item& item);

	void		RetrieveFailSafe (void);
	void		RetrieveFailSafe (const Panel& panel);
	void		RetrieveFailSafe (const Item& item);

	Panel*		GetPanel (void) const;
	Item*		GetItem (void) const;

	Rect		GetRect (void) const;
	Point		GetMouseOffsetInLogicalUnits (void) const;
	NativePoint	GetMouseOffsetInNativeUnits (void) const;

	bool		IsCommandPressed (void) const;
	bool		IsOptionPressed (void) const;
	bool		IsShiftPressed (void) const;

	bool		IsLeftButtonPressed (void) const;
	bool		IsRightButtonPressed (void) const;
	bool		IsWheelButtonPressed (void) const;
};


// === Drag & Drop handling ============================================================================================

// --- Definitions -----------------------------------------------------------------------------------------------------

namespace DragDrop
{
	enum class Effect : UInt16 {
		Reject		= DG_DRAG_REJECT,
		Accept		= DG_DRAG_ACCEPT,
		Copy		= DG_DRAG_ACCEPT_COPY,
		Move		= DG_DRAG_ACCEPT_MOVE,
		CopyAndMove	= DG_DRAG_ACCEPT_COPY | DG_DRAG_ACCEPT_MOVE,
		Link		= DG_DRAG_ACCEPT_LINK,
		Delete		= DG_DRAG_DELETE
	};

	Effect operator| (Effect lhv, Effect rhv);
	Effect operator& (Effect lhv, Effect rhv);
	Effect operator|= (Effect& lhv, Effect rhv);
	Effect operator&= (Effect& lhv, Effect rhv);

	enum Feedback {
		AcceptSelAndIns	= 0,
		RejectSelection	= DG_DRAG_REJECT_SEL,
		RejectInsertion	= DG_DRAG_REJECT_INS,
		RejectSelAndIns	= DG_DRAG_REJECT_SEL | DG_DRAG_REJECT_INS
	};

	enum RelativePos {
		InsertOn	= DG_DRAG_INSERT_ON,
		InsertBelow	= DG_DRAG_INSERT_BELOW,
		InsertAbove = DG_DRAG_INSERT_ABOVE
	};

	enum Scope {
		Item		= DG_DRAG_SCOPE_ITEM,
		Dialog		= DG_DRAG_SCOPE_DIALOG,
		Module		= DG_DRAG_SCOPE_MODULE,
		Application	= DG_DRAG_SCOPE_APP,
		System		= DG_DRAG_SCOPE_SYSTEM
	};
}


// --- ItemDragDropData class ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemDragDropData
{
protected:
	mutable DragDropData* dragData;			//Mutable, because this object is updateable
	mutable bool		  isDataUpToDate;
	short				  mainDialId;

	explicit ItemDragDropData (Panel* source);

public:
	~ItemDragDropData ();

	bool	  HasDataFormat (DGDragFormat format) const;
	ULong	  GetDataSize (DGDragFormat format) const;
	bool	  GetData (DGDragFormat format, void* data, ULong size) const;
	bool	  GetFileData (DGDragFormat format, const GS::uchar_t* folderPath, void* data, ULong size) const;

	bool	  GetText (Int8* text, ULong size) const;

	ULong	  GetLocationCount (void) const;
	bool	  GetLocation (ULong index, IO::Location& location) const;	//must change to IO::Location*

	Item*	  GetSourceItem (void) const;
	ListBox*  GetListBoxSource (void) const;
	ListView* GetListViewSource (void) const;
	TreeView* GetTreeViewSource (bool externalEnabled = false) const;

	ULong	  GetItemCount (void) const;
	Int32	  GetTreeViewItem (ULong index) const;
	short	  GetListBoxItem (ULong index) const;
	short	  GetListViewItem (ULong index) const;
};


// --- DragSourceEventProperty class -----------------------------------------------------------------------------------

class DG_DLL_EXPORT DragSourceEventProperty
{
private:
	DragDropData*		dragData;
	DG::DragDropEventArg*	ddMsgData;
	GSPtr				fileData;

public:
	DragSourceEventProperty ();
	virtual ~DragSourceEventProperty ();

	void	Init (DG::DragDropEventArg* msgData);

	bool	SetData (DGDragFormat format, void* data, ULong size, DragDrop::Scope scope);
	bool	SetDelayedData (DGDragFormat format, DragDrop::Scope scope);
	void	SetLocationData (IO::Location *locArray, ULong nrOfLocations);
	bool	ModifyBaseFormat (DGDragFormat format, DragDrop::Scope scope);

	Point	GetSourcePosition (void) const;
	DGDragFormat		GetRequestedDragFormat (void) const;
	const GS::uchar_t*	GetFolderPath () const;
	void	SetSourceFeedback (const void* feedback, const DG::Rect* feedbackRect);
};


// --- DropTargetEventProperty class -----------------------------------------------------------------------------------

class DG_DLL_EXPORT DropTargetEventProperty: public ItemDragDropData
{
private:
	Point	targetPos;

protected:
	DropTargetEventProperty (const DG::EventArg& msgData, Panel* source);

public:
	virtual ~DropTargetEventProperty ();

	Point	GetTargetPosition (void) const;
};


// --- CompoundItemObserver class --------------------------------------------------------------------------------------

class DG_DLL_EXPORT CompoundItemObserver
{
protected:
	CompoundItemObserver ();

public:
	virtual	~CompoundItemObserver ();

	short	AttachToAllItems (const Panel& panel);
	short	DetachFromAllItems (const Panel& panel);
};


// --- SetAndRestoreEditUpdateDelay class ------------------------------------------------------------------------------

class DG_DLL_EXPORT SetAndRestoreEditUpdateDelay {
public:
	SetAndRestoreEditUpdateDelay (ULong newEditUpdateDelay = 0);
	~SetAndRestoreEditUpdateDelay ();

private:
	SetAndRestoreEditUpdateDelay (const SetAndRestoreEditUpdateDelay&);				// disabled
	SetAndRestoreEditUpdateDelay& operator= (const SetAndRestoreEditUpdateDelay&);	// disabled

	const ULong		mSavedEditUpdateDelay;
};


// --- Utils class (General utility functions) -------------------------------------------------------------------------

#if defined (macintosh)
enum VirtualCodes {
	CommandKey = 55,	// Command
	PeriodKey1 = 47,	// Period key
	PeriodKey2 = 65,	// Period key on Numpad
	SpaceKey   = 49,	// space
	InvalidVkCode = 255
};
#endif

class DG_DLL_EXPORT ScrollBarMetrics
{
public:
	Int32 hScrollHeight;
	Int32 vScrollWidth;
	Int32 hScrollArrowWidth;
	Int32 vScrollArrowHeight;

	ScrollBarMetrics ():
		hScrollHeight (0),
		vScrollWidth (0),
		hScrollArrowWidth (0),
		vScrollArrowHeight (0)
	{
	}
};

class DG_DLL_EXPORT Utils
{
public:
	enum SystemColorType {
		ShadowColorType,			// COLOR_3DSHADOW,		[NSColor shadowColor]
		FaceColorType,				// COLOR_3DFACE,		[NSColor gridColor]
		HighlightColorType,			// COLOR_HIGHLIGHT,		[NSColor selectedTextBackgroundColor]
		HighlightTextColorType,		// COLOR_HIGHLIGHTTEXT,	[NSColor selectedMenuItemTextColor]
		ForegroundTextColorType,	// COLOR_WINDOWTEXT,	[NSColor controlTextColor]
		DisabledTextColorType,		// COLOR_GRAYTTEXT,		[NSColor controlTextColor]
		LightHighlightColorType,	// COLOR_3DHILIGHT,		[NSColor controlLightHighlightColor]
		DarkHighlightColorType,		// COLOR_3DHILIGHT,		[NSColor controlLightHighlightColor]
		ListItemBackgroundColorType,// COLOR_WINDOW,		[NSColor controlBackgroundColor]
		StandardTextColor,
		StandardGrayTextColor,
		StandardTextBackgroundColor,
		TrackerTextColorType,
		TrackerBackgroundColorType,
		TrackerFrameColorType
	};

	enum Alignment {
		RightTopOrLeftTop,				// Place dialog on the right of the control if possible (it has enough place), and if not, then to the left side of it. Top edges aligned.
		RightBottomOrLeftBottom,		// Place dialog on the right of the control if possible (it has enough place), and if not, then to the left side of it. Bottom edges aligned.
		LeftTopOrRightTop,				// Place dialog on the left of the control if possible (it has enough place), and if not, then to the right side of it. Top edges aligned.
		RightCenter,					// Place dialog on the right of the control, center aligned
		BottomLeftRightOrTopLeftRight,	// Place dialog on the bottom of the control, left edges aligned if possible, and if not, then in order to the right edges are aligned
										// If this is not succeed, than the try top aligning
		BottomRight,					// Place dialog on the bottom of the control, right edges aligned
		OnlyKeepRectInScreen			// Place dialog on the screen fitting in it. No alignment, no passing to some item
	};

public:
	// --- Set parent window of a DG dialog opened from a system dialog ------------------------------------------------

	class DG_DLL_EXPORT SetNextModalParentGuard
	{
	private:
		const void* lastWindow;
		SetNextModalParentGuard () { }	// Disable default consrtuction

	public:
		SetNextModalParentGuard (const void* parentWindow);
		virtual ~SetNextModalParentGuard ();
	};

	// --- Image utilities ---------------------------------------------------------------------------------------------

	static void 		DrawIcon (void* drawContext, const DG::Rect& contextRect, const DG::Icon& icon, double resolutionFactor = 1.0, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
	static void			DrawIcon (NewDisplay::NativeContext& context, const DG::Rect& rect, const NewDisplay::NativeImage& nativeImage, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
	static void			DrawIcon (NewDisplay::NativeContext& context, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);

	static bool			GetIconInfo (const DG::Icon& icon, Int32 *pWidth, Int32 *pHeight);

	static void			DestroyDGIcon (Icon& icon);

	static DG::Icon		CreateIconFromNativeImage (const NewDisplay::NativeImage& nativeImage);
	static DG::Icon		CreateIconFromPict (const DG::Picture* picture, const Gfx::Color* transparentColor);

#if defined (WINDOWS)
	static bool			IsIconFullyTransparent (HICON hIcon);

	static void			PremultiplyBitmapAlpha (HBITMAP hBmp);
	static HICON 		PrepareIconForDisabledDraw (HICON hIcon);
	static HICON 		FixMaskedIcon (HICON hIcon);
	static HBITMAP 		CreateDisabledBitmapOfIcon (HICON hIcon);
	static HBITMAP 		CreateDisabledBitmapOfBitmap (HBITMAP hBitmap);
	static HICON 		CreateIconWithOverlay (HICON hIcon, HICON hOverlayIcon);

	static HBITMAP 		CreateCenteredBitmapFromIcon (HICON origIcon, int newBitmapWidth, int newBitmapHeight);

	static void 		DestroyImageList (HIMAGELIST hImageList);

	static void 		DrawIcon (HDC hDC, const DG::Rect& rc, const HICON hIcon, bool isDisabled = false, short hAlignment = DG_IS_CENTER, short vAlignment = DG_IS_VCENTER);
	static void 		DrawIcon (HICON hIcon, HDC hDC, const RECT *rc);
	static BOOL 		DrawIcon (HDC hDC, UINT xDst, UINT yDst, UINT cxDst, UINT cyDst, HICON hIcon, UINT xSrc, UINT ySrc, BOOL disabled);
	static BOOL 		DrawIconCenter (HDC hDC, RECT *rcDst, HICON hIcon, UINT xSrc, UINT ySrc, UINT cxSrc, UINT cySrc, BOOL disabled);

	static bool 		DrawThemeIcon (HTHEME hTheme, int partId, int stateId, HDC hDC, UINT xDst, UINT yDst, UINT cxDst, UINT cyDst,
									   HICON hIcon, UINT xSrc, UINT ySrc, BOOL disabled);
	static bool 		DrawThemeIconCenter (HTHEME hTheme, int partId, int stateId, HDC hDC, RECT *rcDst,
											 HICON hIcn, UINT xSrc, UINT ySrc, UINT cxSrc, UINT cySrc, BOOL disabled);

	static bool 		DrawThemeBitmap (HTHEME hTheme, int partId, int stateId, HDC hDC, UINT xDst, UINT yDst, UINT cxDst, UINT cyDst,
		HBITMAP hBitmap, UINT xSrc, UINT ySrc, BOOL disabled);
	static BOOL 		DrawThemeBitmapCenter (HTHEME hTheme, int partId, int stateId, HDC hDC, RECT *rcDst, HBITMAP hBitmap,
		UINT xSrc, UINT ySrc, UINT cxSrc, UINT cySrc, BOOL disabled);

	static bool 		GetIconData (const HICON hIcon, Int32* width, Int32* height, bool* isColor = nullptr, HBITMAP* hcBmp = nullptr, HBITMAP* hmBmp = nullptr);

 	static void			FillRect (HDC context, double resolutionFactor, const DG::Rect& rect, const Gfx::Color& color, bool drawFrame = false, bool roundEdge = false, bool modifyColorForDisabledControl = false);
#endif

	// --- Drawing utilities -------------------------------------------------------------------------------------------

	static void			FillRect (NewDisplay::NativeContext& context, const DG::Rect& rect, const Gfx::Color& color, bool drawFrame = false, bool roundEdge = false, bool modifyColorForDisabledControl = false);
	static void         FillRectWithSystemColor (NewDisplay::NativeContext& context, const DG::Rect& rect, SystemColorType type);

	// --- Text utilities ----------------------------------------------------------------------------------------------
	static Gfx::Color	GetSystemColor (SystemColorType type);
	static bool 		CanTextFitInArea (const GS::UniString& inText, const DG::Rect& inRect, bool wrappingItem, short inFontType, const double scaleFactor);
	//static GS::UniString WordWrapTextToWidth (const GS::UniString& inText, const short maxWidth, short inFontType, const GS::UniString& separatorStr);
	static void			DrawText (NewDisplay::NativeContext& context, const DG::Rect& rect, const GS::UniString& text, short inFontType, short alignment, bool endEllipsis = false, const Gfx::Color* color = nullptr);
	static void			DrawTextWithSystemColor (NewDisplay::NativeContext& context, const DG::Rect& rect, const GS::UniString& text, SystemColorType type, short inFontType, short alignment, bool endEllipsis = false);
	static DG::Rect 	GetTextDimensions (const GS::UniString& inText, short inFontType, short inMaxWidth, short inMaxHeight, const double scaleFactor, bool wrapText);

#if defined (WINDOWS)
	static bool			GetTruncatedText (HTHEME hTheme, HDC hDC, int partId, int stateId, const wchar_t* pTextIn, const RECT* rc, short truncMode, wchar_t* pTextOut);
#endif

	// --- Other utilities ---------------------------------------------------------------------------------------------

	static GS::UniString	GetShortcutText		(const CommandDescriptor* cmdDesc, bool inBracket, const DG::ShortcutScheme* shortcutScheme = nullptr);
	static GS::UniString	GetShortcutListText (const CommandDescriptor* cmdDesc, bool inBracket, GS::UniString delimiter, const DG::ShortcutScheme* shortcutScheme = nullptr);

	static bool			GetKeyState (Key::Modifier modifier, bool asyncRead = true);
	static bool			GetKeyState (const Key::Code& key, bool asyncRead = true);

	static bool			IsModifierKeyPressed ();

	static ScrollBarMetrics		GetScrollBarSizes (double scaleFactor);

	static ULong		GetDoubleClickTime (void);

	static Gfx::Color	GetListBoxSectionHeaderBackgroundColor (const ListBox& listBox, short itemIndex);

	static Int32		GetRealDisplayDigits ();

#if defined (WINDOWS)
	static GS::UniString	GetGUIResourceUsageInfo (void);
#endif

	static double		GetInitialToolTipDelay ();
	static double		GetToolTipToToolTipDelay ();

	// --- Dialog utilities --------------------------------------------------------------------------------------------

	static void		CalcDialogMaxClientSize (const DG::Dialog& dialog, short& maxClientWidth, short& maxClientHeight);

	static void		KeepRectInBoundingRect (DG::NativeRect& nativeRect, const DG::NativeRect& boundingRect);

	static void		PlaceDialogNextToNativeRect (DG::Dialog& dialog, const DG::NativeRect& nativeRect, Alignment alignment);
	static void		PlaceDialogNextToItem (DG::Dialog& dialog, const DG::Item& item, Alignment alignment);
	static void		PlaceDialogNextToItem (DG::Dialog& dialog, short dialogId, short itemId, Alignment alignment);
	static void		PlaceDialogNextToItems (DG::Dialog& dialog, const DG::Item& leftItem, const DG::Item& rightItem);

	static void		PlaceDialogToMousePos (DG::Dialog& dialog, const DG::NativeUnit& xOffset = DG::NativeUnit (), const DG::NativeUnit& yOffset = DG::NativeUnit (), Alignment alignment = RightTopOrLeftTop);

	// --- Drawing arrows ----------------------------------------------------------------------------------------------

	enum ArrowOrientation {
		Left,
		Right,
		Down
	};

	enum ArrowType {
		Opened,
		Filled
	};

#if defined (WINDOWS)
	static void		DrawArrow (HDC hDC, RECT  arrowRect,	 ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, bool disabled = false);
	static void		DrawArrow (HDC hDC, POINT arrowTipCoord, ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, bool disabled = false);

	static bool		GetArrowSize (ArrowType arrowType, ArrowOrientation arrowOrientation, UInt32 dpi, Int32* width, Int32* height = nullptr);
#endif

	static float	DistanceBetweenPoints (const DG::Point& point1, const DG::Point& point2);
	static float	DistanceBetweenPoints (const DG::NativePoint& point1, const DG::NativePoint& point2);

	static UInt32	GetRawDPIForWindow (void* window = nullptr);
};

// --- Utility functions -----------------------------------------------------------------------------------------------

DG_DLL_EXPORT bool CCALL			IsVisibleOnScreen (const DG::NativePoint& point);
DG_DLL_EXPORT DG::NativeRect CCALL	VisibleBoundingRectOfScreens (void);
DG_DLL_EXPORT short CCALL			GetPixelDepthOnScreen (const DG::NativeRect& rect);
DG_DLL_EXPORT double CCALL			GetPrimaryScreenScaleFactor (void);

DG_DLL_EXPORT void CCALL			GetMonitorRects (GS::Array<DG::NativeRect>& monitorRects, bool onlyUsableFrame = false);
DG_DLL_EXPORT void CCALL			LogMonitorInformation (void);
DG_DLL_EXPORT void CCALL			LogPaletteLayoutInformation (void);

DG_DLL_EXPORT DG::Icon CCALL		GetArrowImage (Utils::ArrowType arrowType, Utils::ArrowOrientation orientation);
DG_DLL_EXPORT void CCALL			ReleaseNativeImage (void* image);

DG_DLL_EXPORT GS::UniString CCALL	GetCefCacheBasePath ();
DG_DLL_EXPORT GS::UniString CCALL	GetCefCachePath (const GS::UniString& cacheBasePath);
DG_DLL_EXPORT GS::UShort CCALL		GetCefDebugPort ();

#if defined (macintosh)
typedef enum ImageTypeHint {
	ImgType_Icon = 0,
	ImgType_Picture = 1,
	ImgType_Cursor = 2
} ImageTypeHint;

typedef double CGFloat;

DG_DLL_EXPORT void* CCALL	GetNativeMaskedImage (void* image, const Gfx::Color* transparentColor);
DG_DLL_EXPORT void* CCALL	GetNativeIconImage (short imageId, GSResModule resModule);
DG_DLL_EXPORT void* CCALL	GetNativeImage (short imageId, GSResModule resModule, ImageTypeHint hint=DG::ImgType_Picture);
DG_DLL_EXPORT void CCALL	GetNativeImageSize (void* image, Int32* pWidth, Int32* pHeight);
DG_DLL_EXPORT void CCALL	DrawNativeImageIntoRect (void* drawContext, const DG::Rect& rect, const void* image, bool isDisabled = false);
DG_DLL_EXPORT void CCALL	CompositeImages (void **dest, CGFloat w, CGFloat h, void *src1, CGFloat x1, CGFloat y1, CGFloat w1, CGFloat h1, void *src2, CGFloat x2, CGFloat y2, CGFloat w2, CGFloat h2);

DG_DLL_EXPORT NewDisplay::NativeImage	CreateNativeImageFromImageData (GSHandle imageData, double resolutionFactor = 1.0);

DG_DLL_EXPORT	void		DrawBestIconIntoRect (void* drawContext, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER,  short vAlignment = DG_IS_VCENTER);
void						DrawIconIntoRect (void* drawContext, const DG::Rect& rect, const DG::Icon& icon, bool isDisabled = false, short hAlignment = DG_IS_CENTER,  short vAlignment = DG_IS_VCENTER);
char						GetMacCharCode (short dgKeyCode);
short						GetMacFunctionKeyCode (short dgKeyCode);

unsigned short				GetVirtualKeyCode (short charCode);
unsigned short				GetSpecVirtualKeyCode (short dgKeyCode);
bool						CheckKey (unsigned short vkCode);

void						InitCef ();
void						QuitCef ();


#endif

} // end of namespace DG

#endif
