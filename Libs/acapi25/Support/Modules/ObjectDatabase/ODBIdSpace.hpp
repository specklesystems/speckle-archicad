
// *****************************************************************************
//
//                                 Class IdSpace
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBIDSPACE_HPP
#define ODBIDSPACE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBObject.hpp"
#include "Owner.hpp"

#include "String.hpp"
#include "ThreadSpecificStorage.hpp"
#include "EventSource.hpp"
#include "EventSender.hpp"

namespace ODB { class IsolatedStateIO; }
namespace ODB { template <class Type> class RefList; }
namespace ODB { template <class Type> class ConstRefList; }
namespace ODB { class ObjectLoader; }
namespace ODB { class ObjectSetSource; }
namespace GS  { template <class IndexType, class ItemType> class HashTable; }


// =============================== Class IdSpace ===============================

namespace ODB {

class ODB_DLL_EXPORT IdSpace: public GS::EventSource {
public:
	class ODB_DLL_EXPORT ObjectRefEnumerator: public GS::ConversionEnumerator<Ref<Object>> {
	public:
		virtual void	Enumerate (const std::function<void (const Ref<Object>&)>& processor) const override;
	};

	class ODB_DLL_EXPORT ConstObjectRefEnumerator: public GS::ConversionEnumerator<ConstRef<Object>> {
	public:
		virtual void	Enumerate (const std::function<void (const ConstRef<Object>&)>& processor) const override;
	};

	class ObjectObserver;
	class ObjectRegister;

private:
	class Databases;
	class LoaderTable;
	class ReidentificationTable;
	friend class ObjectSetView;

	GS::String					name;					// name of the identifier space
	mtaccess ObjectRegister*	objectRegister;			// object register of the identifier space
	Databases&					databases;				// stores databases belonging to the identifier space
	LoaderTable&				loaderTable;			// stores object loaders
	ReidentificationTable*		reidentificationTable;	// id -> id mapping table used for the reidentification of external and unknown objects

	GS::ArrayFB<ObjectObserver*, 1>	objectObservers;	// stores object observers, array is used instead of EventSource because of performance

	UInt32						loadObjectCallCount;	// for testing
	UInt32						loadLinksCallCount;		// fro testing

	static GS::ThreadSpecificStorage<IdSpace*> inputIdSpace;	// input identifier space of the actual thread;

	IdSpace (Owner<ObjectSetSource> objectSetSource, const char* name = ""); // for ObjectSetView

	IdSpace (const IdSpace& source);				// disabled
	IdSpace&	operator= (const IdSpace& source);	// disabled

	GSErrCode	ReidentifyObjectsInternal (GS::HashTable<ODB::Id, ODB::Id>* idMapTable, ObjectFilter* objectFilter);

	void		SendObjectAdded (ObjectInfo* info);

public:
		// Constructors, destructor

	IdSpace (const char* name = "");
   ~IdSpace ();

		// Name query

	const char*	GetName () const;
	void		SetName (const char* newName);
	bool		HasName () const;

		// Content management

	GSErrCode	MoveAllObjects (IdSpace* source);
	GSErrCode	MoveObject     (Ref<Object> sourceObject);

	void		DeleteAllExternalObjects ();
	void		DeleteAllObjects ();

		// Id management

	GSErrCode	ReidentifyAllObjects ();
	GSErrCode	ReidentifyAllObjects (GS::HashTable<ODB::Id, ODB::Id>* idMapTable);

	GSErrCode	ReidentifyObjects	 (ObjectFilter* objectFilter = nullptr);
	GSErrCode	ReidentifyObjects	 (GS::HashTable<ODB::Id, ODB::Id>* idMapTable, ObjectFilter* objectFilter = nullptr);

	GSErrCode	ReidentifyObjects	 (const std::function<bool (const ConstRef<Object>& object)>& objectFilter);
	GSErrCode	ReidentifyObjects	 (GS::HashTable<ODB::Id, ODB::Id>* idMapTable, const std::function<bool (const ConstRef<Object>& object)>& objectFilter);

	GSErrCode	ReidentifyObject	 (Ref<Object> object);
	void		GetReidentificationMappings (GS::HashTable<ODB::Id, ODB::Id>* idMapTable) const;
	void		SetReidentificationMappings (const GS::HashTable<ODB::Id, ODB::Id>& idMapTable);
	void		StopReidentification ();

	bool		IsUnderReidentification () const;

	bool		IsSeparate (const IdSpace& rightOp) const;

		// Comparing

	bool		IsEqualByIdentity (const IdSpace& rightOp) const;
	bool		IsEqualByContent  (const IdSpace& rightOp, Object::IsolatedStateIO* isolatedStateIO = nullptr) const;

		// Content query

	ObjectRefEnumerator		 objects;
	ConstObjectRefEnumerator constObjects;

	RefList<Object>			GetObjects		(ObjectFilter* objectFilter = nullptr);
	ConstRefList<Object>	GetObjects		(ObjectFilter* objectFilter = nullptr) const;
	ConstRefList<Object>	GetConstObjects (ObjectFilter* objectFilter = nullptr) const;

	bool		Contains		(const Id& objectId) const;
	bool		HasCounterpart	(const ConstRef<Object>& object) const;
	template <class Type>
	Ref<Type>	FindCounterpart (const ConstRef<Type>& object) const;

