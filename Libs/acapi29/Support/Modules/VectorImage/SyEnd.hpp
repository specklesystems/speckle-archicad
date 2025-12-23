#ifndef SYEND_HPP
#define SYEND_HPP

#pragma once

#include "ISymbol.hpp"

class Sy_2DHeadType;

class VI_DLL_CLASS_EXPORT Sy_EndType {
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);
	
	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;				// length of the data record = sizeof(Sy_EndType)
	unsigned char	item_Typ;				// = SyEnd (0)
	char			dummyC;
	short			dummyS;
	
	Sy_EndType ();
	Sy_EndType (Int32 item_Len, unsigned char item_Typ);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);
	
	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
};


#endif // SYEND_HPP