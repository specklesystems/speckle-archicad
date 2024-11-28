
// *****************************************************************************
//
// Declaration of Value class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"

#include "UniString.hpp"
#include "Ref.hpp"


namespace JSON {

class ValueVisitor;

// ---------------------------------- Value ------------------------------------

class JSON_API Value {

public:
	enum Type {
		NullType	= 0,
		BoolType	= 1,
		ObjectType	= 2,
		ArrayType	= 3,
		StringType	= 4,
		NumberType	= 5
	};

private:
	Type			m_type;

protected:
	Value (Type type);

public:
	virtual ~Value ();

private:
	Value (const Value& source);				// disabled
	Value& operator= (const Value& source);		// disabled

public:
	Type			GetType () const;
	GS::UniString	GetTypeAsString () const;

	bool			IsNull () const;
	bool			IsBool () const;
	bool			IsNumber () const;
	bool			IsString () const;
	bool			IsObject () const;
	bool			IsArray () const;

	virtual void	Accept (ValueVisitor* visitor) = 0;

};

using ValueRef      = GS::Ref<Value>;
using ValueConstRef = GS::Ref<const Value>;

// -------------------------------- NullValue ----------------------------------

class JSON_API NullValue: public Value {

public:
	typedef GS::Ref<NullValue, GS::Counter>	NullValueRef;

public:
	NullValue ();
	virtual ~NullValue ();

private:
	NullValue (const NullValue& source);				// disabled
	NullValue& operator= (const NullValue& source);		// disabled

public:
	static NullValueRef		Cast (const ValueRef& value);
	static const NullValue&	Cast (const Value& value);
	static NullValue&		Cast (Value& value);

	virtual void		Accept (ValueVisitor* visitor) override;
};

typedef NullValue::NullValueRef	NullValueRef;

// -------------------------------- BoolValue ----------------------------------

class JSON_API BoolValue: public Value {

public:
	typedef GS::Ref<BoolValue, GS::Counter>	BoolValueRef;

private:
	bool		m_value;

public:
	explicit BoolValue (bool value);
	virtual ~BoolValue ();

private:
	BoolValue (const BoolValue& source);				// disabled
	BoolValue& operator= (const BoolValue& source);		// disabled

public:
	bool				IsFalse () const;
	bool				IsTrue () const;
	bool				Get () const;
	void				Set (bool value);

	static BoolValueRef		Cast (const ValueRef& value);
	static const BoolValue&	Cast (const Value& value);
	static BoolValue&		Cast (Value& value);

	virtual void		Accept (ValueVisitor* visitor) override;
};

typedef BoolValue::BoolValueRef	BoolValueRef;

// -------------------------------- NumberValue --------------------------------

class JSON_API NumberValue: public Value {

public:
	typedef GS::Ref<NumberValue, GS::Counter>	NumberValueRef;

	enum NumberValueType {
		Int64Type	= 1,
		UInt64Type	= 2,
		DoubleType	= 4
	};

private:
	union Number {
		Int64	m_int64Value;
		UInt64	m_uint64Value;
		double	m_double;
	} m_value;

	NumberValueType	m_type;

public:
	explicit NumberValue (Int8 value);
	explicit NumberValue (UInt8 value);
	explicit NumberValue (Int16 value);
	explicit NumberValue (UInt16 value);
	explicit NumberValue (Int32 value);
	explicit NumberValue (UInt32 value);
	explicit NumberValue (Int64 value);
	explicit NumberValue (UInt64 value);
	explicit NumberValue (double value);
	virtual ~NumberValue ();

private:
	NumberValue (const NumberValue& source);				// disabled
	NumberValue& operator= (const NumberValue& source);		// disabled

public:
	GS::UniString	GetNumberValueTypesAsString () const;

	bool			IsFloatingPoint () const;
	bool			IsIntegral () const;
	Int32			GetSignum () const;

