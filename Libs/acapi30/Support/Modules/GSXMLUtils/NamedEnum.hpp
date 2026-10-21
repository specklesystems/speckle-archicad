// *********************************************************************************************************************
// Utility class for enum serialization
//
// Module:			GSXMLUtils
// Namespace:		GSXML
// Contact person:	RA
//
// *********************************************************************************************************************

#ifndef	_NAMEDENUM_HPP_
#define	_NAMEDENUM_HPP_

#pragma once

#include "Array.hpp"
#include "StringConversion.hpp"
#include "XMLChannel.hpp"
#include <cstdio>

namespace GSXML
{

template<typename Type, bool integral = std::is_integral<Type>::value>
struct GetAsInteger;

template<typename Type>
struct GetAsInteger<Type, true> {
	using IntegerType = Type;
};

template<typename Type>
struct GetAsInteger<Type, false> {
	using IntegerType = typename std::underlying_type<Type>::type;
};


template <class Type>
struct NamedEnumItem
{
	Type value;
	const char* name;
};

template<class T>
using NamedEnumItemInfo = GS::Array<NamedEnumItem<T>>;



template <class Type>
class NamedEnumType
{
public:
	NamedEnumType (const NamedEnumItemInfo<Type>& itemsInfo, bool flagEnumItems = false, bool strictEnumItems = false);

	void						   AddItemsInfo (const NamedEnumItemInfo<Type>& itemsInfo);
	const NamedEnumItemInfo<Type>& GetItemsInfo () const;

	bool		  GetValue (const GS::UniString& strValue, Type& value) const;
	GS::UniString GetString (Type value) const;

	GSErrCode	WriteXML (GS::XMLOChannel& ox, const char* tagName, Type value) const;
	GSErrCode	ReadXML (GS::XMLIChannel& ix, const char* tagName, Type& value) const;

	GSErrCode	WriteXMLAttr (GS::XMLOChannel& ox, const char* attrName, Type value) const;
	GSErrCode	ReadXMLAttr (GS::XMLIChannel& ix, const char* attrName, Type& value) const;

private:
	NamedEnumItemInfo<Type> itemsInfo;

	bool flags;
	bool strictValues;
	const char* FlagSeparator = "|";

	enum class XMLEntityType {
		Attribute,
		Tag
	};

	GSErrCode	Write (GS::XMLOChannel& ox, XMLEntityType entity, const char* name, Type value) const;
	GSErrCode	Read (GS::XMLIChannel& ix, XMLEntityType entity, const char* name, Type& value) const;

	GSErrCode	WriteStringToChannel (GS::XMLOChannel& ox, XMLEntityType entity, const char* name, const GS::UniString& strValue) const;
	GSErrCode	ReadStringFromChannel (GS::XMLIChannel& ix, XMLEntityType entity, const char* name, GS::UniString& strValue) const;

	GS::Array<GS::UniString> GetStringArray (Type value) const;

	bool GetValue (const GS::UniString& strValue, GS::Array<Type>& valueArray) const;

	bool GetSingleValue (const GS::UniString& strValue, Type& value) const;
	bool Check (Type value, bool strictCheck = false) const;

