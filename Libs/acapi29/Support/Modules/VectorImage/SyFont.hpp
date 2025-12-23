#ifndef SYFONT_HPP
#define SYFONT_HPP

#pragma once

#include "ISymbol.hpp"
class WordAnchor;

class VI_DLL_CLASS_EXPORT Sy_FontType {	// 72 Bytes; Font record
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;				// length of the data record = sizeof(Sy_FontType) + RoundUp8(fontNameLen)
	unsigned char	item_Typ;				// = SyFont (8)
	char			dummyC;
	short			familytype;				// font family type: GDLFONTFAMILYNAME, GDLPLOTTERFONT, GDLPLOTMAKERFONT
	Int32			styleind;
	unsigned char	face;					// (Style) Style of text
private:
	char			centre;					// Kind of text centre (1..9); if < 0 nonBreaking input mode
public:
	short			just;					// Justification of text
	double			slant;					// Slant of text letters in rad (pi/2 is plain text)
	double			size;					// Letter size in mm independent of scale
	double			spac;					// Spacing between text lines in mm
	Int32			fontNameOffs;			// data offset of the font name
	Int32			fontNameLen;			// data length of the font name
	
	Sy_FontType ();

	WordAnchor	GetAnchor () const;
	void		SetAnchor (const WordAnchor& wordAnchor);

	bool CheckAndRepair (void);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
};

#endif // SYFONT_HPP