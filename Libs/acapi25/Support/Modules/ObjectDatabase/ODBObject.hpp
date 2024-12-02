
// *****************************************************************************
//
//                                 Class Object
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBOBJECT_HPP
#define ODBOBJECT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBReference.hpp"
#include "ODBQuery.hpp"
#include "ODBAssociationProperty.hpp"

#include "EventObserver.hpp"

#include <functional>


namespace ODB { class Association; }
namespace ODB { class Database; }
namespace ODB { class SharedAssociation11Untyped; }
namespace ODB { class ConversionData; }
namespace ODB { template <class LeftClass, class RightClass, class AssociationClass = void> class AssociationNN; }
namespace ODB { template <class LeftClass, class RightClass> class RightOrderedAssociationNN; }

namespace GS { class XMLOChannel; }
namespace GS { class XMLIChannel; }


// =============================== Class Object ================================

namespace ODB {

class ODB_DLL_EXPORT Object: public GS::Object {
	DECLARE_CLASS_INFO

public:
	using BaseClass = CurrentClass;
	using CurrentClass = Object;

	class ODB_DLL_EXPORT Modification {
	public:
		virtual ~Modification ();
	};

private:
	GSErrCode	WriteOwnIsolatedState1 (GS::OChannel& oc) const;
	GSErrCode	ReadOwnIsolatedState1  (GS::IChannel& ic);

	GSErrCode	WriteOwnIsolatedState2 (GS::OChannel& oc) const;
	GSErrCode	ReadOwnIsolatedState2  (GS::IChannel& ic);

	GSErrCode	WriteOwnIsolatedState3 (GS::OChannel& oc) const;
	GSErrCode	ReadOwnIsolatedState3  (GS::IChannel& ic);

	void		IsolateAndDeletePartObjects ();

protected:
	const Ref<Object> thisRef;	// reference of the object itself (it is const to avoid accidental modifications)

			 Object ();
	explicit Object (const GS::ClassInfo* finalClassInfo);
	explicit Object (const Ref<Object>& thisRef);
			 Object (const GS::ClassInfo* finalClassInfo, const Ref<Object>& thisRef);

	virtual GSErrCode	WriteContentForIdGeneration (GS::OChannel& oc) const;

		// Conversion support

	GSErrCode				AttachConversionData (ConversionData* conversionData);
	ConversionData*			GetConversionData	 (const GS::ClassInfo* conversionDataType);
	const ConversionData*	GetConversionData	 (const GS::ClassInfo* conversionDataType) const;
	bool					HasConversionData	 (const GS::ClassInfo* conversionDataType) const;

	template <class DataType>
	DataType*				GetConversionData ();

	template <class DataType>
	const DataType*			GetConversionData () const;

	template <class DataType>
	bool					HasConversionData () const;

	template <class DataType>
	DataType*				RetrieveConversionData ();

		// Association events

	template <class LeftClass, class RightClass> friend class Association11;
	template <class LeftClass, class RightClass> friend class SharedAssociation11;
	template <class LeftClass, class RightClass> friend class Association1N;
	template <class LeftClass, class RightClass> friend class OrderedAssociation1N;
	template <class LeftClass, class RightClass, class AssociationClass> friend class AssociationNN;
	template <class LeftClass, class RightClass> friend class RightOrderedAssociationNN;

	virtual void	ObjectConnected    (const Ref<Object>& thisRef, const Association& association, const Ref<Object>& connectedObject) const;
	virtual void	ObjectDisconnected (const Ref<Object>& thisRef, const Association& association, const Ref<Object>& disconnectedObject) const;
	virtual void	ObjectDeleted      (const Ref<Object>& thisRef, const Association& association, const Ref<Object>& deletedObject) const;
	virtual void	ObjectModified     (const Ref<Object>& thisRef, const Association& association, const Ref<Object>& modifiedObject, ULong hint, const Modification* modification) const;
	virtual void	ObjectReordered    (const Ref<Object>& thisRef, const Association& association, const Ref<Object>& reorderedObject) const;