	Type DefaultValue () const;

};


template <class Type>
Type NamedEnumType<Type>::DefaultValue () const
{
	DBASSERT (!itemsInfo.IsEmpty ());

	return itemsInfo.GetFirst ().value;
}


template <class Type>
const NamedEnumItemInfo<Type>& NamedEnumType<Type>::GetItemsInfo () const
{
	return itemsInfo;
}


template <class Type>
NamedEnumType<Type>::NamedEnumType (const NamedEnumItemInfo<Type>& itemsInfo,
									bool						   flagEnumItems,
									bool						   strictEnumItems /*= false*/)
{
	flags = flagEnumItems;
	strictValues = strictEnumItems;

	AddItemsInfo (itemsInfo);
}


template <class Type>
void NamedEnumType<Type>::AddItemsInfo (const NamedEnumItemInfo<Type>& itemsInfo)
{
	this->itemsInfo.Append (itemsInfo);
}


template <class Type>
GS::UniString NamedEnumType<Type>::GetString (Type value) const
{
	GS::UniString	result;

	GS::Array<GS::UniString> valueArray = GetStringArray (value);
	GS::Array<GS::UniString>::Iterator iter = valueArray.Begin();
	if (iter != valueArray.End ()) {
		result = *iter;
		++iter;
	}
	while (iter != valueArray.End ()) {
		result += FlagSeparator;
		result += *iter;
		++iter;
	}
	return result;
}


template <class Type>
GS::Array<GS::UniString> NamedEnumType<Type>::GetStringArray (Type value) const
{
	DBASSERT (Check (value));

	GS::Array<GS::UniString> result;

	for (const NamedEnumItem<Type>& itemInfo : itemsInfo) {
		if (flags) {
			auto valueAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (value);
			auto actItemsValueAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (itemInfo.value);

			if (static_cast<typename GetAsInteger<Type>::IntegerType> (valueAsInteger & actItemsValueAsInteger) == actItemsValueAsInteger) {
				value = static_cast<Type> (valueAsInteger & (~actItemsValueAsInteger));
				result.Push (itemInfo.name);
			}
		} else {
			if (itemInfo.value == value) {
				result.Push (itemInfo.name);
				return result;
			}
		}
	}

	if (!strictValues && value != static_cast<Type> (0)) {
		if (flags) {
			result.Push (GS::UniString::Printf ("0x%x", value));
		} else {
			result.Push (GS::UniString::Printf ("%d", value));
		}
	}

	return result;
}


template <class Type>
bool NamedEnumType<Type>::GetSingleValue (const GS::UniString& strValue, Type& value) const
{
	bool result = false;
	value = DefaultValue ();

	for (const NamedEnumItem<Type> itemInfo : itemsInfo) {
		if (strValue == itemInfo.name) {
			value = itemInfo.value;
			result = true;
			break;
		}
	}

	if (!result) {
		UInt32 tmpValue = 0;
		if (sscanf (strValue.ToCStr ().Get(), "0x%x", &tmpValue) == 1) { //We don't need to use asserts while parsing, so C sscanf is fine
			result = true;
		} else if (sscanf (strValue.ToCStr ().Get (), "0X%x", &tmpValue) == 1) {
			result = true;
		} else if (GS::UniStringToValue (strValue, tmpValue)) {
			result = true;
		} else {
			return false;
		}
		value = (Type)tmpValue;
	}

	if (strictValues) {
		if (Check (value))
			return true;
		value = DefaultValue ();
		return false;
	}
	return result;
}


template <class Type>
bool NamedEnumType<Type>::GetValue (const GS::UniString& strValue,
									GS::Array<Type>&	 valueArray) const
{
	UIndex startStrValueIdx = 0;
	while (startStrValueIdx < strValue.GetLength()) {
		UIndex endStrValueIdx = strValue.FindFirst (FlagSeparator, startStrValueIdx);
		if (endStrValueIdx > strValue.GetLength())
			endStrValueIdx = strValue.GetLength();
		GS::UniString tmpStrValue = strValue.GetSubstring (startStrValueIdx, endStrValueIdx - startStrValueIdx);
		tmpStrValue.Trim ();
		if (tmpStrValue.IsEmpty ()) {
			startStrValueIdx = endStrValueIdx + GS::Strlen32 (FlagSeparator);
			continue;
		}

		Type tmpValue;
		if (GetSingleValue (tmpStrValue, tmpValue)) {
			valueArray.Push (tmpValue);
		} else {
			DBBREAK_GUID ("80686156-002B-4D6E-A62D-7585E7DBCDC9");
		}
		startStrValueIdx = endStrValueIdx + GS::Strlen32 (FlagSeparator);
	}

	return true;
}


template <class Type>
bool NamedEnumType<Type>::GetValue (const GS::UniString& strValue, Type& value) const
{
	bool result;
	if (flags)
		value = static_cast<Type> (0);
	else
		value = DefaultValue ();

	GS::Array<Type> valueArray;
	typename GS::Array<Type>::ConstIterator iter;
	if (GetValue (strValue, valueArray)) {
		iter = valueArray.Begin();
		if (flags) {
			while (iter != valueArray.End ()) {
				auto valueAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (value);
				auto iterAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (*iter);

				value = static_cast<Type> (valueAsInteger | iterAsInteger);
				++iter;
			}
			result = true;
		} else {
			if (iter != valueArray.End ()) {
				value = static_cast<Type> (*iter);
				++iter;
				result = (iter == valueArray.End ());
			} else {
				result = false;
			}
		}
		DBASSERT (Check (value));
		return result;
	}

	return false;
}


template <class Type>
bool NamedEnumType<Type>::Check (Type value, bool strictCheck) const
{
	DBASSERT (!itemsInfo.IsEmpty ());

	if (!strictValues && !strictCheck)
		return true;

	for (const NamedEnumItem<Type>& itemInfo : itemsInfo) {
		if (flags) {
			auto valueAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (value);
			auto actItemsValueAsInteger = static_cast<typename GetAsInteger<Type>::IntegerType> (itemInfo.value);

			if (static_cast<typename GetAsInteger<Type>::IntegerType> (valueAsInteger & actItemsValueAsInteger) == actItemsValueAsInteger) {
				value = static_cast<Type> (valueAsInteger & (~actItemsValueAsInteger));
			}
		} else {
			if (itemInfo.value == value) {
				return true;
			}
		}
	}

	if (flags) {
		return (value == static_cast<Type> (0));
	}

	return false;
}


template <class Type>
GSErrCode NamedEnumType<Type>::WriteXML (GS::XMLOChannel& ox, const char* tagName, Type value) const
{
	return Write (ox, XMLEntityType::Tag, tagName, value);
}


template <class Type>
GSErrCode NamedEnumType<Type>::ReadXML (GS::XMLIChannel& ix, const char* tagName, Type& value) const
{
	return Read (ix, XMLEntityType::Tag, tagName, value);
}


template <class Type>
GSErrCode NamedEnumType<Type>::WriteXMLAttr (GS::XMLOChannel& ox, const char* attrName, Type value) const
{
	return Write (ox, XMLEntityType::Attribute, attrName, value);
}


template <class Type>
GSErrCode NamedEnumType<Type>::ReadXMLAttr (GS::XMLIChannel& ix, const char* attrName, Type& value) const
{
	return Read (ix, XMLEntityType::Attribute, attrName, value);
}


template <class Type>
GSErrCode NamedEnumType<Type>::Write (GS::XMLOChannel& ox, XMLEntityType entity, const char* name, Type value) const
{
	if (DBERROR_GUID (!Check (value, true), "0117E8E1-62B8-4E90-855E-6A9B240F8821")) {
		return Error;
	}

	return WriteStringToChannel (ox, entity, name, GetString (value));
}


template <class Type>
GSErrCode NamedEnumType<Type>::Read (GS::XMLIChannel& ix, XMLEntityType entity, const char* name, Type& value) const
{
	GSErrCode err = NoError;
	value = DefaultValue ();

	GS::UniString strValue;
	err = ReadStringFromChannel (ix, entity, name, strValue);
	if (err != NoError)
		return err;

	if (DBERROR_GUID (!GetValue (strValue, value), "F267D23B-87A9-4B0F-B1AD-75514CC31A38")) {
		ix.AddMessage (GS::UniString::SPrintf ("Invalid value for NamedEnumType: \"%s\"", strValue.ToCStr ().Get ()));
		err = Error;
	}

	return err;
}


template <class Type>
GSErrCode NamedEnumType<Type>::WriteStringToChannel  (GS::XMLOChannel& ox, XMLEntityType entity, const char* name, const GS::UniString& strValue)const 
{
	switch (entity) {
	case NamedEnumType::XMLEntityType::Tag: 
		return ox.WriteXML (name, strValue);
	case NamedEnumType::XMLEntityType::Attribute:
		return ox.WriteXMLAttr (name, strValue);
	default: 
		DBBREAK ();
		return Error;
	}
}


template <class Type>
GSErrCode NamedEnumType<Type>::ReadStringFromChannel (GS::XMLIChannel& ix, XMLEntityType entity, const char* name, GS::UniString& strValue) const
{
	switch (entity) {
	case NamedEnumType::XMLEntityType::Tag:
		return ix.ReadXML (name, strValue);
	case NamedEnumType::XMLEntityType::Attribute:
		return ix.ReadXMLAttr (name, strValue);
	default:
		DBBREAK ();
		return Error;
	}
}


}

#endif //_NAMEDENUM_HPP_