	const GS::ClassInfo*	GetClassInfo (const Id& objectId) const;

	USize		GetObjectCount () const;
	bool		IsEmpty		   () const;

	void		EnumerateObjects (const std::function<void (const Ref<Object>&)>& processor);
	void		EnumerateObjects (const std::function<void (const ConstRef<Object>&)>& processor) const;

	void		EnumerateDatabases (const std::function<void (const Ref<Database>& database)>& processor);
	void		EnumerateDatabases (const std::function<void (const ConstRef<Database>& database)>& processor) const;

		// Object loader management

	void		RegisterObjectLoader   (ObjectLoader* objectLoader);
	void		UnregisterObjectLoader (ObjectLoader* objectLoader);

		// Default and input identifier space management

	static IdSpace*			GetDefaultIdSpace ();

	static inline IdSpace*	GetInputIdSpace ();
	static void				SetInputIdSpace (IdSpace* newInputIdSpace);		// sets thread input IdSpace of the current thread
	static void				SetDefaultInputIdSpace ();

	class ODB_DLL_EXPORT InputScope {
	private:
		bool	 isOpen;
		IdSpace* previousInputIdSpace;

	public:
		InputScope (IdSpace* newInputIdSpace);
	   ~InputScope ();

		void	Close ();
	};

		// AboutToDelete event

	GS::EventSender<GS::SendCaller<CommonRefUntyped>, const Ref<Object>&> AboutToDelete;

		// Testing

	UInt32	GetLocalObjectCount () const;

	UInt32	GetLoadObjectCallCount  () const;
	UInt32	GetLoadLinksCallCount   () const;
	
	const ObjectRegister* GetObjectRegister () const;

		// Types

	class ODB_DLL_EXPORT ObjectObserver {
	protected:
		friend class IdSpace;   // to allow access to event sending methods

		virtual ~ObjectObserver ();

		virtual void      ObjectAddedToIdSpace (IdSpace* /*idSpace*/, const Ref<Object>& /*object*/) {}
	};

		// Module private methods

#ifdef ODB_MODULE_PRIVATE

	void		Attach (ObjectObserver& observer);
	void		Detach (ObjectObserver& observer);

	void		AddObject	  (ObjectInfo* info);
	void		DeleteObject  (ObjectInfo* info);
	void		SetObjectId   (ObjectInfo* info, const Id& newId);
	ObjectInfo*	AcquireObject (const Id& id) const;
	ObjectInfo*	AcquireObjectWithReidentification (Id* id) const;
	void		GetReidentifiedId (Id* id) const;
	void		AddReidentificationMapping (const Id& oldId, const Id& reidentifiedId);
	bool		HasReidentificationMapping (const Id& oldId) const;

	void		DatabaseCreated (const Ref<Database>& database);
	void		DatabaseDeleted (const Ref<Database>& database);

	bool		LoadObject (const Id& id);
	bool		LoadLinks  (const Id& id);
	bool		IsLinked   () const;

#endif
};


class IdSpace::ObjectRegister {
private:
	friend class IdSpace;

	ObjectRegister (const ObjectRegister& source);				// disabled
	ObjectRegister&	operator= (const ObjectRegister& source);	// disabled

public:
	enum AddResult {
		ObjectAdded,
		ObjectExists,
	};
	
	ObjectRegister ();
	virtual ~ObjectRegister ();

	virtual AddResult	Add	    (const Id& id, ObjectInfo* objectInfo) mtaccess = 0;
	virtual void		Delete  (const Id& id) mtaccess = 0;
	virtual ObjectInfo*	Acquire (const Id& id) const mtaccess = 0;

	virtual void		GetContent			(GS::Array<Ref<Object>>* content) const mtaccess = 0;
	virtual void		GetLocalContent		(GS::Array<Ref<Object>>* content) const mtaccess = 0;
	virtual UInt32		GetObjectCount		() const mtaccess = 0;
	virtual UInt32		GetLocalObjectCount	() const = 0;

	virtual bool					Contains	 (const Id& id) const mtaccess = 0;
	virtual const GS::ClassInfo*	GetClassInfo (const Id& id) const mtaccess = 0;
	virtual bool					IsLinked	 (const Id& id) const mtaccess = 0;

	virtual GSErrCode	WriteIsolatedState (const Id& objectId, GS::OChannel& oc) const mtaccess = 0;
	virtual GSErrCode	WriteLinks		   (const Id& objectId, GS::OChannel& oc) const mtaccess = 0;
};

}	// namespace ODB



template <class Type>
ODB::Ref<Type>	ODB::IdSpace::FindCounterpart (const ConstRef<Type>& object) const
{
	if (object.GetIdSpace () == this) {
		DBBREAK ();		// this method is intended to interrelate different identifier spaces (note: otherwise constness of the reference would be eliminated)
		return nullptr;
	}

	return Ref<Type> (ReferToExisting, object.GetId (), const_cast<IdSpace*> (this));	// it never creates new reference into this IdSpace so const cast can be used
}


inline ODB::IdSpace*	ODB::IdSpace::GetInputIdSpace ()
{
	IdSpace* result = inputIdSpace.Get ();

	return (result != nullptr ? result : GetDefaultIdSpace ());
}


#endif
