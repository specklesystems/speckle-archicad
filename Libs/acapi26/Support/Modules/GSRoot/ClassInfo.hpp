// *****************************************************************************
//
//                Classes ClassVersion, ClassType and ClassInfo
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef CLASSINFO_HPP
#define CLASSINFO_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSGuid.hpp"
#include "GSDebug.hpp"
#include "CustomProperty.hpp"
#include "StaticInstantiable.hpp"
#include "OnHeap.hpp"


// --------------------------------- Predefinitions ----------------------------

namespace GS {
class Object;
class ObjectState;
class IChannel;
class OChannel;
class XMLOChannel;
class XMLIChannel;
class Extension;
class ExtensionClass;
class ErrorStatus;
class String;
template <class Key, class Value> class HashTable;
}

// -------------------------------- Definitions --------------------------------

#define	DECLARE_ROOT_CLASS_INFO																	\
	private:																					\
		static	GS::ClassInfo			classInfo;												\
	public:																						\
		virtual const GS::ClassInfo*	GetClassInfo () const			{ return &classInfo; }	\
		static GS::ClassInfo*			GetClassInfoStatic ()			{ return &classInfo; }	\
	private:


#define	DECLARE_CLASS_INFO																		\
	private:																					\
		static	GS::ClassInfo			classInfo;												\
	public:																						\
		virtual const GS::ClassInfo*	GetClassInfo () const override	{ return &classInfo; }	\
		static GS::ClassInfo*			GetClassInfoStatic ()			{ return &classInfo; }	\
	private:


#define	DECLARE_DYNAMIC_CLASS_INFO(className)													\
	private:																					\
		static GS::ClassInfo			classInfo;												\
	public:																						\
		virtual const GS::ClassInfo*	GetClassInfo () const override	{ return &classInfo; }	\
		static GS::ClassInfo*			GetClassInfoStatic ()			{ return &classInfo; }	\
		using BaseClass = CurrentClass;															\
		using CurrentClass = className;															\
	private:																					\
		static GS::Object*				ConstructorFunction ()									\
		{																						\
			try {																				\
				return new className ();														\
			} catch (...) {																		\
				return nullptr;																	\
			}																					\
		}


#define	DECLARE_DYNAMIC_CLASS_INFO_ABSTRACT(className)										\
	private:																				\
		static GS::ClassInfo	classInfo;													\
	public:																					\
		virtual const GS::ClassInfo*	GetClassInfo (void) const override { return &classInfo; }	\
		static GS::ClassInfo*			GetClassInfoStatic (void) { return &classInfo; }			\
		using BaseClass = CurrentClass;														\
		using CurrentClass = className;														\
	private:


namespace GS {


template <class Class>
constexpr bool      IsClassInfoDeclared = IsSame<typename Class::CurrentClass, Class>;


// ============================ Class ClassVersion =============================


class GSROOT_DLL_EXPORT ClassVersion {
private:
	unsigned char	mainVersion;	// main version of the class
	unsigned char	subVersion;		// sub version of the class

public:
	inline ClassVersion ();
	inline ClassVersion (unsigned char mainVersion, unsigned char subVersion);

	inline void		Set (unsigned char newMainVersion, unsigned char newSubVersion);

	GS_FORCE_INLINE unsigned char	GetMainVersion (void) const;
	GS_FORCE_INLINE unsigned char	GetSubVersion  (void) const;

	inline bool		IsValid (void) const;
	inline bool		IsEmpty (void) const;

	inline bool		operator== (const ClassVersion& right) const;
	inline bool		operator!= (const ClassVersion& right) const;
	inline bool		operator<  (const ClassVersion& right) const;
	inline bool		operator<= (const ClassVersion& right) const;
	inline bool		operator>  (const ClassVersion& right) const;
	inline bool		operator>= (const ClassVersion& right) const;

	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Read  (IChannel& ic);

	GSErrCode	WriteXML (XMLOChannel& oc) const;
	GSErrCode	ReadXML  (XMLIChannel& ic);

