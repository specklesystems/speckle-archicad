#ifndef EDGE_OVERRIDEDATA_HPP__
#define EDGE_OVERRIDEDATA_HPP__

#pragma once

#include "VectorImageExport.h"

typedef GSIndex GSAttributeIndex;

namespace PVI { // ProfileVectorImage


class VI_DLL_CLASS_EXPORT EdgeOverrideData : public GS::Object 
{
	DECLARE_CLASS_INFO

public:
	EdgeOverrideData ();
	EdgeOverrideData (GSAttributeIndex inInnerLineType, GSAttributeIndex inOuterLineType, short inInnerPen, short inOuterPen, bool inOverrideSectionLines);

	bool operator== (const EdgeOverrideData& other) const;
	bool operator!= (const EdgeOverrideData& other) const;

	GSAttributeIndex	GetInnerLineType () const;
	GSAttributeIndex	GetOuterLineType () const;
	short				GetInnerPen () const;
	short				GetOuterPen () const;
	bool				GetOverrideSectionLines () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const;

private:
	GSAttributeIndex	innerLineType;
	GSAttributeIndex	outerLineType;
	short				innerPen;
	short				outerPen;
	bool				overrideSectionLines;

	GSErrCode	ReadVersion1  (GS::IChannel& ic);
	GSErrCode	ReadVersion2  (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;
	GSErrCode	WriteVersion2 (GS::OChannel& oc) const;
};

}

#endif
