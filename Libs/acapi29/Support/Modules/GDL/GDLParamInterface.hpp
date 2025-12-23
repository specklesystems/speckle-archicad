// *********************************************************************************************************************
// Module:			GDL
// Namespace:		GDL
// Contact person:	KV
// *********************************************************************************************************************

#ifndef GDLPARAMINTERFACE_HPP
#define GDLPARAMINTERFACE_HPP

#include "CopyOnWrite.hpp"
#include "GDLExport.h"
#include "GSFriend.hpp"
#include "Owner.hpp"
#include "UniString.hpp"
#include "GDLDictionaryValueTypes.hpp"
#include "ADBAttributeIndex.hpp"


namespace GDL
{

class Dictionary;
class Parameters;
class ParametersConversion;
class DictionaryPath;

class GDL_DLL_EXPORT ParameterGetter : public GS::Object
{
public:
	virtual ~ParameterGetter ();

	virtual bool						IsNull () const = 0;
	virtual Parameters					CreateParameters () const = 0;
	virtual Parameters					CreatePartialCopy (Int32 firstInd, Int32 lastInd) const = 0;
	virtual GSErr						CopyVarsInto (Parameters& rhs, Int32 firstInd, Int32 lastInd, Int32 destInd) const = 0;
	virtual GSErr						InsertVarInto (Parameters& rhs, Int32 sourceInd, Int32 destInd) const = 0;

	virtual Int32						GetVarNumber () const = 0;
	virtual Int32						GetIndexOfName (const char* name) const = 0;
	virtual Int32						GetIndexOfName (const char* name, Int32 varIndex, bool forwardFromVarIndex) const = 0;

	virtual GSErr						GetVarName (Int32 index, char* name, Int32 buffSize) const = 0;
	virtual const char*					GetVarNameRef (Int32 index) const = 0;
	virtual short						GetVarType (Int32 index, bool* isArray = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr, GSErr* err = nullptr) const = 0;
	virtual unsigned char				GetVarFlags (Int32 index, GSErr* err = nullptr) const = 0;
	virtual bool						IsVarFix (Int32 index) const = 0;

	virtual bool						GetBoolVar (Int32 index, GSErr* err = nullptr) const = 0;
	virtual Int32						GetIntVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual ADB::AttributeIndex			GetAttrVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual double						GetNumVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual GSErr						GetUStrVar (Int32 index, GS::UniString& retVal) const = 0;
	virtual double						GetParamA (GSErr* err = nullptr) const = 0;
	virtual double						GetParamB (GSErr* err = nullptr) const = 0;

	virtual bool						GetBoolArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr) const = 0;
	virtual Int32						GetIntArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual ADB::AttributeIndex			GetAttrArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual double						GetNumArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual GSErr						GetUStrArrayVal (Int32 index, Int32 ind1, Int32 ind2, GS::UniString& retVal) const = 0;
	virtual const GS::UniChar::Layout*	GetUStrArrayValRef (Int32 index, Int32 ind1, Int32 ind2) const = 0;
	virtual GSErr						GetArrayUVal (Int32 index, Int32 ind1, Int32 ind2, double* numVal, GS::UniString& strVal, GS::UniString* numValDescription = nullptr) const = 0;

	virtual GSPtr						GetUArrayVar (Int32 index, Int32* len = nullptr, short* type = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr) const = 0;
	virtual GSPtr						GetUArrayDescription (Int32 index, Int32* len = nullptr, short* type = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr) const = 0;

	virtual const GS::UniChar::Layout*	GetUStrVarRef (Int32 index) const = 0;
	virtual const void*					GetUArrayRef (Int32 index, MemSize* len = nullptr) const = 0;

	virtual const GDL::Dictionary&		GetDictionaryVar (Int32 index, GSErr* err = nullptr) const = 0;

protected:
	ParameterGetter () = default;
	ParameterGetter (const ParameterGetter& source) = default;
	ParameterGetter (ParameterGetter&& source) = default;
	ParameterGetter& operator= (const ParameterGetter& source) = default;
	ParameterGetter& operator= (ParameterGetter&& source) = default;
};

