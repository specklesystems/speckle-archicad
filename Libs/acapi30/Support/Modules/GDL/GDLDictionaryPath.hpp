
#ifndef GS_GDL_DICTIONARYPATH_HPP
#define GS_GDL_DICTIONARYPATH_HPP

#include "GDLExport.h"
#include "Optional.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "GDLDictionaryException.hpp"
#include "GDLObjectUniqueId.hpp"



namespace GDL {

DECLARE_EXCEPTION_CLASS (InvalidFieldNameException, DictionaryException, Error, GDL_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (InvalidDictionaryPathException, DictionaryException, Error, GDL_DLL_EXPORT)



class GDL_DLL_EXPORT FieldName
{
public:
	FieldName (const GS::String& name);

	const GS::String&		AsString () const;
	ULong					GenerateHashValue (void) const				{ return GS::CalculateHashValue (upperCaseIndex); }

	bool					operator== (const FieldName& rightOp) const { return upperCaseIndex == rightOp.upperCaseIndex; }
	bool					operator!= (const FieldName& rightOp) const { return !((*this) == rightOp); }

	static bool				IsValidName (const GS::String& name);

private:
	RuntimeUniqueId<GS::String> upperCaseIndex;
	RuntimeUniqueId<GS::String> originalCaseIndex;
};


class GDL_DLL_EXPORT DictionaryPath
{
public:
	class GDL_DLL_EXPORT Item
	{
	public:
		Item (const FieldName& fieldName);
		Item (const FieldName& fieldName, const UIndex arrayIndex);

		bool					HasArrayIndex () const;
		const FieldName&		GetFieldName () const;
		UIndex					GetArrayIndex () const;
		Item					AddArrayIndex (UIndex) const;
		Item					RemoveArrayIndex () const;

		void					ModifyArrayIndex (GS::Optional<UIndex>);

	private:
		FieldName				fieldName;
		GS::Optional<UIndex>	arrayIndex;
	};

	DictionaryPath (const FieldName& fieldName);
	DictionaryPath (const FieldName& fieldName, const UIndex index);
	DictionaryPath (std::initializer_list<Item> itemList);

	DictionaryPath&		Append (const FieldName& fieldName);
	DictionaryPath&		Append (const FieldName& fieldName, const UIndex arrayIndex);
	DictionaryPath&		Append (const GDL::DictionaryPath::Item& item);
	const Item&			GetLastItem () const;
	USize				GetSize () const;
	const GDL::DictionaryPath::Item&	operator [] (UIndex index) const;
	void				ModifyArrayIndex (UInt32 index, GS::Optional<UIndex> arrayIndex);

private:
	GS::ArrayFB<Item, 6>	pathItems;
};

}

#endif // GS_GDL_DICTIONARYPATH_HPP