	bool			IsInt8 () const;
	bool			IsUInt8 () const;
	bool			IsInt16 () const;
	bool			IsUInt16 () const;
	bool			IsInt32 () const;
	bool			IsUInt32 () const;
	bool			IsInt64 () const;
	bool			IsUInt64 () const;
	bool			IsDouble () const;

	Int8			GetInt8 () const;
	bool			Get (Int8& value) const;
	void			Set (Int8 value);

	UInt8			GetUInt8 () const;
	bool			Get (UInt8& value) const;
	void			Set (UInt8 value);

	Int16			GetInt16 () const;
	bool			Get (Int16& value) const;
	void			Set (Int16 value);

	UInt16			GetUInt16 () const;
	bool			Get (UInt16& value) const;
	void			Set (UInt16 value);

	Int32			GetInt32 () const;
	bool			Get (Int32& value) const;
	void			Set (Int32 value);

	UInt32			GetUInt32 () const;
	bool			Get (UInt32& value) const;
	void			Set (UInt32 value);

	Int64			GetInt64 () const;
	bool			Get (Int64& value) const;
	void			Set (Int64 value);

	UInt64			GetUInt64 () const;
	bool			Get (UInt64& value) const;
	void			Set (UInt64 value);

	double			GetDouble () const;
	bool			Get (double& value) const;
	void			Set (double value);

	static NumberValueRef		Cast (const ValueRef& value);
	static const NumberValue&	Cast (const Value& value);
	static NumberValue&			Cast (Value& value);
	
	virtual void	Accept (ValueVisitor* visitor) override;

};

typedef NumberValue::NumberValueRef	NumberValueRef;

// -------------------------------- StringValue --------------------------------

class JSON_API StringValue: public Value {

public:
	typedef GS::Ref<StringValue, GS::Counter>	StringValueRef;

private:
	GS::UniString		m_value;

public:
	explicit StringValue (const GS::UniString& value);
	virtual ~StringValue ();

private:
	StringValue (const StringValue& source);				// disabled
	StringValue& operator= (const StringValue& source);		// disabled

public:
	void					Set (const GS::UniString& value);
	GS::UniString			Get () const;

	static StringValueRef		Cast (const ValueRef& value);
	static const StringValue&	Cast (const Value& value);
	static StringValue&			Cast (Value& value);

	virtual void			Accept (ValueVisitor* visitor) override;
};

typedef StringValue::StringValueRef	StringValueRef;

// -------------------------------- ObjectMember -------------------------------

class JSON_API ObjectMember {

private:
	GS::UniString		m_name;
	ValueRef			m_value;

public:
	ObjectMember (const GS::UniString& name, const ValueRef& value);
	ObjectMember ();
	~ObjectMember ();
	
	ObjectMember&			SetName (const GS::UniString& name);
	const GS::UniString&	GetName () const;
	ObjectMember&			SetValue (const ValueRef& value);
	ValueRef&				GetValue ();
	const ValueRef&			GetValue () const;
};

// -------------------------------- ArrayValue ---------------------------------

class JSON_API ArrayValue: public Value {

public:
	typedef GS::Ref<ArrayValue, GS::Counter>	ArrayValueRef;

private:
	GS::Array <ValueRef>	m_items;

public:
	ArrayValue ();
	virtual ~ArrayValue ();

private:
	ArrayValue (const ArrayValue& source);					// disabled
	ArrayValue& operator= (const ArrayValue& source);		// disabled

public:
	USize			GetSize () const;
	bool			IsEmpty () const;

	ValueRef&		Get (UIndex index);
	const ValueRef&	Get (UIndex index) const;

	void			Enumerate (const std::function<void (const ValueRef& value)>& processor) const;

	template <class T>
	void			Enumerate (const std::function<void (const GS::Ref<T, GS::Counter>& value)>& processor) const
	{
		if (DBERROR (processor == nullptr)) {
			throw GS::IllegalArgumentException ("Failed to enumerate array, processor is null.", __FILE__, __LINE__);
		}

		Enumerate ([&](const ValueRef& value)
		{
			processor (T::Cast (value));
		});
	}