class GDL_DLL_EXPORT ParameterAccessor : public ParameterGetter
{
public:
	virtual ~ParameterAccessor ();

	virtual GSErr						ModifyVarName (Int32 index, const char* name) = 0;
	virtual GSErr						ModifyVarType (Int32 index, short newType, bool isArray, Int32 dim1, Int32 dim2, bool keepPreviousArrayValues = false) = 0;
	virtual GSErr						ModifyVarType_Simple (Int32 index, short newType) = 0;
	virtual GSErr						ModifyVarFlags (Int32 index, unsigned char flags) = 0;
	virtual GSErr						SetVarFix (Int32 index, bool isFix) = 0;
	virtual GSErr						SetVarFlagBits (Int32 index, unsigned char bits) = 0;
	virtual GSErr						ClearVarFlagBits (Int32 index, unsigned char bits) = 0;

	virtual GSErr						ModifyBoolVar (Int32 index, bool boolVal) = 0;
	virtual GSErr						ModifyIntVar (Int32 index, Int32 intVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyAttrVar (Int32 index, const ADB::AttributeIndex& attrVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyNumVar (Int32 index, double numVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyUStrVar (Int32 index, const GS::UniString& strVal) = 0;
	virtual GSErr						ModifyParamA (double val) = 0;
	virtual GSErr						ModifyParamB (double val) = 0;

	virtual GSErr						ModifyBoolArrayVal (Int32 index, Int32 ind1, Int32 ind2, bool boolVal) = 0;
	virtual GSErr						ModifyIntArrayVal (Int32 index, Int32 ind1, Int32 ind2, Int32 intVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyAttrArrayVal (Int32 index, Int32 ind1, Int32 ind2, const ADB::AttributeIndex& intVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyNumArrayVal (Int32 index, Int32 ind1, Int32 ind2, double numVal, const GS::UniString* numValDescription = nullptr) = 0;
	virtual GSErr						ModifyUStrArrayVal (Int32 index, Int32 ind1, Int32 ind2, const GS::UniString& strVal) = 0;

	virtual GSErr						ModifyIntArray (Int32 index, const Int32* intVals, const GS::UniChar::Layout* arrayDescription = nullptr) = 0;
	virtual GSErr						ModifyIntArray (Int32 index, const GS::Array<Int32>& intVals) = 0;
	virtual GSErr						ModifyAttrArray (Int32 index, const GS::Array<ADB::AttributeIndex>& intVals) = 0;
	virtual GSErr						ModifyNumArray (Int32 index, const double* numVals, const GS::UniChar::Layout* arrayDescription = nullptr) = 0;
	virtual GSErr						ModifyUStrArray (Int32 index, const GS::UniChar::Layout* strVals) = 0;

	virtual GSErr						ModifyArrayDimensions (const Int32 index, Int32 newDim1, Int32 newDim2) = 0;

	virtual GSErr						ModifyDictionaryVar (Int32 index, const GDL::Dictionary& dictionary) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const Int32 intVal) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<Int32>& intArray) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const double numVal) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<double>& numArray) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::UniString& stringVal) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<GS::UniString>& stringArray) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GDL::Dictionary& dictVal) = 0;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<GDL::Dictionary>& dictArray) = 0;
	virtual GSErr						RemoveDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path) = 0;

	virtual GSErr						AddVar (const char* name, short type, bool isArray, Int32 dim1, Int32 dim2) = 0;
	virtual GSErr						InsertNewVar (Int32 destInd, const char* name, short type, bool isArray, Int32 dim1, Int32 dim2) = 0;
	virtual GSErr						ReplaceVar (Int32 oldIndex, Int32 newIndex) = 0;
	virtual GSErr						DropVars (Int32 firstInd, Int32 lastInd) = 0;