	void	SizeChanged ();

	void	SignalChange (ULong hint = 0, const Modification* modification = nullptr);

	friend class ODB::CommonRefUntyped;	// to access InitializeLazyData methods

	bool	HasLazyDataToBeInitialized	() const;
	void	SetLazyDataInitialization	();
	void	ClearLazyDataInitialization	();

	virtual void	InitializeLazyData () const;

	GSErrCode	ReadIsolatedState  (GS::IChannel& ic, const GS::InputFrame& frame);

public:
		// types

	class IsolatedState;
	class IsolatedStateIO;
	class OwnerUserObserver;
	class OwnerUserEventSource;

		// constructors, destructor, assignment

	Object (const Object& source);
	Object&		operator= (const Object& source);
   ~Object ();

	static void		DeleteFromMemory	   (Ref<Object> object);
	static void		DeleteIsolatedExternal (Ref<Object> object);

	bool			IsDeletingFromMemory () const;

		// this reference management

	inline const Ref<Object>&		GetRef ();			// returning const reference pointing into the object isn't nice but is faster than returning Ref by value (because of construction and destruction of the temporary object)
	inline const ConstRef<Object>&	GetRef () const;	// returning const reference pointing into the object isn't nice but is faster than returning ConstRef by value (because of construction and destruction of the temporary object)

	void	InitRef (const Ref<Object>& newRef);			// thisRef initialization of newly created isolated objects without id and links
	void	SetRef  (const Ref<Object>& newRef);			// thisRef setting of non-database objects possibly having id and links

		// user ownership management

	static short	GetOwnerUser (const ConstRef<Object>& object);
	static bool		HasOwnerUser (const ConstRef<Object>& object);
	static void		SetOwnerUser (const Ref<Object>& object, short ownerUser);
	static void		SetIsolatedOwnerUser (const Ref<Object>& object, short ownerUser);
	static void		ClearIsolatedOwnerUser (const Ref<Object>& object);

	static void		AttachOwnerUserObserver (OwnerUserObserver& observer);
	static void		DetachOwnerUserObserver (OwnerUserObserver& observer);

	DECLARE_EXTERNAL_ATTRIBUTE_EQUALITY_QUERY (ODB_DLL_EXPORT, OwnerUser, ODB::Object, short, GetOwnerUser)

		// I/O

	enum ObjectSharing {
		NotShared	= 0,	// object is not shared
		FirstShared = 1,	// first occurrence of a shared object
		NextShared	= 2		// next occurrence of a shared object
	};

	static GS::SerializationContext::Flag	SkipManagementDataForDatabaseObjectsAtWrite;	// skip id and stamps during writing for database objects
	static GS::SerializationContext::Flag	SkipManagementDataAtWrite;						// skip id and stamps during writing
	static GS::SerializationContext::Flag	SetStampsAtRead;								// always set modification and creation stamps (even if the object already has identity)

	virtual	GSErrCode	Write (GS::OChannel& oc) const override;
	virtual	GSErrCode	Read  (GS::IChannel& ic) override;

	virtual	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
	virtual	GSErrCode	ReadXML  (GS::XMLIChannel& ic);

	GSErrCode	WriteCompositeState (GS::OChannel& oc) const;
	GSErrCode	ReadCompositeState  (GS::IChannel& ic);
	GSErrCode	ReadCompositeState (GS::IChannel& ic, ObjectSharing* objectSharing);

	GS::ErrorStatus  Store (GS::ObjectState& os) const override;
	GS::ErrorStatus  Restore (const GS::ObjectState& os) override;

	static void	OpenSharedWriteBlock  ();
	static void	CloseSharedWriteBlock ();

		// isolated state management

	virtual	IsolatedState*	CreateIsolatedState  () const;
	virtual	GSErrCode		StoreIsolatedState   (IsolatedState* isolatedState) const;
	virtual	GSErrCode		RestoreIsolatedState (const IsolatedState* isolatedState);

