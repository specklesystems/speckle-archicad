#ifndef SYRICHTEXT_HPP
#define SYRICHTEXT_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Point2D.hpp"

class	Box2DData;
struct	TRANMAT;
class	WordAnchor;

namespace Geometry {
	class Transformation2D;
}

class VI_DLL_CLASS_EXPORT Sy_RichTextType {
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;		// length of the data record
	unsigned char	item_Typ;		// = SyRichText (11)
	DrawIndex		drwIndex;		// index in drawing order or 0
	short			sy_fragmentIdx;	// Fragment (layer) number: 1 - 16

	Coord			loc;
	double			width;
	double			height;
	double			angle;
	double			widthFactor;
	double			charSpaceFactor;
private:
	char			anchor;
public:
	bool			fixedHeight;
	bool			nonBreaking;
	bool			canScale;
	Int32			paramInd;
	Int32			ind1;
	Int32			ind2;

	Int32			numParagraphs;
	Int32			numTextStyles;
	Int32			numLines;
	Int32			numTabs;

	char			sy2dRenovationStatus; // Sy2dRenovationStatusTypes
private:
	char			filler_1;
	short			filler_2;
	Int32			filler_3;
public:

	struct Paragraph;
	struct TextStyle;
	struct Eol_Width;
	struct Tab;

	Sy_RichTextType ();

	WordAnchor	GetAnchor () const;
	void		SetAnchor (const WordAnchor& wordAnchor);

	void GetPointers (	Paragraph**		par,
						TextStyle**		stl,
						Eol_Width**		ln,
						Tab**			tab,
						GS::uchar_t**	strings);

	void GetPointers (	const Paragraph**		par,
						const TextStyle**		stl,
						const Eol_Width**		ln,
						const Tab**				tab,
						const GS::uchar_t**		strings) const;

	void GetBounds (Box2DData& box, double planScale) const;
	void Transform (const Geometry::Transformation2D& tran);
	void Transform (const TRANMAT& tran);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
};


struct VI_DLL_CLASS_EXPORT Sy_RichTextType::Paragraph {
	short			alignment;
private:
	[[maybe_unused]] short filler_1;
	[[maybe_unused]] Int32 filler_2;
public:
	double			firstLineIndent;
	double			leftIndent;
	double			rightIndent;
	double			lineSpacing;

	Int32			firstTextStyleInd;
	Int32			numTextStyles;
	Int32			firstLineInd;
	Int32			numLines;
	Int32			firstTabInd;
	Int32			numTabs;

	Paragraph () :
		alignment (0),
		filler_1 (0),
		filler_2 (0),
		firstLineIndent (0.0),
		leftIndent (0.0),
		rightIndent (0.0),
		lineSpacing (0.0),
		firstTextStyleInd (0),
		numTextStyles (0),
		firstLineInd (0),
		numLines (0),
		firstTabInd (0),
		numTabs (0)
	{
	}
};


struct VI_DLL_CLASS_EXPORT Sy_RichTextType::TextStyle {
	double			size;
	short			styleInd;		// contains fontname and face only
	short			penInd;
	Int32			stringOffset;
	
	TextStyle () :
		size (0.0),
		styleInd (0),
		penInd (0),
		stringOffset (0)
	{
	}
};


struct VI_DLL_CLASS_EXPORT Sy_RichTextType::Eol_Width {
	double			width;
	Int32			eolPosition;
private:
	[[maybe_unused]] Int32 filler_1;
public:
	
	Eol_Width () :
		width (0.0),
		eolPosition (0),
		filler_1 (0)
	{
	}
};


struct VI_DLL_CLASS_EXPORT Sy_RichTextType::Tab {
	double			position;
	Int32			type;
private:
	[[maybe_unused]] Int32 filler_1;
public:
	
	Tab () :
		position (0.0),
		type (0),
		filler_1 (0)
	{
	}
};


inline void Sy_RichTextType::GetPointers (Paragraph** par, TextStyle** stl, Eol_Width** ln, Tab** tab, GS::uchar_t** strings)
{
	*par		= (Paragraph *)		(this + 1);
	*stl		= (TextStyle *)		(*par + numParagraphs);
	*ln			= (Eol_Width *)		(*stl + numTextStyles);
	*tab		= (Tab *)			(*ln + numLines);
	*strings	= (GS::uchar_t *)	(*tab + numTabs);
}


inline void Sy_RichTextType::GetPointers (const Paragraph** par, const TextStyle** stl, const Eol_Width** ln, const Tab** tab, const GS::uchar_t** strings) const
{
	*par		= (const Paragraph *)		(this + 1);
	*stl		= (const TextStyle *)		(*par + numParagraphs);
	*ln			= (const Eol_Width *)		(*stl + numTextStyles);
	*tab		= (const Tab *)				(*ln + numLines);
	*strings	= (const GS::uchar_t *)		(*tab + numTabs);
}

#endif // SYRICHTEXT_HPP