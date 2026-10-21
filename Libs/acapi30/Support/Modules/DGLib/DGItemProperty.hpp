// *********************************************************************************************************************
// File:			DGItemProperty.hpp
//
// Description:		ItemProperty classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
// *********************************************************************************************************************

#ifndef DGITEMPROPERTY_HPP
#define DGITEMPROPERTY_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "UniString.hpp"

#include "Color.hpp"

#include "DGItem.hpp"


namespace DG {

// --- Definitions -----------------------------------------------------------------------------------------------------

namespace Font {
	enum Size {
		Large			= DG_IS_LARGE,
		Small			= DG_IS_SMALL,
		ExtraSmall		= DG_IS_EXTRASMALL,
		DefaultSize		= DG_IS_DEFAULT
	};

	enum Style {
		Plain			= DG_IS_PLAIN,
		Bold			= DG_IS_BOLD,
		Italic			= DG_IS_ITALIC,
		Underline		= DG_IS_UNDERLINE,
		Shadow			= DG_IS_SHADOW,
		Outline			= DG_IS_OUTLINE,
		DefaultStyle	= DG_IS_DEFAULT
	};
}


// --- Class declarations ----------------------------------------------------------------------------------------------

// --- FocusableProperty -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT FocusableProperty: virtual public ItemBase
{
protected:
	FocusableProperty ();

public:
	~FocusableProperty ();

	virtual void	SetFocus (void);
	bool	IsFocused (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};


// --- ItemFontProperty ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemFontProperty: virtual public ItemBase
{
protected:
	ItemFontProperty ();

public:
	~ItemFontProperty ();

	void		 SetFontSize (Font::Size size);
	Font::Size	 GetFontSize (void) const;

	void		 SetFontStyle (Font::Style style);
	Font::Style	 GetFontStyle (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};


// --- ItemIconProperty ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemIconProperty: virtual public ItemBase
{
protected:
	ItemIconProperty ();

public:
	~ItemIconProperty ();

	void		SetIcon (const DG::Icon& icon);
	DG::Icon	GetIcon (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};


// --- ItemTextProperty ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemTextProperty: virtual public ItemBase
{
protected:
	ItemTextProperty ();

public:
	~ItemTextProperty ();

	void		SetText (const GS::UniString& text);
	void		CatText (const GS::UniString& text);

	GS::UniString	GetText (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};


// --- ItemColorProperty -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemColorProperty: virtual public ItemBase
{
protected:
	ItemColorProperty ();

public:
	~ItemColorProperty ();

	void			SetTextColor (const Gfx::Color& textColor);
	Gfx::Color		GetTextColor (void) const;

	void			SetBackgroundColor (const Gfx::Color& bkgColor);
	Gfx::Color		GetBackgroundColor (void) const;

	void			ResetDefaultTextColor (void);
	void			ResetDefaultBackgroundColor (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};


// --- ItemVariousProperty ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemVariousProperty: virtual public ItemBase
{
protected:
	ItemVariousProperty ();

public:
	~ItemVariousProperty ();

	void			SetVariousState (bool isVarious);
	bool			GetVariousState (void) const;
	void			SetVariousText (const GS::UniString& text);
	GS::UniString	GetVariousText (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};


// --- ItemVariousProperty ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ItemTextLengthLimitProperty: virtual public ItemBase
{
protected:
	ItemTextLengthLimitProperty ();

public:
	~ItemTextLengthLimitProperty ();

	void	SetMaxTextLength (UInt32 maxLength);
	UInt32	GetMaxTextLength (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const;
};

} // end of namespace DG

#endif
