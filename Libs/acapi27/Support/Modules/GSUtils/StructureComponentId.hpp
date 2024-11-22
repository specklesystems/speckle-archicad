#ifndef STRUCTURECOMPONENTID_HPP
#define STRUCTURECOMPONENTID_HPP
#pragma once

#include "GSUtilsExport.h"
#include "ClassInfo.hpp"
#include "IOFrame.hpp"
#include "Channel.hpp"
#include "HashCommon.hpp"
#include "BaseAlgorithms.hpp"


namespace GS {
	class ObjectState;
}

class GSUTILS_DLL_EXPORT_CPP StructureComponentId
{
	DECLARE_ROOT_CLASS_INFO
private:
	Int32 value;

	StructureComponentId (Int32 value);
public:
	StructureComponentId ();
	virtual ~StructureComponentId();

	static const StructureComponentId Missing;
	static const StructureComponentId Basic;
	static const StructureComponentId ColumnCore;
	static const StructureComponentId ColumnVeneer;
	static const StructureComponentId ColumnWrapping;
	static const StructureComponentId ValidDummy;

	static StructureComponentId FromSkinIndex (short skinIndex);
	short GetSkinIndex () const;

	template<typename PrevIdsType>
	static StructureComponentId CreateNextUnique (const PrevIdsType& prevIds)
	{
		Int32 maxValue = -1;
		for (const StructureComponentId& prevId : prevIds) {
			maxValue = GS::Max (maxValue, prevId.value);
		}
		return StructureComponentId (maxValue + 1);
	}

	static StructureComponentId FromLegacyId (const Int32 legacyId);
	Int32 ToLegacyId () const;

	GS::UniString	ValueStringForDump () const;

	GSErrCode	Write (GS::OChannel& oc) const;
	GSErrCode	Read (GS::IChannel& ic);

	GS::ErrorStatus	Store (GS::ObjectState& os) const;
	GS::ErrorStatus	Restore (const GS::ObjectState& os);

	GSErrCode	WriteXML (GS::XMLOChannel& channel) const;
	GSErrCode	ReadXML (GS::XMLIChannel& channel);


	bool operator == (const StructureComponentId& other) const;
	bool operator != (const StructureComponentId& other) const { return !operator==(other); }	
	bool operator < (const StructureComponentId& other) const;
	bool operator > (const StructureComponentId& other) const;

	ULong	GenerateHashValue () const;

private:
	GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

};

GSUTILS_DLL_EXPORT_CPP
GSErrCode Read (GS::IChannel& ic, StructureComponentId& structureComponentId);
GSUTILS_DLL_EXPORT_CPP
GSErrCode Write (GS::OChannel& oc, const StructureComponentId& structureComponentId);

#endif