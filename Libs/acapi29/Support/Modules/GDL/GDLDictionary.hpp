// *********************************************************************************************************************
// Description:		GDLDictionary.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	KV
// *********************************************************************************************************************

#ifndef GDLDICTIONARY_HPP
#define GDLDICTIONARY_HPP

#include "Array.hpp"
#include "GSFriend.hpp"
#include "CopyOnWrite.hpp"
#include "GDLDictionaryException.hpp"
#include "GDLDictionaryPath.hpp"
#include "GDLDictionaryValueTypes.hpp"
#include "GDLExport.h"
#include "Object.hpp"
#include "Owner.hpp"


namespace GDL
{

class IDictionaryScheme;
class IDictionaryValueVisitor;


DECLARE_EXCEPTION_CLASS (MissingFieldNameException, DictionaryException, Error, GDL_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (InvalidDictionaryTypeException, DictionaryException, Error, GDL_DLL_EXPORT)

class GDL_DLL_EXPORT Dictionary : public GS::Object
{
	DECLARE_CLASS_INFO;

public:
	Dictionary ();
	Dictionary (const Dictionary& rhs);
	Dictionary (Dictionary&& rhs);
	~Dictionary ();

	Dictionary&							operator= (const Dictionary& rhs);
	Dictionary&							operator= (Dictionary&& rhs);

	bool								operator== (const Dictionary& right) const;
	bool								operator!= (const Dictionary& right) const;

	bool								Contains (const DictionaryPath& path) const;
	DictionaryValueType					GetValueType (const DictionaryPath& path) const;
	DictionaryCollectionType			GetCollectionType (const DictionaryPath& path) const;

	Int32								GetInteger (const DictionaryPath& path) const;
	double								GetDouble (const DictionaryPath& path) const;
	const GS::UniString&				GetString (const DictionaryPath& path) const;
	const Dictionary&					GetDictionary (const DictionaryPath& path) const;

	const GS::Array<Int32>&				GetIntegerArray (const DictionaryPath& path) const;
	const GS::Array<double>&			GetDoubleArray (const DictionaryPath& path) const;
	const GS::Array<GS::UniString>&		GetStringArray (const DictionaryPath& path) const;
	const GS::Array<Dictionary>&		GetDictionaryArray (const DictionaryPath& path) const;
	USize								GetArraySize (const DictionaryPath& path) const;

	void								SetInteger (const DictionaryPath& path, Int32 value);
	void								SetDouble (const DictionaryPath& path, double value);
	void								SetString (const DictionaryPath& path, const GS::UniString& value);
	void								SetDictionary (const DictionaryPath& path, const Dictionary& value);
	
	void								SetIntegerArray (const DictionaryPath& path, const GS::Array<Int32>& value);
	void								SetDoubleArray (const DictionaryPath& path, const GS::Array<double>& value);
	void								SetStringArray (const DictionaryPath& path, const GS::Array<GS::UniString>& value);
	void								SetDictionaryArray (const DictionaryPath& path, const GS::Array<Dictionary>& value);
	
	bool								RemoveField (const DictionaryPath& path);

	virtual GSErrCode					Read (GS::IChannel& ic) override;
	virtual GSErrCode					Write (GS::OChannel& oc) const override;

	virtual GS::ErrorStatus				Store (GS::ObjectState& os) const override;
	virtual GS::ErrorStatus				Restore (const GS::ObjectState& os) override;
	
	void								VisitFields (IDictionaryValueVisitor&) const;
	void								VisitFieldsInOrder (IDictionaryValueVisitor&) const;

	GS::UniString						SerializeJSON () const;
	GSErrCode							DeserializeJSON (const GS::UniString& input);

private:
	void								Clear ();

	GSErrCode							ReadVersion1 (GS::IChannel& ic);
	GSErrCode							WriteVersion1 (GS::OChannel& oc) const;

	class DictionaryImpl;
	GS::CopyOnWrite<DictionaryImpl> impl;
};

}

#endif