	virtual	GSErrCode		WriteIsolatedState (GS::OChannel& oc) const;
	virtual	GSErrCode		ReadIsolatedState  (GS::IChannel& ic);

	virtual	GSErrCode		WriteIsolatedStateXML (GS::XMLOChannel& oc) const;
	virtual	GSErrCode		ReadIsolatedStateXML  (GS::XMLIChannel& ic);

	virtual	GSErrCode		CopyIsolatedState (const Object& source);
	GSErrCode				CopyIsolatedStateWithStoreRestore (const Object& source);
	GSErrCode				CopyIsolatedStateWithWriteRead	  (const Object& source, IsolatedStateIO* isolatedStateIO = nullptr);

	virtual USize			GetIsolatedSize () const;

	virtual void			Isolate    ();
	static void				IsolateAssociationLinks (const Ref<Object>& object);
	void					IsolateAll ();

	static Object*			CreateIsolatedObject (const GS::ClassInfo* classInfo);
	static Object*			CreateIsolatedObject (const GS::Guid& classId);
	static Object*			CreateIsolatedObject (GS::ClassType classType);

		// Types

	class ODB_DLL_EXPORT IsolatedState {
	private:
		friend class ODB::Object;

		Ref<Object>	thisRef;
		UChar		persistentFlags;
		short		ownerUser;

	public:
		virtual ~IsolatedState ();
	};

	class ODB_DLL_EXPORT IsolatedStateIO {
	public:
		virtual	GSErrCode	WriteIsolatedState (const ConstRef<Object>& object, GS::OChannel& oc) const;
		virtual	GSErrCode	ReadIsolatedState  (const Ref<Object>& object, GS::IChannel& ic);
	};

	class ODB_DLL_EXPORT OwnerUserObserver: public GS::EventObserver {
	protected:
		friend class OwnerUserEventSource;	// to allow access to event sending methods

		virtual void	OwnerUserChanged (const ConstRef<Object>& object);
	};

	class ConstMethods {};

	// Module private methods

#ifdef ODB_MODULE_PRIVATE

	enum DatabaseObjectSelector { AllowDatabaseObject };

	static void		DeleteFromMemory (Ref<Object> object, DatabaseObjectSelector);

#endif

