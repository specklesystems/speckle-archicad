#ifndef SYHEAD_HPP
#define SYHEAD_HPP

#pragma once

#include "ISymbol.hpp"
#include "Box2DData.h"


#define HeadBits_UseDrwQ				0x01	// Use continous drawing queue
#define HeadBits_SortDrwQ				0x02	// sort behind drawing
#define HeadBits_HangOutOfBox			0x10	// There are some hotspots which are hangs out of the model box
#define HeadBits_GeneratedWithOverride	0x20


class VI_DLL_CLASS_EXPORT Sy_2DHeadType {

	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	void InitVersions ();

public:
	Int32			item_Len;				// length of the data record = sizeof(Sy_2DHeadType)
	unsigned char	item_Typ;				// = SyHead (1)
	unsigned char	headVers;				// = Curr_Sy2DVersion
	unsigned short	platform;				// platform identifier sign: 'MM' or 'WW'
	Box2DData		box;					// Boundaries of the Symbol's image
	unsigned char	isBoundBoxValid;
private:
	unsigned char	reserved1;				// filler, MUST BE 0
	short			reserved2;				// filler, MUST BE 0
public:
	Int32			defScale;				// default scale (not used yet)
	Int32			headBits;				// HeadBits_UseDrwQ, HeadBits_SortDrwQ, HeadBits_HangOutOfBox
	
	ULong			endOff;					// offset of the end record from section start
	ULong			nHots;					// Number of hotspots			in the Symbol
	ULong			nLine;					// Number of lines				in the Symbol
	ULong			nArc;					// Number of arcs				in the Symbol
	ULong			nText;					// Number of Texts				in the Symbol
	ULong			nHatc;					// Number of Hatches			in the Symbol
	ULong			nSpline;				// Number of Splines			in the Symbol
	ULong			nFonts;					// Number of Font data records	in the Symbol
	ULong			nPicture;				// Number of Pictures			in the Symbol
	ULong			nPixMap;				// Number of PixMaps			in the Symbol
	ULong			nRichText;				// Number of RichTexts			in the Symbol
	ULong			nPolyLine;				// Number of polyLines			in the Symbol
	ULong			nObject;				// Number of objects			in the Symbol
	
	short			versOfHots;				// Version of hotspots			in the Symbol
	short			versOfLine;				// Version of lines				in the Symbol
	short			versOfArc;				// Version of arcs				in the Symbol
	short			versOfText;				// Version of Texts				in the Symbol
	short			versOfHatc;				// Version of Hatches			in the Symbol
	short			versOfSpline;			// Version of Splines			in the Symbol
	short			versOfFonts;			// Version of Font data records	in the Symbol
	short			versOfPicture;			// Version of Pictures			in the Symbol
	short			versOfPixMap;			// Version of PixMaps			in the Symbol
	short			versOfRichText;			// Version of RichTexts			in the Symbol
	short			versOfPolyLine;			// Version of polyLines			in the Symbol
	short			versOfObject;			// Version of objects			in the Symbol

	Sy_2DHeadType ();
	
	Sy_2DHeadType (	Int32			item_Len,
					unsigned char	item_Typ,
					unsigned char	headVers,
					unsigned short	platform,
					double			boxxMin,
					double			boxyMin,
					double			boxxMax,
					double			boxyMax,
					unsigned char	isBoundBoxValid,
					Int32			defScale,
					Int32			headBits,
					ULong			endOff,
					ULong			nHots,
					ULong			nLine,
					ULong			nArc,
					ULong			nText,
					ULong			nHatc,
					ULong			nSpline,
					ULong			nFonts,
					ULong			nPicture,
					ULong			nPixMap,
					ULong			nRichText,
					ULong			nPolyLine,
					ULong			nObject);

	void SetToPreviousSyVersion ();

	short GetVersion (SyEnum syType) const;
	GSErrCode ReadBin (GS::IChannel& oc, short version);

	GSErrCode Write (GS::OChannel& oc, short version) const;
	GSErrCode Read (GS::IChannel& oc, short version);

	static Int32 GetConvertedSize (Int32 ac19ItemLen);

	static short GetActVersion () { return Curr_Sy2DVersion; }
	static short GetPreviousVersion () { return 36; }
};


#endif // SYHEAD_HPP