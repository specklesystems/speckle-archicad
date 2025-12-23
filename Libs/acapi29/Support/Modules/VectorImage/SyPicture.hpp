#ifndef SYPICTURE_HPP
#define SYPICTURE_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Box2DData.h"

class VI_DLL_CLASS_EXPORT Sy_PictureType {		// 160 Bytes; Picture record
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;					// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;					// = SyPicture (9)
	DrawIndex		drwIndex;					// index in drawing order or 0
	short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
	bool			mirrored;					// TRUE if mirrored to local vertical axis
	char			anchorPoint;				// Value: 1 - 9
	short			colorDepth;
	short			pixelSizeX;
	short			pixelSizeY;
	short			storageFormat;
	unsigned short	pictPlatform;				// 'MM' or 'WW' (picHdl platfor PICT Or BMAP)
private:
	Int32			filler_2;
public:
	Box2DData		destBox;					// Box in real coordinates
	Box2DData		origBox;					// Box in real coordinates
	char			pictName[128];
	double			rotAngle;					// Rotation around left bottom
	Int32			picHdlLen;					// PicHandle data length
	Int32			picHdlOff;					// Offset of the PicHandle from record start
												// = sizeof(Sy_PictureType)
	Int32			figHdlLen;
	Int32			figHdlOff;
	bool			transparent;				// #10158 TranspPict
private:
	char			filler_3_1;
	short			filler_3;
	Int32			filler_4;
	Int32			filler_5;
	Int32			filler_6;
public:
	
	Sy_PictureType ();
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};


#endif // SYPICTURE_HPP