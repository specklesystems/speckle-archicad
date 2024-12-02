// *****************************************************************************
//
//                              Class FieldType
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// *****************************************************************************


#ifndef ODBFIELDTYPE_HPP
#define ODBFIELDTYPE_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"
#include "GSGuid.hpp"
#include "String.hpp"
#include "StaticInstantiable.hpp"

#include <functional>

namespace GS	{ class TypeIndex; }
namespace GS	{ class ObjectState; }
namespace ODB	{ class DynamicObject; }
namespace GS	{ class RandomGenerator; }


// ============================== Class FieldType ==============================

namespace ODB {

using GetFunction = std::function<void (const DynamicObject&)>;

class ODB_DLL_EXPORT FieldType : public GS::StaticInstantiable {
public:
	class ODB_DLL_EXPORT Names {
	private:
		GS::String	name;				// example: GS::UInt16
		GS::String	shortName;			// example: UInt16    <- optional, if it is empty then name is used instead
		GS::String	fundamentalName;	// example: unsigned short (type without typedefs)  <- optional, if it is empty then name is used instead

	public:
		Names () = default;
		Names (const char* name, const char* shortName = nullptr, const char* fundamentalName = nullptr);

		const GS::String&	GetName () const;
		const GS::String&	GetShortName () const;
		const GS::String&	GetFundamentalName () const;
	};

	struct NatVisTypeInfo {
		ULong		id;
		GS::String	fullQualifiedName;
		bool		isBasic;
	};

private:
	GS::Guid		id;
	Names			names;
	NatVisTypeInfo	natVisInfo;

protected:
	template <class Type>
	static void		GetValueImp (const DynamicObject& object, const GetFunction& getFunction, const std::function<void (const char*)>& processor);

public:
	virtual ~FieldType ();

	virtual UInt32	GetSize () const = 0;
	virtual UInt32	GetAlignment () const;

	virtual void	Construct		  (char* target) const = 0;
	virtual void	ConstructWithCopy (char* target, const char* sourceField) const = 0;
	virtual void	ConstructWithMove (char* target, char* sourceField) const = 0;

	virtual void	AssignWithCopy (char* targetField, const char* sourceField) const = 0;
	virtual void	AssignWithMove (char* targetField, char* sourceField) const = 0;

	virtual void	Destroy (char* field) const = 0;

	virtual void	GetValue (const DynamicObject& object, const GetFunction& getFunction, const std::function<void (const char*)>& processor) const = 0;

	GS::Guid		GetId () const;
	void			SetId (const GS::Guid& id);


	void			  SetNames (const Names& names);

	const GS::String&	GetName () const;
	const GS::String&	GetShortName () const;
	const GS::String&	GetFundamentalName () const;

	virtual GS::String	GetCompilerGeneratedName () const;

	virtual GSErrCode	Read  (char* field, GS::IChannel& ic) const = 0;
	virtual GSErrCode	Write (const char* field, GS::OChannel& oc) const = 0;

		// ObjectState storage

	virtual GSErrCode	Store	(const GS::String& fieldName, const char* field, GS::ObjectState& os) const;
	virtual GSErrCode	Restore	(const GS::String& fieldName, char* field, const GS::ObjectState& os) const;

		// compare

	virtual bool	ImplementsEquality () const;
	virtual bool	IsEqual			 (const char* field1, const char* field2) const;	// base method
	bool			IsNotEqual		 (const char* field1, const char* field2) const;	// derived from IsEqual

	virtual bool	ImplementsOrdering () const;
	virtual bool	IsLess			 (const char* field1, const char* field2) const;	// base method
	bool			IsLessOrEqual	 (const char* field1, const char* field2) const;	// derived from IsLess
	bool			IsGreater		 (const char* field1, const char* field2) const;	// derived from IsLess
	bool			IsGreaterOrEqual (const char* field1, const char* field2) const;	// derived from IsLess

		// conversion

	virtual bool		ImplementsToText () const;
	virtual GS::String	ToText (const char* field) const;

	virtual bool		ImplementsFromText () const;
	virtual GSErrCode	FromText (const GS::String& text, char* field) const;

		// debug and test

	void				SetNatVisTypeInfo (const GS::String& typeName, const GS::String& modulName, bool isBasic);
	NatVisTypeInfo		GetNatVisTypeInfo () const;

	virtual void	Assign (char* field, GS::RandomGenerator& randomGenerator) const;
};


// ============================== class FieldType ==============================


template <class Type>
void	FieldType::GetValueImp (const DynamicObject& object, const GetFunction& getFunction, const std::function<void (const char*)>& processor)
{
	Type result = reinterpret_cast<const std::function<Type (const DynamicObject&)>&> (getFunction) (object);

	processor (reinterpret_cast<const char*> (&result));
}


ODB_DLL_EXPORT FieldType*		RegisterFieldType (FieldType* fieldType, const GS::TypeIndex& fieldTypeId);

template <typename Type>
class FieldTypeFactory {
public:
	static const FieldType&		Get ();
};


template <typename Type>
const FieldType&	GetFieldType ()               // should return function static FieldType instance for the given Type
{
	return 	FieldTypeFactory<Type>::Get ();
}


template <typename Type>
const FieldType&	CallGetFieldType ()
{
	return GetFieldType<Type> ();
}


template <typename Type>
bool	IsFieldType (const FieldType* fieldType)
{
	return &GetFieldType<Type> () == fieldType;
}


ODB_DLL_EXPORT void		TypeMismatchError ();


template <typename Type>
void	CheckFieldType (const FieldType* fieldType)
{
	if (!IsFieldType<Type> (fieldType))
		TypeMismatchError ();
}

}	// namespace ODB


#endif
