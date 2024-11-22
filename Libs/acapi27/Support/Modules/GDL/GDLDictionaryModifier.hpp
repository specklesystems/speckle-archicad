
#ifndef GS_GDL_GDLDICTIONARYMODIFIER_HPP
#define GS_GDL_GDLDICTIONARYMODIFIER_HPP

#include "GDLExport.h"
#include "GDLDictionaryValueTypes.hpp"
#include "UniString.hpp"
#include "GDLParamTypes.hpp"

namespace GDL {

class Dictionary;
class DictionaryPath;

}


namespace GDL {


class GDL_DLL_EXPORT IDictionaryModifier {
public:
	IDictionaryModifier ();
	virtual ~IDictionaryModifier ();

	enum class CanSetResult {
		Ok,
		ArrayInArrayError,
		NonArrayUsedAsArrayError,
		CollectionTypeChangeError,
		InvalidValueTypeChangeError,
		MixedArrayError
	};

	virtual CanSetResult	CanSet (const DictionaryPath& path, DictionaryCollectionType collectionType, DictionaryValueType valueType) const = 0;

	virtual void			SetInteger (const DictionaryPath& path, Int32 value) = 0;
	virtual void			SetDouble (const DictionaryPath& path, double value) = 0;
	virtual void			SetString (const DictionaryPath& path, const GS::UniString& value) = 0;
	virtual void			SetDictionary (const DictionaryPath& path, const Dictionary& value) = 0;

	virtual void			SetIntegerArray (const DictionaryPath& path, const GS::Array<Int32>& value) = 0;
	virtual void			SetDoubleArray (const DictionaryPath& path, const GS::Array<double>& value) = 0;
	virtual void			SetStringArray (const DictionaryPath& path, const GS::Array<GS::UniString>& value) = 0;
	virtual void			SetDictionaryArray (const DictionaryPath& path, const GS::Array<Dictionary>& value) = 0;

	virtual void			RemoveField (const DictionaryPath& path) = 0;
};


class GDL_DLL_EXPORT ParameterAccessorDictionaryModifier: public IDictionaryModifier {
public:
	ParameterAccessorDictionaryModifier (GDL::ParameterAccessor& parameterAccessor, Int32 index);
	virtual ~ParameterAccessorDictionaryModifier ();

	virtual CanSetResult	CanSet (const DictionaryPath& path, DictionaryCollectionType collectionType, DictionaryValueType valueType) const override;

	virtual void			SetInteger (const DictionaryPath& path, Int32 value) override;
	virtual void			SetDouble (const DictionaryPath& path, double value) override;
	virtual void			SetString (const DictionaryPath& path, const GS::UniString& value) override;
	virtual void			SetDictionary (const DictionaryPath& path, const Dictionary& value) override;

	virtual void			SetIntegerArray (const DictionaryPath& path, const GS::Array<Int32>& value) override;
	virtual void			SetDoubleArray (const DictionaryPath& path, const GS::Array<double>& value) override;
	virtual void			SetStringArray (const DictionaryPath& path, const GS::Array<GS::UniString>& value) override;
	virtual void			SetDictionaryArray (const DictionaryPath& path, const GS::Array<Dictionary>& value) override;

	virtual void			RemoveField (const DictionaryPath& path) override;

private:
	GDL::ParameterAccessor& parameterAccessor;
	Int32					index;
};

class GDL_DLL_EXPORT DictionaryModifier: public IDictionaryModifier {
public:
	DictionaryModifier (Dictionary&	dictionary);
	virtual ~DictionaryModifier ();

	virtual CanSetResult	CanSet (const DictionaryPath& path, DictionaryCollectionType collectionType, DictionaryValueType valueType) const override;

	virtual void			SetInteger (const DictionaryPath& path, Int32 value) override;
	virtual void			SetDouble (const DictionaryPath& path, double value) override;
	virtual void			SetString (const DictionaryPath& path, const GS::UniString& value) override;
	virtual void			SetDictionary (const DictionaryPath& path, const Dictionary& value) override;

	virtual void			SetIntegerArray (const DictionaryPath& path, const GS::Array<Int32>& value) override;
	virtual void			SetDoubleArray (const DictionaryPath& path, const GS::Array<double>& value) override;
	virtual void			SetStringArray (const DictionaryPath& path, const GS::Array<GS::UniString>& value) override;
	virtual void			SetDictionaryArray (const DictionaryPath& path, const GS::Array<Dictionary>& value) override;

	virtual void			RemoveField (const DictionaryPath& path) override;

private:
	GDL::Dictionary& dictionary;
};

}

#endif