	GSErrCode	Store   (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);
};

}	// namespace GS


inline GS::ClassVersion::ClassVersion ():
	mainVersion (0),
	subVersion  (0)
{
}


inline GS::ClassVersion::ClassVersion (unsigned char mainVersion, unsigned char subVersion):
	mainVersion (mainVersion),
	subVersion  (subVersion)
{
}


inline void		GS::ClassVersion::Set (unsigned char newMainVersion, unsigned char newSubVersion)
{
	mainVersion = newMainVersion;
	subVersion  = newSubVersion;
}


GS_FORCE_INLINE unsigned char	GS::ClassVersion::GetMainVersion (void) const
{
	return mainVersion;
}


GS_FORCE_INLINE unsigned char	GS::ClassVersion::GetSubVersion (void) const
{
	return subVersion;
}


inline bool		GS::ClassVersion::IsValid (void) const
{
	return (mainVersion != 0);
}


inline bool		GS::ClassVersion::IsEmpty (void) const
{
	return (mainVersion == 0 && subVersion == 0);
}


inline bool		GS::ClassVersion::operator== (const ClassVersion& rightOp) const
{
	return (mainVersion == rightOp.mainVersion && subVersion == rightOp.subVersion);
}


inline bool		GS::ClassVersion::operator!= (const ClassVersion& rightOp) const
{
	return (mainVersion != rightOp.mainVersion || subVersion != rightOp.subVersion);
}


inline bool		GS::ClassVersion::operator< (const ClassVersion& rightOp) const
{
	if (mainVersion < rightOp.mainVersion)
		return true;
	else if (mainVersion > rightOp.mainVersion)
		return false;
	else
		return (subVersion < rightOp.subVersion);
}


inline bool		GS::ClassVersion::operator<= (const ClassVersion& rightOp) const
{
	if (mainVersion < rightOp.mainVersion)
		return true;
	else if (mainVersion > rightOp.mainVersion)
		return false;
	else
		return (subVersion <= rightOp.subVersion);
}


inline bool		GS::ClassVersion::operator> (const ClassVersion& rightOp) const
{
	if (mainVersion > rightOp.mainVersion)
		return true;
	else if (mainVersion < rightOp.mainVersion)
		return false;
	else
		return (subVersion > rightOp.subVersion);
}


inline bool		GS::ClassVersion::operator>= (const ClassVersion& rightOp) const
{
	if (mainVersion > rightOp.mainVersion)
		return true;
	else if (mainVersion < rightOp.mainVersion)
		return false;
	else
		return (subVersion >= rightOp.subVersion);
}
// ____________________________ Class ClassVersion _____________________________



// ============================== Class ClassType ==============================

namespace GS {

class GSROOT_DLL_EXPORT ClassType {
private:
	ULong	highValue;		// higher 32 bits of the class type
	ULong	lowValue;		// lower 32 bits of the class type

public:
	inline ClassType ();
	explicit ClassType (const char* className);
	inline ClassType (ULong highValue, ULong lowValue);

	inline bool		operator== (const ClassType& rightOp) const;
	inline bool		operator!= (const ClassType& rightOp) const;

	inline ULong	GenerateHashValue (void) const;

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Write (OChannel& oc) const;

	GSErrCode	WriteXML (XMLOChannel& oc) const;
	GSErrCode	ReadXML  (XMLIChannel& ic);
};

}	// namespace GS



inline GS::ClassType::ClassType ():
	highValue (0),
	lowValue  (0)
{
}


inline GS::ClassType::ClassType (ULong hValue, ULong lValue):
	highValue (hValue),
	lowValue  (lValue)
{
}


inline bool		GS::ClassType::operator== (const ClassType& rightOp) const
{
	return (highValue == rightOp.highValue && lowValue == rightOp.lowValue);
}


inline bool		GS::ClassType::operator!= (const ClassType& rightOp) const
{
	return (highValue != rightOp.highValue || lowValue != rightOp.lowValue);
}


