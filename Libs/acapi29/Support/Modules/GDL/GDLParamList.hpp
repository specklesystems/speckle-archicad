// *********************************************************************************************************************
// Description:		GDLParamList.hpp
//
// Module:			GDL
// Namespace:
// Contact person:	HK, SD
//
// *********************************************************************************************************************

#ifndef GDLADDPAR_HPP
#define GDLADDPAR_HPP

#include "GDLPropertyList.hpp"
#include "GDLExport.h"

namespace GDL
{

struct GDL_DLL_EXPORT ParamListUserData
{
	short			dataType;
	unsigned char	flags;
	char			filler;

	ParamListUserData ();

	void Write (GS::OChannel&, const GS::ClassVersion&) const;
	void Read (GS::IChannel&, const GS::ClassVersion&);

	void CheckIntegrity () const;

	static const GS::ClassInfo* GetClassInfo ();
};

class GDL_DLL_EXPORT ParamList : public PropertyList<ParamListUserData>
{
public:
	void ModifyEntryDataType (ULong index, short dataType);
	short GetEntryDataType (ULong index) const;

	void ModifyEntryFlags (ULong index, unsigned char newFlags);
	void ClearEntryFlagBits (ULong index, unsigned char flagBits);
	void SetEntryFlagBits (ULong index, unsigned char flagBits);
	unsigned char GetEntryFlags (ULong index) const;

	double GetParamA () const;
	double GetParamB () const;
	void ModifyParamA (double value);
	void ModifyParamB (double value);

	GDL::Parameters	WriteToParameters () const;
	void ReadFromParameters (const GDL::ParameterGetter& addPar);

	bool Equals (const ParamList& op) const;
	Int32 CheckSum (double* sumVars) const;

	static StorageType GetStorageType (short dataType);
};

}

void inline GDL::ParamListUserData::Write (GS::OChannel& oc, const GS::ClassVersion& /* version */) const
{
	if (oc.Write (dataType) != NoError)
		throw GS::GSException ();
	if (oc.Write (flags) != NoError)
		throw GS::GSException ();
}

void GS_FORCE_INLINE GDL::ParamListUserData::CheckIntegrity () const
{
}

void GS_FORCE_INLINE GDL::ParamList::ModifyEntryDataType (ULong index, short dataType)
{
	GetUserData (index).dataType = dataType;
}

short GS_FORCE_INLINE GDL::ParamList::GetEntryDataType (ULong index) const
{
	return GetUserData (index).dataType;
}

void GS_FORCE_INLINE GDL::ParamList::ModifyEntryFlags (ULong index, unsigned char newFlags)
{
	GetUserData (index).flags = newFlags;
}

void GS_FORCE_INLINE GDL::ParamList::ClearEntryFlagBits (ULong index, unsigned char flagBits)
{
	GetUserData (index).flags &= ~flagBits;
}

void GS_FORCE_INLINE GDL::ParamList::SetEntryFlagBits (ULong index, unsigned char flagBits)
{
	GetUserData (index).flags |= flagBits;
}

unsigned char GS_FORCE_INLINE GDL::ParamList::GetEntryFlags (ULong index) const
{
	return GetUserData (index).flags;
}

double GS_FORCE_INLINE GDL::ParamList::GetParamA () const
{
	return (*this)["A"];
}

double GS_FORCE_INLINE GDL::ParamList::GetParamB () const
{
	return (*this)["B"];
}

void GS_FORCE_INLINE GDL::ParamList::ModifyParamA (double value)
{
	(*this)["A"] = value;
}

void GS_FORCE_INLINE GDL::ParamList::ModifyParamB (double value)
{
	(*this)["B"] = value;
}


GDL_DLL_EXPORT
bool GDL_CALL GDLCompareParamLists (const GDL::ParamList& defParamList, GDL::ParamList& oldParamList, bool* modifOldPar);

GDL_DLL_EXPORT
GSErr GDL_CALL GDLMergeParamLists (const GDL::ParamList& defParamList, const GDL::ParamList& oldParamList, GDL::ParamList* newParamList);

GDL_DLL_EXPORT
GSErr GDL_CALL GDLAppendDiff (const GDL::ParamList& oldPar, GDL::ParamList* newPar);


#endif
