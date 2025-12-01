#ifndef SYTEXT_HPP
#define SYTEXT_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Point2D.hpp"

class Box2DData;

namespace GS { class MemoryIChannel32; }
namespace Geometry { class Transformation2D; }

class VI_DLL_CLASS_EXPORT Sy_TextType {	// 88 Bytes + content data; Text record
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;				// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;				// = SyText (5)
	DrawIndex		drwIndex;				// index in drawing order or 0
	short			sy_pen;					// color information 0 if deleted
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	char			nonBreaking;			// 0: wrap around at dest rect; 1: wrap around at Cr only
	unsigned char	paramInd;				// Symbol parameter index (0: value from not text param)
	Int32			styleind;
	Coord			loc;					// Real coordinates of text centre
	double			angle;					// Angle of text letters in rad
	double			width;					// Horizontal size of text box in mm
	double			height;					// Vertical size of text box in mm

	double			size;					// Transformed letter size in mm
	double			spac;					// Transformed spacing between text lines in mm

	short			ind1;					// Indexes of an array type GDL parameter
	short			ind2;
	Int32			lines;					// Number of text lines
	Int32			conLen;					// Text content data length
	Int32			conOff;					// Offset of the Text content from record start
											// = sizeof(Sy_TextType)
	Int32			lStLen;					// Text line starts data length
	Int32			lStOff;					// Offset of the linestarts from record start
											// = sizeof(Sy_TextType)+RoundUp8(conLen)
	char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
private:
	char			filler_1;
	short			filler_2;
	Int32			filler_3;
public:

	Sy_TextType ();

	GSErrCode GetBounds (Box2DData& box, double planScale) const;
	void Transform (const Geometry::Transformation2D& tran, double dScale);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen, GS::MemoryIChannel32& ic, const UInt32 offset);
};



#endif // SYTEXT_HPP