inline ULong	GS::ClassType::GenerateHashValue (void) const
{
	const ULong* ul = reinterpret_cast<const ULong*> (this);

	return (ul[0] * 65599 + ul[1]);
}


// ______________________________ Class ClassType ______________________________



// ============================== Class ExportedClassName ======================

namespace GS {

class GSROOT_DLL_EXPORT ExportedClassName {
private:
	const char* name;

public:
	explicit ExportedClassName (const char* name);

	operator const char* () const;
	const char*		Get () const;
};

}
// ______________________________ Class ExportedClassName ______________________



// ========================= Class CustomClassProperty =========================


namespace GS {


class CustomClassPropertyValue;

enum PropertyInheritance { InheritableProperty };

class GSROOT_DLL_EXPORT CustomClassProperty : public CustomProperty {
private:
	class ValueNames;

	Guid			guid;			// identifier of the custom property
	bool			isInheritable = false;	// determines whether is the property inheritable by derived classes

	CustomClassProperty (const CustomClassProperty& source);				// disabled
	CustomClassProperty&	operator= (const CustomClassProperty& source);	// disabled

	static	void	CreateCustomClassProperties (void);

public:
	CustomClassProperty (const Guid& guid, const char* name, UInt32 defaultValue);
	CustomClassProperty (const Guid& guid, const char* name, int defaultValue);		// because of literals
	CustomClassProperty (const Guid& guid, const char* name, const void* defaultValue);

	CustomClassProperty (const Guid& guid, const char* name, PropertyInheritance, UInt32 defaultValue);
	CustomClassProperty (const Guid& guid, const char* name, PropertyInheritance, int defaultValue);		// because of literals
	CustomClassProperty (const Guid& guid, const char* name, PropertyInheritance, const void* defaultValue);

   ~CustomClassProperty ();

	GS_FORCE_INLINE bool	IsInheritable (void) const;

	Guid	GetId (void) const;

	CustomClassPropertyValue	operator() (UInt32 value) const;
	CustomClassPropertyValue	operator() (const void* value) const;

	static void		EnumerateInstances (const std::function<void (const CustomClassProperty&)>& processor);
};


class GSROOT_DLL_EXPORT CustomClassPropertyValue : public CustomPropertyValue {
public:
	using	CustomPropertyValue::CustomPropertyValue;

	const CustomClassProperty&	GetCustomProperty (void) const;
};


class GSROOT_DLL_EXPORT CustomClassPropertyValueStatic : public  CustomClassPropertyValue, public StaticInstantiable {
public:
	CustomClassPropertyValueStatic ();
	explicit CustomClassPropertyValueStatic (const CustomClassProperty& customProperty);
	CustomClassPropertyValueStatic (const CustomClassProperty& customProperty, UInt32 value, const char* valueName = nullptr);
	CustomClassPropertyValueStatic (const CustomClassProperty& customProperty, int value, const char* valueName = nullptr);	// because of literals
	CustomClassPropertyValueStatic (const CustomClassProperty& customProperty, void* value, const char* valueName = nullptr);
	CustomClassPropertyValueStatic (const CustomClassProperty& customProperty, const CustomClassProperty::Value& value, const char* valueName = nullptr);
};


}	// namespace GS


GS_FORCE_INLINE bool	GS::CustomClassProperty::IsInheritable (void) const
{
	return isInheritable;
}


// =========================== Class ObjectDefaults ============================

namespace GS {

class GSROOT_DLL_EXPORT ObjectDefaults {
private:
	UInt64	objectDefaults;		// stores ODB::ObjectInfo flags that will be initialized to 1 at the object creation

public:
	inline ObjectDefaults (UInt64 objectDefaults = 0);

	inline	operator UInt64 (void) const;

	GSROOT_DLL_EXPORT friend ObjectDefaults		operator+ (const ObjectDefaults& leftOp, const ObjectDefaults& rightOp);
};

GSROOT_DLL_EXPORT ObjectDefaults		operator+ (const ObjectDefaults& leftOp, const ObjectDefaults& rightOp);

}	// namespace GS