	ArrayValue&		AddNull ();
	ArrayValue&		Add (bool value);
	ArrayValue&		Add (Int8 value);
	ArrayValue&		Add (UInt8 value);
	ArrayValue&		Add (Int16 value);
	ArrayValue&		Add (UInt16 value);
	ArrayValue&		Add (Int32 value);
	ArrayValue&		Add (UInt32 value);
	ArrayValue&		Add (Int64 value);
	ArrayValue&		Add (UInt64 value);
	ArrayValue&		Add (double value);
	ArrayValue&		Add (const GS::UniString& value);
	ArrayValue&		Add (const char* value);
	ArrayValue&		AddValue (const ValueRef& value);

	void			Remove (UIndex index);
	void			Clear ();

	static ArrayValueRef		Cast (const ValueRef& value);
	static const ArrayValue&	Cast (const Value& value);
	static ArrayValue&			Cast (Value& value);

	virtual void	Accept (ValueVisitor* visitor) override;
};

typedef ArrayValue::ArrayValueRef	ArrayValueRef;

// -------------------------------- ObjectValue --------------------------------

class JSON_API ObjectValue: public Value {

public:
	typedef GS::Ref<ObjectValue, GS::Counter>	ObjectValueRef;

private:
	GS::Array <ObjectMember>	m_members;

public:
	ObjectValue ();
	virtual ~ObjectValue ();

private:
	ObjectValue (const ObjectValue& source);				// disabled
	ObjectValue& operator= (const ObjectValue& source);		// disabled

public:
	USize			GetSize () const;
	bool			IsEmpty () const;

	ValueRef&		Get (UIndex index);
	const ValueRef&	Get (UIndex index) const;
	ValueRef		Get (const GS::UniString& name);
	const ValueRef	Get (const GS::UniString& name) const;

	GS::UniString	GetName (UIndex index) const;
	bool			HasMember (const GS::UniString& name) const;

	void			GetMandatoryMember (const GS::UniString& name, ValueRef& value);
	void			GetMandatoryMember (const GS::UniString& name, ValueRef& value) const;
	void			GetMandatoryMember (const GS::UniString& name, ObjectValueRef& value);
	void			GetMandatoryMember (const GS::UniString& name, ObjectValueRef& value) const;
	void			GetMandatoryMember (const GS::UniString& name, ArrayValueRef& value);
	void			GetMandatoryMember (const GS::UniString& name, ArrayValueRef& value) const;
	void			GetMandatoryMember (const GS::UniString& name, bool& value) const;
	void			GetMandatoryMember (const GS::UniString& name, Int8& value) const;
	void			GetMandatoryMember (const GS::UniString& name, UInt8& value) const;
	void			GetMandatoryMember (const GS::UniString& name, Int16& value) const;
	void			GetMandatoryMember (const GS::UniString& name, UInt16& value) const;
	void			GetMandatoryMember (const GS::UniString& name, Int32& value) const;
	void			GetMandatoryMember (const GS::UniString& name, UInt32& value) const;
	void			GetMandatoryMember (const GS::UniString& name, Int64& value) const;
	void			GetMandatoryMember (const GS::UniString& name, UInt64& value) const;
	void			GetMandatoryMember (const GS::UniString& name, double& value) const;
	void			GetMandatoryMember (const GS::UniString& name, GS::UniString& value) const;

