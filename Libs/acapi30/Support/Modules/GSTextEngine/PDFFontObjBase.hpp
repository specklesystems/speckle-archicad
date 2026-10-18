
// *****************************************************************************
//
//                                PDFFontObjBase
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	BL
//
// SG compatible
//
// *****************************************************************************


#if !defined PDFFONTOBJBASE_HPP
#define PDFFONTOBJBASE_HPP

// --------------------------------- Includes ----------------------------------

#if defined (macintosh)
#include "MacUtils/CGUtil.hpp"
#endif

#include "TEBase.hpp"

#include "Location.hpp"


// ----------------------------- Predeclarations -------------------------------

namespace TE {
	class IFont;
}

// ============================== Class PDFFontObjBase =========================

namespace TE {

class	TE_DLL_EXPORT PDFFontObjBase {
private:
#if defined (macintosh)
	CFStringRef				string;
	CTFontRef				ctfont;
#endif
	IO::Location			fontLocation;
	const TE::IFont*		font;
	double					posX;
	double					posY;
	double					widthFactor;
	double					charSpaceFactor;
	double					textScale;
	double					rotAngle;
	bool					reqUnderline;
	bool					reqStrikeOut;
	double					baselineOffset;
	double					strikeOutPosX;
	double					strikeOutPosY;
	double					strikeOutWeight;
	double					strikeOutWidth;
	double					underlinePosX;
	double					underlinePosY;
	double					underlineWeight;
	double					underlineWidth;

public:
	PDFFontObjBase (void) : font (nullptr), posX (0.0), posY (0.0), widthFactor (1.0), charSpaceFactor (1.0), textScale (1.0), rotAngle (0.0),
							reqUnderline (false), reqStrikeOut (false), baselineOffset (0.0), strikeOutPosX (0.0), strikeOutPosY (0.0), strikeOutWeight (1.0), strikeOutWidth (0.0), underlinePosX (0.0), underlinePosY (0.0), underlineWeight (1.0), underlineWidth (0.0)
	{
#if defined (macintosh)
		string = nullptr;
		ctfont = nullptr;
#endif
	}
	PDFFontObjBase (const TE::PDFFontObjBase& source) {
#if defined (macintosh)
		SetString (source.GetString ());
		SetCTFont (source.GetCTFont ());
#endif
		SetFontLocation (source.GetFontLocation ());
		SetFont (source.GetFont ());
		SetPosX (source.GetPosX ());
		SetPosY (source.GetPosY ());
		SetWidthFactor (source.GetWidthFactor ());
		SetCharSpaceFactor (source.GetCharSpaceFactor ());
		SetTextScale (source.GetTextScale ());
		SetRotAngle (source.GetRotAngle ());
		SetBaselineOffset (source.GetBaselineOffset ());
		SetStrikeOut (source.GetStrikeOut ());
		SetStrikeOutPosX (source.GetStrikeOutPosX ());
		SetStrikeOutPosY (source.GetStrikeOutPosY ());
		SetStrikeOutWeight (source.GetStrikeOutWeight ());
		SetStrikeOutWidth (source.GetStrikeOutWidth ());
		SetUnderline (source.GetUnderline ());
		SetUnderlinePosX (source.GetUnderlinePosX ());
		SetUnderlinePosY (source.GetUnderlinePosY ());
		SetUnderlineWeight (source.GetUnderlineWeight ());
		SetUnderlineWidth (source.GetUnderlineWidth ());
	}
	~PDFFontObjBase (void) {}

#if defined (macintosh)
	void				SetString (CFStringRef inString)					{ string = inString; }
	void				SetCTFont (CTFontRef inCTfont)						{ ctfont = inCTfont; }
#endif
	void				SetFontLocation (IO::Location inFontLocation)		{ fontLocation = inFontLocation; }
	void				SetFont (const TE::IFont* inFont)					{ font = inFont; }
	void				SetPosX (double inPosX)								{ posX = inPosX; }
	void				SetPosY (double inPosY)								{ posY = inPosY; }
	void				SetWidthFactor (double inWidthFactor)				{ widthFactor = inWidthFactor; }
	void				SetCharSpaceFactor (double inCharSpaceFactor)		{ charSpaceFactor = inCharSpaceFactor; }
	void				SetTextScale (double inTextScale)					{ textScale = inTextScale; }
	void				SetRotAngle (double inRotAngle)						{ rotAngle = inRotAngle; }
	void				SetBaselineOffset (double inBaselineOffset)			{ baselineOffset = inBaselineOffset; }
	void				SetStrikeOut (bool inReqStrikeOut)					{ reqStrikeOut = inReqStrikeOut; }
	void				SetStrikeOutPosX (double inStrikeOutPosX)			{ strikeOutPosX = inStrikeOutPosX; }
	void				SetStrikeOutPosY (double inStrikeOutPosY)			{ strikeOutPosY = inStrikeOutPosY; }
	void				SetStrikeOutWeight (double inStrikeOutWeight)		{ strikeOutWeight = inStrikeOutWeight; }
	void				SetStrikeOutWidth (double inStrikeOutWidth)			{ strikeOutWidth = inStrikeOutWidth; }
	void				SetUnderline (bool inReqUnderline)					{ reqUnderline = inReqUnderline; }
	void				SetUnderlinePosX (double inUnderlinePosX)			{ underlinePosX = inUnderlinePosX; }
	void				SetUnderlinePosY (double inUnderlinePosY)			{ underlinePosY = inUnderlinePosY; }
	void				SetUnderlineWeight (double inUnderlineWeight)		{ underlineWeight = inUnderlineWeight; }
	void				SetUnderlineWidth (double inUnderlineWidth)			{ underlineWidth = inUnderlineWidth; }

#if defined (macintosh)
	CFStringRef			GetString () const					{ return string; }
	CTFontRef			GetCTFont () const					{ return ctfont; }
#endif
	IO::Location		GetFontLocation () const			{ return fontLocation; }
	const TE::IFont*	GetFont () const					{ return font; }
	double				GetPosX () const					{ return posX; }
	double				GetPosY () const					{ return posY; }
	double				GetWidthFactor () const				{ return widthFactor; }
	double				GetCharSpaceFactor () const			{ return charSpaceFactor; }
	double				GetTextScale () const				{ return textScale; }
	double				GetRotAngle () const				{ return rotAngle; }
	double				GetBaselineOffset () const			{ return baselineOffset; }
	bool				GetStrikeOut () const				{ return reqStrikeOut; }
	double				GetStrikeOutPosX () const			{ return strikeOutPosX; }
	double				GetStrikeOutPosY () const			{ return strikeOutPosY; }
	double				GetStrikeOutWeight () const			{ return strikeOutWeight; }
	double				GetStrikeOutWidth () const			{ return strikeOutWidth; }
	bool				GetUnderline () const				{ return reqUnderline; }
	double				GetUnderlinePosX () const			{ return underlinePosX; }
	double				GetUnderlinePosY () const			{ return underlinePosY; }
	double				GetUnderlineWeight () const			{ return underlineWeight; }
	double				GetUnderlineWidth () const			{ return underlineWidth; }
};


}	// namespace TE
// ______________________________ Class PDFFontObjBase ______________________________


#endif