inline GS::ObjectDefaults::ObjectDefaults (UInt64 objectDefaults):
	objectDefaults (objectDefaults)
{
}


inline	GS::ObjectDefaults::operator UInt64 (void) const
{
	return objectDefaults;
}
// ___________________________ Class ObjectDefaults ____________________________



// ============= Class CustomClassPropertyValueWithObjectDefaults ==============

namespace GS {

class GSROOT_DLL_EXPORT CustomClassPropertyValueWithObjectDefaults: public CustomClassPropertyValue {
private:
	ObjectDefaults	objectDefaults;		// stores properties of the object will be set at the object creation

public:
	CustomClassPropertyValueWithObjectDefaults (const CustomClassProperty& customClassProperty, UInt32 value, const ObjectDefaults& objectDefaults, const char* valueName = nullptr);

	ObjectDefaults	GetObjectDefaults (void) const;
};

}	// namespace GS
// _____________ Class CustomClassPropertyValueWithObjectDefaults ______________



// ============================ Class ClassProperty ============================

namespace GS {

class ClassInfo;
using ConstructorFPtr = Object* (*) ();


class GSROOT_DLL_EXPORT ConstructorObject {
public:
	virtual Object*	Create () const = 0;

	virtual ~ConstructorObject ();
};


class GSROOT_DLL_EXPORT ClassProperty {
private:
	ClassType					type;
	Guid						guid;
	ClassVersion				version;

	const ClassInfo*			baseClass = nullptr;

	const char*					exportedClassName = nullptr;

	ConstructorFPtr				constructorFPtr = nullptr;

	const ConstructorObject*	constructorObject = nullptr;

	ObjectDefaults				objectDefaults;

	enum { MaxCustomClassPropertyValueCount = 10 };
	const CustomClassPropertyValue*	customClassPropertyValues[MaxCustomClassPropertyValueCount];	// implemented with C array to avoid including of the GS::Array (because of the slow compile time)
	ULong							customClassPropertyValueCount = 0;

	enum { MaxCustomClassPropertyValueStaticCount = 10 };
	const CustomClassPropertyValueStatic*	customClassPropertyValueStatics[MaxCustomClassPropertyValueStaticCount];	// implemented with C array to avoid including of the GS::Array (because of the slow compile time)
	ULong									customClassPropertyValueStaticCount = 0;

	friend class ClassInfo;
	class CustomPropertyValue;

public:
	ClassProperty ();
	ClassProperty (ClassType type);
	ClassProperty (const Guid& guid);
	ClassProperty (ClassVersion version);
	ClassProperty (const ClassInfo* baseClass);
	ClassProperty (const ExportedClassName& exportedClassName);
	ClassProperty (ConstructorFPtr constructor);
	ClassProperty (const ConstructorObject& constructor);
	ClassProperty (const CustomClassPropertyValue& customClassPropertyValue);
	ClassProperty (const CustomClassPropertyValueStatic& customClassPropertyValueStatic);
	ClassProperty (const CustomClassPropertyValueWithObjectDefaults& customClassPropertyValueWithObjectDefaults);

	GSROOT_DLL_EXPORT friend ClassProperty	operator+ (const ClassProperty& leftOp, const ClassProperty& rightOp);
};

GSROOT_DLL_EXPORT ClassProperty	operator+ (const ClassProperty& leftOp, const ClassProperty& rightOp);

GSROOT_DLL_EXPORT ClassProperty	AddProperties (std::initializer_list<ClassProperty> properties);

}	// namespace GS
// ____________________________ Class ClassProperty ____________________________



// ======================== Class ExternalClassProperty ========================

namespace GS {

class GSROOT_DLL_EXPORT ExternalClassProperty {
public:
	ExternalClassProperty (ClassInfo* targetClassInfo, const CustomClassPropertyValue& customClassPropertyValue);
};	

}	// namespace GS


