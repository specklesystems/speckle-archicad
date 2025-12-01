#ifndef SYPIXMAP_HPP
#define SYPIXMAP_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Box2DData.h"

class Box2DData;
namespace Geometry {
class Transformation2D;
}

class VI_DLL_CLASS_EXPORT Sy_PixMapType {	// 160 Bytes; PixMap record
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;				// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;				// = SyPixMap (10)
	DrawIndex		drwIndex;				// index in drawing order or 0
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	bool			mirrored;				// TRUE if mirrored to local vertical axis
	char			anchorPoint;			// Value: 1 - 9
	short			colorDepth;
	short			pixelSizeX;
	short			pixelSizeY;
	UInt32			pixMapFormat;
private:
	Int32			filler_2;
public:
	Box2DData		destBox;				// Box in real coordinates
	Box2DData		origBox;				// Box in real coordinates
	char			pixName[128];
	double			rotAngle;				// Rotation around left bottom
	Int32			pixHdlLen;				// PixMapHandle data length
	Int32			pixHdlOff;				// Offset of the PixMapHandle from record start
											// = sizeof(Sy_PixMapType)
	bool			transparent;			// #10158 TranspPict
	char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
private:
	short			filler_3;
public:
	Int32			mimeTypeLen;			// data length of the mime-type
	Int32			mimeTypeOff;			// data offset of the mime-type
private:
	Int32			filler_6;
public:

	Sy_PixMapType ();

	void GetBounds (Box2DData& box) const;
	void Transform (const Geometry::Transformation2D& tran);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};


#endif // SYPIXMAP_HPP