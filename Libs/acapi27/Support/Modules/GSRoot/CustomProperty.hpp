
// *****************************************************************************
//
//                          Struct CustomProperty
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB, KKr
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBCUSTOMPROPERTY_HPP
#define ODBCUSTOMPROPERTY_HPP


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "GSDebug.hpp"

// ======================== Struct CustomProperty =========================

namespace GS {

template<typename T> class HashSet;

	// Custom property

class CustomPropertyValue;

class GSROOT_DLL_EXPORT CustomProperty {
public:
	enum ValueType { Integer, Pointer };

	class GSROOT_DLL_EXPORT Value {
	private:
		ValueType type;

		union {
			UInt32 integer;
			const void*  pointer;
		};

	public:
		Value ();
		Value (UInt32 integer);
		Value (int integer);	// because of literals
		Value (const void* pointer);

		ValueType	GetType (void) const;

		UInt32		GetUInt32 (void) const;
		const void*		GetPtr	  (void) const;

		bool	operator== (const Value& rightOp) const;
		bool	operator!= (const Value& rightOp) const;

		ULong	GenerateHashValue (void) const;
	};

protected:
	class ValueNames;

	const char*		name;			// name of the custom property
	Value			defaultValue;	// default value of the property
	ValueNames&		valueNames;		// stores optional value names

	CustomProperty (const CustomProperty& source);				// disabled
	CustomProperty&	operator= (const CustomProperty& source);	// disabled

	friend class CustomPropertyValue;

	void	AddValueName (Value value, const char* valueName);

public:
	CustomProperty (const char* name, UInt32 defaultValue);
	CustomProperty (const char* name, int defaultValue);		// because of literals
	CustomProperty (const char* name, const void* defaultValue);
  
	virtual ~CustomProperty ();

	ValueType		GetValueType (void) const;

	const char*		GetName (void) const;

	CustomPropertyValue	GetDefaultValue (void) const;

	bool			HasDefaultValue (const CustomPropertyValue& value) const;
	bool			HasDefaultValue (const CustomProperty::Value& value) const;

	const char*		GetValueName (const CustomPropertyValue& value) const;

	CustomPropertyValue	operator() (UInt32 value) const;
	CustomPropertyValue	operator() (const void* value) const;

protected:
	static GS::HashSet<GS::CustomProperty*>* customProperties;
};



class GSROOT_DLL_EXPORT CustomPropertyValue {
protected:
	const CustomProperty*	customProperty;				// type of the property
	CustomProperty::Value	value;						// value of the property

	const CustomProperty&	GetCustomProperty (void) const;

public:
	CustomPropertyValue ();
	explicit CustomPropertyValue (const CustomProperty& customProperty);
	CustomPropertyValue (const CustomProperty& customProperty, UInt32 value, const char* valueName = nullptr);
	CustomPropertyValue (const CustomProperty& customProperty, int value, const char* valueName = nullptr);	// because of literals
	CustomPropertyValue (const CustomProperty& customProperty, void* value, const char* valueName = nullptr);
	CustomPropertyValue (const CustomProperty& customProperty, const CustomProperty::Value& value, const char* valueName = nullptr);

	CustomProperty::ValueType	GetValueType (void) const;

	UInt32								GetValueUInt32 (void) const;
	const void*								GetValuePtr	   (void) const;
	CustomProperty::Value	GetValue	   (void) const;

	inline bool		operator== (const CustomPropertyValue& rightOp) const;
	inline bool		operator!= (const CustomPropertyValue& rightOp) const;
	friend CustomProperty;
};


inline bool		CustomPropertyValue::operator== (const CustomPropertyValue& rightOp) const
{
	DBASSERT (customProperty == rightOp.customProperty);

	return (value == rightOp.value);
}


inline bool		CustomPropertyValue::operator!= (const CustomPropertyValue& rightOp) const
{
	DBASSERT (customProperty == rightOp.customProperty);

	return (value != rightOp.value);
}

}	// namespace GS
// ________________________ Struct CustomProperty _________________________


#endif