#define CONCATENATE_LINE_NUMBER2(name,lineNumber) name##lineNumber
#define CONCATENATE_LINE_NUMBER(name,lineNumber) CONCATENATE_LINE_NUMBER2(name,lineNumber)

#define EXTERNAL_CLASS_PROPERTY(Class, customClassPropertyValue)	\
	static GS::ExternalClassProperty CONCATENATE_LINE_NUMBER (externalClassProperty, __LINE__) (Class::GetClassInfoStatic (), customClassPropertyValue);

// ________________________ Class ExternalClassProperty ________________________



// ============================== Class ClassInfo ==============================

namespace GS {

class GSROOT_DLL_EXPORT ClassInfo: public StaticInstantiable {
private:
	class UnprocessedCustomProperties;

	using Extensions		= HashTable<const ExtensionClass*, Extension*>;
	using CustomProperties	= HashTable<const GS::CustomClassProperty*, CustomClassProperty::Value>;

	ClassInfo*					currentClassInfo	= nullptr;	// the newest version of this class
	OnHeap<String>				name;							// class name
	OnHeap<String>				exportedName;					// exported class name
	ClassType					type;							// class type (specified by the user or generated from the name)
	Guid						guid;							// class guid
	UInt64						flags				= 0;		// custom flags for derived classes
	ClassVersion				version;						// current version of the class
	ClassVersion				oldVersion;						// an old version of the class -> used at object serialization
	const ClassInfo*			baseClass			= nullptr;	// base class of this class
	ConstructorFPtr				constructorFPtr		= nullptr;	// points to the "constructor" function of the class (if it isn't nullptr)
	const ConstructorObject*	constructorObject	= nullptr;	// points to the "constructor" object of the class (if it isn't nullptr)
	ObjectDefaults				objectDefaults;					// stores properties of the object will be set at the object creation
	OnHeap<CustomProperties>	customProperties;				// custom class property values indexed by their property types
	OnHeap<Extensions>			extensions;						// extensions of the class

	ClassInfo (ClassInfo* currentClassInfo, const char* className, const ClassProperty& property);

	ClassInfo (const ClassInfo& source);				// disabled
	ClassInfo&	operator= (const ClassInfo& source);	// disabled

	void	ProcessCustomProperties (void) const;

protected:
	ClassInfo (ConstructorFPtr constructorFPtr);
	ClassInfo (const GS::ObjectState& os, ConstructorFPtr constructorFPtr, GS::ErrorStatus& status);

	inline void		AddFlag (UInt64 flag);

	void	SetBaseClass (const ClassInfo* baseClass);

public:
	ClassInfo ();

	template<typename... Properties>
	explicit ClassInfo (const char* className, const Properties&... properties);

	template<typename... Properties>
	explicit ClassInfo (ClassInfo& currentClassInfo, const char* className, const Properties&... properties);

	virtual ~ClassInfo ();

		// Types

	class CustomPropertyValueEnumerator;

		// Name, type, id, flags

	const char*				GetName	(void) const;
	const char*				GetExportedName (void) const;
	inline ClassType		GetType	(void) const;
	inline const Guid&		GetId	(void) const;
	inline bool				HasId	(void) const;
	inline bool				HasFlag (UInt64 flag) const;

		// version

	enum SystemVersion { Current, Old };

	inline ClassVersion		GetVersion	  (void) const;
	inline ClassVersion		GetVersion	  (SystemVersion systemVersion) const;
	inline ClassVersion		GetOldVersion (void) const;
	void					SetOldVersion (ClassVersion oldVersion);
	
	virtual GSErrCode		RestoreOldVersion	(const GS::ObjectState& os);
	static  GSErrCode		RestoreOldVersion	(const GS::ObjectState& os, ClassVersion* version);
	virtual GSErrCode		StoreCurrentVersion (GS::ObjectState& os) const;

	inline GS::ClassInfo*	GetCurrentClassInfo (void) const;

		// base class

