// *****************************************************************************
// File:			UCRollDown.hpp
//
// Description:		Rolldown control classes (UC260)
//
// Project:			GRAPHISOFT User Control Library (UCLib)
//
// Namespace:		UC
//
// Contact person:	VM
//
// SG compatible
// *****************************************************************************

#ifndef UCROLLDOWN_HPP
#define UCROLLDOWN_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGModule.hpp"
#include "UC.h"


namespace UC {

// --- Class declarations ------------------------------------------------------

class UC_DLL_EXPORT RollDown: public DG::UserControl
{
public:
	enum SizeFlag {
		Large		= CS_ROLLDOWN_LARGE,
		Small		= CS_ROLLDOWN_SMALL
	};

	enum ActivityFlag {
		Active		= CS_ROLLDOWN_ACTIVE,
		Inactive	= CS_ROLLDOWN_INACTIVE
	};

	enum TextTruncation {
		DrawEllipses	= CS_ROLLDOWN_DRAWELLIPSIS,
		Truncated		= CS_ROLLDOWN_TRUNCATED
	};

	RollDown (const DG::Panel& panel, short item);
	RollDown (const DG::Panel& panel, const DG::Rect& rect);
	RollDown (const DG::Panel& panel, const DG::Rect& rect, const DG::Icon& icon, const GS::UniString& text,
			  SizeFlag sizeFlag = Large, ActivityFlag activityFlag = Active);
   ~RollDown ();

	void			SetSizeFlag (SizeFlag sizeFlag);
	SizeFlag		GetSizeFlag (void) const;

	void			SetActivityFlag (ActivityFlag activityFlag);
	ActivityFlag	GetActivityFlag (void) const;

	void			SetFontSize (DG::Font::Size size);
	DG::Font::Size	GetFontSize (void) const;

	void			SetFontStyle (DG::Font::Style style);
	DG::Font::Style	GetFontStyle (void) const;

	void			SetIconFieldWidth (short iconfieldWidth);
	short			GetIconFieldWidth (void) const;

	void			SetIcon (const DG::Icon& icon);
	DG::Icon		GetIcon (void) const;

	short			GetExpandedHeight (void) const;
	short			GetCollapsedHeight (void) const;

	void			SetText (const GS::UniString& text);
	GS::UniString	GetText (void) const;

	void			SetTextTruncation (TextTruncation truncation);
	TextTruncation	GetTextTruncation (void) const;

	void			Expand (void);
	void			Collapse (void);
	bool			IsExpanded (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace UC

#endif