	void			GetOptionalMember (const GS::UniString& name, ValueRef& value, ValueRef defaultValue);
	void			GetOptionalMember (const GS::UniString& name, ValueRef& value, ValueRef defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, ObjectValueRef& value, ObjectValueRef& defaultValue);
	void			GetOptionalMember (const GS::UniString& name, ObjectValueRef& value, ObjectValueRef& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, ArrayValueRef& value, ArrayValueRef defaultValue);
	void			GetOptionalMember (const GS::UniString& name, ArrayValueRef& value, ArrayValueRef& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, bool& value, const bool& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, Int8& value, const Int8& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, UInt8& value, const UInt8& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, Int16& value, const Int16& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, UInt16& value, const UInt16& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, Int32& value, const Int32& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, UInt32& value, const UInt32& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, Int64& value, const Int64& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, UInt64& value, const UInt64& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, double& value, const double& defaultValue) const;
	void			GetOptionalMember (const GS::UniString& name, GS::UniString& value, const GS::UniString& defaultValue) const;

	bool			GetOptionalMember (const GS::UniString& name, ValueRef& value) const;
	bool			GetOptionalMember (const GS::UniString& name, ObjectValueRef& value) const;
	bool			GetOptionalMember (const GS::UniString& name, ArrayValueRef& value) const;

	bool			GetOptionalMember (const GS::UniString& name, bool& value) const;
	bool			GetOptionalMember (const GS::UniString& name, Int8& value) const;
	bool			GetOptionalMember (const GS::UniString& name, UInt8& value) const;
	bool			GetOptionalMember (const GS::UniString& name, Int16& value) const;
	bool			GetOptionalMember (const GS::UniString& name, UInt16& value) const;
	bool			GetOptionalMember (const GS::UniString& name, Int32& value) const;
	bool			GetOptionalMember (const GS::UniString& name, UInt32& value) const;
	bool			GetOptionalMember (const GS::UniString& name, Int64& value) const;
	bool			GetOptionalMember (const GS::UniString& name, UInt64& value) const;
	bool			GetOptionalMember (const GS::UniString& name, double& value) const;
	bool			GetOptionalMember (const GS::UniString& name, GS::UniString& value) const;

	void			Enumerate (const std::function<void (const ObjectMember& member)>& processor) const;
	void			Enumerate (const std::function<void (const GS::UniString& name, const ValueRef& value)>& processor) const;

	template <class T>
	void			Enumerate (const std::function<void (const GS::UniString& name, const GS::Ref<T, GS::Counter>& value)>& processor) const
	{
		if (DBERROR (processor == nullptr)) {
			throw GS::IllegalArgumentException ("Failed to enumerate object, processor is null.", __FILE__, __LINE__);
		}

		Enumerate ([&](const GS::UniString& key, const ValueRef& value)
		{
			processor (key, T::Cast (value));
		});
	}
	
	ObjectValue&	AddNull (const GS::UniString& name);
	ObjectValue&	Add (const GS::UniString& name, bool value);
	ObjectValue&	Add (const GS::UniString& name, Int8 value);
	ObjectValue&	Add (const GS::UniString& name, UInt8 value);
	ObjectValue&	Add (const GS::UniString& name, Int16 value);
	ObjectValue&	Add (const GS::UniString& name, UInt16 value);
	ObjectValue&	Add (const GS::UniString& name, Int32 value);
	ObjectValue&	Add (const GS::UniString& name, UInt32 value);
	ObjectValue&	Add (const GS::UniString& name, Int64 value);
	ObjectValue&	Add (const GS::UniString& name, UInt64 value);
	ObjectValue&	Add (const GS::UniString& name, double value);
	ObjectValue&	Add (const GS::UniString& name, const GS::UniString& value);
	ObjectValue&	Add (const GS::UniString& name, const char* value);
	ObjectValue&	AddValue (const GS::UniString& name, const ValueRef& value);

	bool			Remove (const GS::UniString& name);
	void			Remove (UIndex index);
	void			Clear ();

	static ObjectValueRef		Cast (const ValueRef& value);
	static const ObjectValue&	Cast (const Value& value);
	static ObjectValue&			Cast (Value& value);

	virtual void	Accept (ValueVisitor* visitor) override;
};

typedef ObjectValue::ObjectValueRef	ObjectValueRef;

}

#endif