	inline const ClassInfo*	GetBaseClass (void) const;
	inline bool				HasBaseClass (void) const;
	bool					IsCompatibleWith (const ClassInfo* classInfo) const;

		// constructor

	bool					HasConstructor	  (void) const;
	Object*					CreateNewInstance (void) const;

	inline ObjectDefaults	GetObjectDefaults (void) const;

		// custom properties

	CustomClassPropertyValue	GetCustomPropertyValue (const CustomClassProperty& customProperty) const;
	bool		HasCustomPropertyValue			 (const CustomClassPropertyValue& customPropertyValue) const;
	bool		HasDefaultCustomPropertyValue	 (const CustomClassProperty& customProperty) const;
	bool		HasNonDefaultCustomPropertyValue (const CustomClassProperty& customProperty) const;
	bool		EnumerateCustomPropertyValues	 (CustomPropertyValueEnumerator* enumerator) const;

	void		AddCustomPropertyValue (const CustomClassPropertyValue& customClassPropertyValue);

		// extensions

	void		RegisterExtension	(Extension* extension);
	void		UnregisterExtension (Extension* extension);
	Extension*	GetExtension		(const ExtensionClass* extensionClass) const;
	bool		HasExtension		(const ExtensionClass* extensionClass) const;

	template <class E>
	inline E*	GetExtension (void) const;

	template <class E>
	inline bool	HasExtension (void) const;

		// IO

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

		// Types

	class GSROOT_DLL_EXPORT CustomPropertyValueEnumerator {
	public:
		virtual ~CustomPropertyValueEnumerator ();

		virtual bool	CustomPropertyValueFound (const CustomClassPropertyValue& /*customPropertyValue*/) { return true; }
	};
};

}	// namespace GS


template<typename... Properties>
GS::ClassInfo::ClassInfo (const char* className, const Properties&... properties) : 
	ClassInfo (nullptr, className, AddProperties ({ properties... }))
{
}


template<typename... Properties>
GS::ClassInfo::ClassInfo (ClassInfo& currentClassInfo, const char* className, const Properties&... properties) : 
	ClassInfo (&currentClassInfo, className, AddProperties ({ properties... }))
{
}


inline GS::ClassType	GS::ClassInfo::GetType (void) const
{
	return type;
}


inline const GS::Guid&	GS::ClassInfo::GetId (void) const
{
	return guid;
}


inline bool		GS::ClassInfo::HasId (void) const
{
	return !guid.IsNull ();
}


inline void		GS::ClassInfo::AddFlag (UInt64 flag)
{
	flags |= flag;
}


inline bool		GS::ClassInfo::HasFlag (UInt64 flag) const
{
	return ((flags & flag) != 0);
}


inline GS::ClassVersion		GS::ClassInfo::GetVersion (void) const
{
	return version;
}


inline GS::ClassVersion		GS::ClassInfo::GetVersion (SystemVersion systemVersion) const
{
	if (systemVersion == Current)
		return version;
	else
		return oldVersion;
}


inline GS::ClassVersion		GS::ClassInfo::GetOldVersion (void) const
{
	return oldVersion;
}


inline const GS::ClassInfo*		GS::ClassInfo::GetBaseClass (void) const
{
	return baseClass;
}


inline bool		GS::ClassInfo::HasBaseClass (void) const
{
	return (baseClass != nullptr);
}


inline GS::ClassInfo*	GS::ClassInfo::GetCurrentClassInfo (void) const
{
	return currentClassInfo;
}


inline GS::ObjectDefaults	GS::ClassInfo::GetObjectDefaults (void) const
{
	return objectDefaults;
}


template <class E>
inline E*	GS::ClassInfo::GetExtension (void) const
{
	return static_cast<E*> (GetExtension (&E::extensionClass));
}


template <class E>
inline bool		GS::ClassInfo::HasExtension (void) const
{
	return HasExtension (&E::extensionClass);
}
// ______________________________ Class ClassInfo ______________________________


#endif