	virtual Id		GenerateIdFromContent () const;
};


ODB_DLL_EXPORT extern Object::IsolatedStateIO	defaultIsolatedStateIO;		// this object implements default isolated state IO


ODB_DLL_EXPORT extern const GS::CustomClassProperty		Pinning;	// controls whether will be instances of the class automatically pinned at the object creation

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue					NotPinned;	// instances of the class will not be automatically pinned at the object creation
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	Pinned;		// instances of the class will be automatically pinned at the object creation


ODB_DLL_EXPORT extern const GS::CustomClassProperty		OwnershipTermination;	// indicates whether can the class have part objects

ODB_DLL_EXPORT extern const GS::CustomClassProperty		ObjectIdentification;	// type controlling object identification

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue				   IndependentIdentification;		// independent (random generated) object identification is used
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults ContentDependentIdentification;	// identifier is generated from object's content
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue				   ContextDependentIdentification;	// identifier is generated from object's context


ODB_DLL_EXPORT extern const GS::CustomClassProperty		IdentificationContextDefinition;		// describes the way object identification context is defined

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	PureAssociationContextDefinition;	// context is defined only with associations
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	MixedContextDefinition;				// context is defined both with associations and other types of references


ODB_DLL_EXPORT extern const GS::CustomClassProperty ContentIdentificationScopeDefinition;		// describes whether the class defines identification scope

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	NotContentIdentificationScope;		// class doesn't define identification scope
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	DefinesContentIdentificationScope;	// class defines identification scope


ODB_DLL_EXPORT extern const GS::CustomClassProperty ContentIdentificationScopeType;			// describes the class that defines content identification scope for the class using this property


ODB_DLL_EXPORT extern const GS::CustomClassProperty		UserOwnershipModel;			// user ownership model

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	SingleUserOwnership;	// objects can be owned by a single user
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	SharedUserOwnership;	// objects are owned by all users


ODB_DLL_EXPORT extern const GS::CustomClassProperty		ObjectEmbedding;	// describes whether can be object of the class embedded into an another class

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	ObjectEmbeddingIsDisabled;		// object embedding is disabled
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue	ObjectEmbeddingIsEnabled;		// object embedding is enabled


ODB_DLL_EXPORT extern const GS::CustomClassProperty     ClassDerivation;	// describes whether is class core or derived

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue                     CoreClass;		// class has core data that can't be computed from other classes or data
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults   DerivedClass;	// class can be computed (derived) from other classes or data


ODB_DLL_EXPORT extern const GS::CustomClassProperty		DataLayer;	// data layer the class belongs to

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue					DataLayer0;		// layer 0
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer1;		// layer 1
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer2;		// layer 2
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer3;		// layer 3
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer4;		// layer 4
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer5;		// layer 5
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer6;		// layer 6
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults	DataLayer7;		// layer 7


ODB_DLL_EXPORT extern const GS::CustomClassProperty     DataLayerDetermination;		// defines the way data layer of the object is determined

ODB_DLL_EXPORT extern const GS::CustomClassPropertyValue                     UseOwnDataLayer;				// object will use own data layer field
ODB_DLL_EXPORT extern const GS::CustomClassPropertyValueWithObjectDefaults   DetermineDataLayerByOwner;		// data layer of the object is determined by owner object's data layer (this is done on demand at first time)


const UInt32 DataLayerCount = 8;


inline const GS::ClassInfo*		GetClassInfo (const CommonRefUntyped& object)
{
	const GS::ClassInfo* classInfo = object.GetClassInfo ();			// querying from ODB::ObjectInfo

	if (classInfo == nullptr && object.IsAvailable ())
		classInfo = object.GetConstMemoryAddress ()->GetClassInfo ();	// querying from GS::Object

	return classInfo;
}


template <class E>
inline E*	GetExtension (const CommonRefUntyped& object)
{
	const GS::ClassInfo* classInfo = object.GetClassInfo ();			// querying from ODB::ObjectInfo

	if (classInfo == nullptr && object.IsAvailable ())
		classInfo = object.GetConstMemoryAddress ()->GetClassInfo ();	// querying from GS::Object

	return classInfo->GetExtension<E> ();
}


class ODB_DLL_EXPORT ObjectFilter {
public:
	virtual ~ObjectFilter ();

	virtual bool	Filter (const ConstRef<Object>& object);
};


class ODB_DLL_EXPORT ExternalObjectFilter: public ObjectFilter {
public:
	virtual bool	Filter (const ConstRef<Object>& object) override;
};

ODB_DLL_EXPORT extern ExternalObjectFilter	externalObjectFilter;


class ODB_DLL_EXPORT InternalObjectFilter: public ObjectFilter {
public:
	virtual bool	Filter (const ConstRef<Object>& object) override;
};

ODB_DLL_EXPORT extern InternalObjectFilter	internalObjectFilter;


class ODB_DLL_EXPORT TypeQuery: public Query {
protected:
	const GS::ClassInfo* type;	// type to be queried

	explicit TypeQuery (const GS::ClassInfo* type);
public:
    virtual ~TypeQuery ();

	const GS::ClassInfo*	GetType () const;
};


class TypeNonCompatibilityQuery;

class ODB_DLL_EXPORT TypeCompatibilityQuery: public TypeQuery {
	DECLARE_CLASS_INFO

public:
	TypeCompatibilityQuery (const GS::ClassInfo* type);

