#ifndef SYPOINTCLOUD_HPP
#define SYPOINTCLOUD_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"

class  Sy_2DHeadType;


class Sy_PointCloudType {
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;
	unsigned char	item_Typ;
	DrawIndex		drwIndex;
	short			sy_fragmentIdx;
	UIndex			iInObjectArray;
private:
	Int32			filler;
public:

	Sy_PointCloudType ();
		
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
};

#endif // SYPOINTCLOUD_HPP