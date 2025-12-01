#ifndef EDGE_OVERRIDEDATA_HPP__
#define EDGE_OVERRIDEDATA_HPP__

#pragma once

#include "VectorImageExport.h"

// from CADInfrastructureBase
#include "ADBAttributeIndex.hpp"

namespace PVI { // ProfileVectorImage


class VI_DLL_CLASS_EXPORT EdgeOverrideData : public GS::Object 
{
	DECLARE_CLASS_INFO

public:
	EdgeOverrideData ();
	EdgeOverrideData (const ADB::AttributeIndex& inInnerLineType, const ADB::AttributeIndex& inOuterLineType, short inInnerPen, short inOuterPen, bool inOverrideSectionLines);

	bool operator== (const EdgeOverrideData& other) const;
	bool operator!= (const EdgeOverrideData& other) const;

	const ADB::AttributeIndex& GetInnerLineType () const;
	const ADB::AttributeIndex& GetOuterLineType () const;
	short				GetInnerPen () const;
	short				GetOuterPen () const;
	bool				GetOverrideSectionLines () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const;

private:
	ADB::AttributeIndex	innerLineType;
	ADB::AttributeIndex	outerLineType;
	short				innerPen;
	short				outerPen;
	bool				overrideSectionLines;

	GSErrCode	ReadVersion1  (GS::IChannel& ic);
	GSErrCode	ReadVersion2  (GS::IChannel& ic);
	GSErrCode	WriteVersion2 (GS::OChannel& oc) const;
};

}

#endif