protected:
	ParameterAccessor () = default;
	ParameterAccessor (const ParameterAccessor& source) = default;
	ParameterAccessor (ParameterAccessor&& source) = default;
	ParameterAccessor& operator= (const ParameterAccessor& source) = default;
	ParameterAccessor& operator= (ParameterAccessor&& source) = default;
};


class GDL_DLL_EXPORT Parameters : public ParameterAccessor
{
	DECLARE_CLASS_INFO;

public:
	enum class InitMode { InitNamesFromAToZ };

	Parameters ();
	explicit Parameters (Int32 paramNumber);
	explicit Parameters (InitMode initMode);
	Parameters (const Parameters& rhs);
	Parameters (Parameters&& rhs);
	virtual ~Parameters ();

	Parameters&			operator= (const Parameters& rhs);
	Parameters&			operator= (Parameters&& rhs);

	void				Clear ();
	bool				IsBinaryEqual (const Parameters& rhs) const;

	// ... ParameterGetter and ParameterAccessor methods ...
	virtual bool						IsNull () const override;
	virtual Parameters					CreateParameters () const override;
	virtual Parameters					CreatePartialCopy (Int32 firstInd, Int32 lastInd) const override;
	virtual GSErr						CopyVarsInto (Parameters& rhs, Int32 firstInd, Int32 lastInd, Int32 destInd) const override;
	virtual GSErr						InsertVarInto (Parameters& rhs, Int32 sourceInd, Int32 destInd) const override;

	virtual Int32						GetVarNumber () const override;
	virtual Int32						GetIndexOfName (const char* name) const override;
	virtual Int32						GetIndexOfName (const char* name, Int32 varIndex, bool forwardFromVarIndex) const override;

	virtual GSErr						GetVarName (Int32 index, char* name, Int32 buffSize) const override;
	virtual const char*					GetVarNameRef (Int32 index) const override;
	virtual short						GetVarType (Int32 index, bool* isArray = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr, GSErr* err = nullptr) const override;
	virtual unsigned char				GetVarFlags (Int32 index, GSErr* err = nullptr) const override;
	virtual bool						IsVarFix (Int32 index) const override;