	virtual	TypeCompatibilityQuery*	Clone () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	TypeNonCompatibilityQuery	operator! () const;
};


class ODB_DLL_EXPORT TypeNonCompatibilityQuery: public TypeQuery {
	DECLARE_CLASS_INFO

public:
	TypeNonCompatibilityQuery (const GS::ClassInfo* type);

	virtual	TypeNonCompatibilityQuery*	Clone () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	TypeCompatibilityQuery	operator! () const;
};


class ODB_DLL_EXPORT OrderedTypeCompatibilityQuery: public TypeQuery {
	DECLARE_CLASS_INFO

public:
	OrderedTypeCompatibilityQuery (const GS::ClassInfo* type);

	virtual	OrderedTypeCompatibilityQuery*	Clone () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;
};


class ODB_DLL_EXPORT TypeCompatibilityQueryCreator {
public:
	TypeCompatibilityQuery		operator== (const GS::ClassInfo* type) const;
	TypeNonCompatibilityQuery	operator!= (const GS::ClassInfo* type) const;
};

ODB_DLL_EXPORT extern const TypeCompatibilityQueryCreator Type;

inline TypeCompatibilityQuery	TypeIs (const GS::ClassInfo* type)
{
	return TypeCompatibilityQuery (type);
}


template <class Type>
inline TypeCompatibilityQuery	TypeIs ()
{
	return TypeCompatibilityQuery (Type::GetClassInfoStatic ());
}


inline TypeNonCompatibilityQuery	TypeIsNot (const GS::ClassInfo* type)
{
	return TypeNonCompatibilityQuery (type);
}


template <class Type>
inline TypeNonCompatibilityQuery	TypeIsNot ()
{
	return TypeNonCompatibilityQuery (Type::GetClassInfoStatic ());
}


struct ObjectLog;

struct ClassIdAssertSubject;

ODB_DLL_EXPORT GS::String	LogAssertSubject (GS::FastLogger::LogComposer& logComposer, const ClassIdAssertSubject& subject);

}	// namespace ODB


inline const ODB::Ref<ODB::Object>&		ODB::Object::GetRef ()
{
	return thisRef;
}


inline const ODB::ConstRef<ODB::Object>&	ODB::Object::GetRef () const
{
	// The following code works because Ref and ConstRef have the same layout and
	// implementation and differ only in the constness of methods
	// Returning const reference pointing into the object isn't nice but is faster than
	// returning ConstRef by value (because of construction and destruction of the temporary object)
	// If this hack fails then the correct solution should be used (that is returning ConstRef by value: return thisRef;)

	return *reinterpret_cast<const ConstRef<Object>*> (&thisRef);
}


template <class DataType>
DataType*	ODB::Object::GetConversionData ()
{
	return static_cast<DataType*> (GetConversionData (DataType::GetClassInfoStatic ()));
}


template <class DataType>
const DataType*		ODB::Object::GetConversionData () const
{
	return static_cast<const DataType*> (GetConversionData (DataType::GetClassInfoStatic ()));
}


template <class DataType>
bool	ODB::Object::HasConversionData () const
{
	return HasConversionData (DataType::GetClassInfoStatic ());
}


template <class DataType>
DataType*	ODB::Object::RetrieveConversionData ()
{
	DataType* conversionData = GetConversionData<DataType> ();
	if (conversionData == nullptr) {
		conversionData = new DataType ();
		if (AttachConversionData (conversionData) != NoError) {
			delete conversionData;
			conversionData = nullptr;
		}
	}

	return conversionData;
}


struct ODB::ObjectLog {
	const char* className;
	char		id[64];
	const char* idSpace;
	const char* database;
	char		flags[1024];
	UInt32		accessLevel;
	char		connections[1024];

	explicit ObjectLog (const ConstRef<Object>& object);
};


struct ODB::ClassIdAssertSubject {
	GS::Guid classId;

	ClassIdAssertSubject (const GS::Guid& classId): classId (classId) {}
};
// _______________________________ Class Object ________________________________

#endif