	virtual bool						GetBoolVar (Int32 index, GSErr* err = nullptr) const override;
	virtual Int32						GetIntVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual ADB::AttributeIndex			GetAttrVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual double						GetNumVar (Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual GSErr						GetUStrVar (Int32 index, GS::UniString& retVal) const override;
	virtual double						GetParamA (GSErr* err = nullptr) const override;
	virtual double						GetParamB (GSErr* err = nullptr) const override;

	virtual bool						GetBoolArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr) const override;
	virtual Int32						GetIntArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual ADB::AttributeIndex			GetAttrArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual double						GetNumArrayVal (Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const override;
	virtual GSErr						GetUStrArrayVal (Int32 index, Int32 ind1, Int32 ind2, GS::UniString& retVal) const override;
	virtual const GS::UniChar::Layout*	GetUStrArrayValRef (Int32 index, Int32 ind1, Int32 ind2) const override;
	virtual GSErr						GetArrayUVal (Int32 index, Int32 ind1, Int32 ind2, double* numVal, GS::UniString& strVal, GS::UniString* numValDescription = nullptr) const override;

	virtual GSPtr						GetUArrayVar (Int32 index, Int32* len = nullptr, short* type = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr) const override;
	virtual GSPtr						GetUArrayDescription (Int32 index, Int32* len = nullptr, short* type = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr) const override;

	virtual const GS::UniChar::Layout*	GetUStrVarRef (Int32 index) const override;
	virtual const void*					GetUArrayRef (Int32 index, MemSize* len = nullptr) const override;

	virtual const GDL::Dictionary&		GetDictionaryVar (Int32 index, GSErr* err = nullptr) const override;

	virtual GSErr						ModifyVarName (Int32 index, const char* name) override;
	virtual GSErr						ModifyVarType (Int32 index, short newType, bool isArray, Int32 dim1, Int32 dim2, bool keepPreviousArrayValues = false) override;
	virtual GSErr						ModifyVarType_Simple (Int32 index, short newType) override;
	virtual GSErr						ModifyVarFlags (Int32 index, unsigned char flags) override;
	virtual GSErr						SetVarFix (Int32 index, bool isFix) override;
	virtual GSErr						SetVarFlagBits (Int32 index, unsigned char bits) override;
	virtual GSErr						ClearVarFlagBits (Int32 index, unsigned char bits) override;

	virtual GSErr						ModifyBoolVar (Int32 index, bool boolVal) override;
	virtual GSErr						ModifyIntVar (Int32 index, Int32 intVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyAttrVar (Int32 index, const ADB::AttributeIndex& attrVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyNumVar (Int32 index, double numVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyUStrVar (Int32 index, const GS::UniString& strVal) override;
	virtual GSErr						ModifyParamA (double val) override;
	virtual GSErr						ModifyParamB (double val) override;

	virtual GSErr						ModifyBoolArrayVal (Int32 index, Int32 ind1, Int32 ind2, bool boolVal) override;
	virtual GSErr						ModifyIntArrayVal (Int32 index, Int32 ind1, Int32 ind2, Int32 intVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyAttrArrayVal (Int32 index, Int32 ind1, Int32 ind2, const ADB::AttributeIndex& attrVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyNumArrayVal (Int32 index, Int32 ind1, Int32 ind2, double numVal, const GS::UniString* numValDescription = nullptr) override;
	virtual GSErr						ModifyUStrArrayVal (Int32 index, Int32 ind1, Int32 ind2, const GS::UniString& strVal) override;

	virtual GSErr						ModifyIntArray (Int32 index, const Int32* intVals, const GS::UniChar::Layout* arrayDescription = nullptr) override;
	virtual GSErr						ModifyIntArray (Int32 index, const GS::Array<Int32>& intVals) override;
	virtual GSErr						ModifyAttrArray (Int32 index, const GS::Array<ADB::AttributeIndex>& attrVals) override;
	virtual GSErr						ModifyNumArray (Int32 index, const double* numVals, const GS::UniChar::Layout* arrayDescription = nullptr) override;
	virtual GSErr						ModifyUStrArray (Int32 index, const GS::UniChar::Layout* strVals) override;

	virtual GSErr						ModifyArrayDimensions (const Int32 index, Int32 newDim1, Int32 newDim2) override;

	virtual GSErr						ModifyDictionaryVar (Int32 index, const GDL::Dictionary& dictionary) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const Int32 intVal) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<Int32>& intArray) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const double numVal) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<double>& numArray) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::UniString& stringVal) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<GS::UniString>& stringArray) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GDL::Dictionary& dictVal) override;
	virtual GSErr						ModifyDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path, const GS::Array<GDL::Dictionary>& dictArray) override;
	virtual GSErr						RemoveDictionaryVarMember (Int32 index, const GDL::DictionaryPath& path) override;

	virtual GSErr						AddVar (const char* name, short type, bool isArray, Int32 dim1, Int32 dim2) override;
	virtual GSErr						InsertNewVar (Int32 destInd, const char* name, short type, bool isArray, Int32 dim1, Int32 dim2) override;
	virtual GSErr						ReplaceVar (Int32 oldIndex, Int32 newIndex) override;
	virtual GSErr						DropVars (Int32 firstInd, Int32 lastInd) override;

	// ... GS::Object methods ...
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;

	// ... Restricted methods ...
	static Parameters	CreateParametersFromHandle (GS::Friend<ParametersConversion>, GSConstHandle addParHdl);
	GSConstHandle		GetHandleFromParameters (GS::Friend<ParametersConversion>) const;
	
private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic);
	GSErrCode			WriteVersion1 (GS::OChannel& oc) const;

	class ParametersImpl;
	GS::CopyOnWrite<ParametersImpl> impl;
};

GDL_DLL_EXPORT
Owner<Parameters> CreateParametersPtr (const ParameterGetter& paramGetter);


GDL_DLL_EXPORT extern const Parameters NullParameters;

}

#endif
