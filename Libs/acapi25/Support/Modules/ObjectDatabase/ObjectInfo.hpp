

// *****************************************************************************
//
//                               Class ObjectInfo
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined OBJECTINFO_HPP
#define OBJECTINFO_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBId.hpp"

#include "Atomic.hpp"
#include "MemoryBarrier.hpp"
#include "ThreadSpecificStorage.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace ODB { class IdSpace; }
namespace ODB { class Database; }
namespace ODB { class Object; }
namespace ODB { class ObjectDataStore; }


// ============================= Class ObjectInfo ==============================

namespace ODB {


#if defined (_MSC_VER) && defined (GS_32BIT)
#pragma pack(push, 4)
#endif

class ODB_DLL_EXPORT ObjectInfo {
private:
	const GS::ClassInfo*	classInfo;				// class descriptor
	IdSpace*				idSpace;				// identifier space to which the object belongs
	Database*				database;				// database to which the object belongs
	Object*					memoryAddress;			// memory address of the object
	Id						id;						// identifier of the object
	UInt64					creationStamp;			// creation stamp of the object
	UInt64					modificationStamp;		// modification stamp of the object
	volatile UInt64			flags;					// various boolean informations
	ObjectDataStore*		objectDataStore;		// stores object related data (e.g. links, owner object)
	volatile UInt32			referenceCounter;		// number of references to this ObjectInfo instance
	UShort					accessLevel;			// last transaction level at which copy of the object was created (0 = no copy) or DerivedNotificationIsEnabled which enables modification of derived objects without modification scope
	UInt8					clockFlag;				// flag used by the clock algorithm
	UInt8					reservedForAllocator;	// reserved for the ObjectInfo memory allocator -> it is put here to utilize the last byte (because ObjectInfo is padded to 68 bytes and only 67 is used) - see sizes in cpp

	static GS::ThreadSpecificStorage<bool> loadingLinks;       // thread is currently loading links

	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}							// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}								// disabled

	// Flags should not be modified in read-only operations, because setting flags is neither locked nor atomic. Setting a flag bit can 
	// interfere with concurrent writes to other flag bits.
	// The only exception is the AssociationIndexNotification flag which can change from unset to set by association queries running in parallel. This race-condition
	// is acceptable, because AssociationIndexNotification is the ONLY flag bit that might change during read-only operations. Don't add other flags with similar 
	// behavior to the flags integer!
	
	static const UInt64 FlagCount									   = 44;
	static const UInt64 LastFlagPower								   = FlagCount - 1;

	static const UInt64 Internal									   = 1ull <<  0;			// object is in the memory
	static const UInt64 External									   = 1ull <<  1;			// object is not in the memory
	static const UInt64 WasInternalFlag								   = 1ull <<  2; 			// object was at least once in the memory during the current execution
	static const UInt64 Loadable									   = 1ull <<  3; 			// if the object is external then it is loadable by someone (database or object loading manager)
	static const UInt64 LoadingObject								   = 1ull <<  4; 			// object is loading (object is under transition from external to internal -> it is needed to prevent other threads to find the object internal too early)
	static const UInt64 LoadingLinks								   = 1ull <<  5; 			// links are loading
	static const UInt64 ExternalLinks								   = 1ull <<  6;			// object has links that are not in the memory (but may have links that are in the memory along some transient associations)
	static const UInt64 HadInternalLinksFlag						   = 1ull <<  7; 			// object had at least once all of it links in the memory during the current execution
	static const UInt64 LinksAreUnavailable							   = 1ull <<  8;			// object's links are not available (loadable)
	static const UInt64 Const										   = 1ull <<  9; 			// object is not modifiable because it is constant (read only)
	static const UInt64 LogicalConst								   = 1ull << 10; 			// object is logically not modifiable because it is logically constant
	static const UInt64 Undeletable									   = 1ull << 11; 			// object is not deletable
	static const UInt64 UnauthorizedToModify						   = 1ull << 12; 			// object is not modifiable because the current user has not enough privileges (object is owned by another user)
	static const UInt64 UnauthorizedToLogicallyModify				   = 1ull << 13; 			// object is logically not modifiable because the current user has not enough privileges (object is owned by another user)
	static const UInt64 HasOwnerObjectFlag							   = 1ull << 14; 			// object is owned by another object along an association
	static const UInt64 HasOwnerLinkFlag							   = 1ull << 15; 			// object is owned by a link along an association with association class
	static const UInt64 SharedByAssociation							   = 1ull << 16; 			// object is logically owned by one object but is physically shared among multiple objects (ownership is not necessarily along an association)
	static const UInt64 SharedByReference							   = 1ull << 17;
	static const UInt64 ContentBasedIdentity						   = 1ull << 18;			// object's identifier is determined by object's content
	static const UInt64 ContextBasedIdentity						   = 1ull << 19;			// object's identifier is determined by object's context
	static const UInt64 Derived										   = 1ull << 20; 			// object is derived from other (core or derived) objects
	static const UInt64 ObjectModifiedOnTraceLine1					   = 1ull << 21;			// object is modified on trace line 1
	static const UInt64 ObjectModifiedOnTraceLine2					   = 1ull << 22;			// object is modified on trace line 2
	static const UInt64 ObjectModifiedOnTraceLine3					   = 1ull << 23;			// object is modified on trace line 3
	static const UInt64 LinkModifiedOnTraceLine1					   = 1ull << 24;			// object has modification in its connections (links) on trace line 1
	static const UInt64 Pinned										   = 1ull << 25; 			// object is pinned in the memory
	static const UInt64 ExternalOnDelete							   = 1ull << 26; 			// object becomes external after it is deleted
	static const UInt64 EventReceptionIsDisabled					   = 1ull << 27; 			// object can't receive events
	static const UInt64 AssociationIndexNotification				   = 1ull << 28; 			// at least one of the object's indices is consistent with the state of this object and needs notification on modification request
	static const UInt64 DependencyNotification						   = 1ull << 29; 			// at least one of the object's dependent objects is consistent with the state of this object and needs notification on modification request
	static const UInt64 LazyDataNotification						   = 1ull << 30; 			// object has lazy data to be initialized on access
	static const UInt64 DerivedDataNotification						   = 1ull << 31; 			// object has derived data to be initialized on access
	static const UInt64 ObjectModificationNotificationForRing		   = 1ull << 32; 			// modification ring should be notified at the next object modification
	static const UInt64 ObjectModificationNotificationForTimeline	   = 1ull << 33; 			// timeline should be notified at the next object modification
	static const UInt64 LinkModificationNotificationForTimeline		   = 1ull << 34; 			// timeline should be notified at the next link modification
	static const UInt64 ObjectDeletionNotification					   = 1ull << 35;			// object deletion should send AboutToDelete notification
	static const UInt64 CreatedBySubThread							   = 1ull << 36;			// true when ObjectInfo is created by a sub thread (not by the main thread)
	static const UInt64 ModifiableWithoutModificationScope			   = 1ull << 37; 			// object is modifiable without modification scope
	static const UInt64 LogicalConstModifiableWithoutModificationScope = 1ull << 38; 			// object is logical const modifiable without modification scope
	static const UInt64 DataLayerBit1								   = 1ull << 39; 			// 1. bit of the data layer index
	static const UInt64 DataLayerBit2								   = 1ull << 40; 			// 2. bit of the data layer index
	static const UInt64 DataLayerBit3								   = 1ull << 41; 			// 3. bit of the data layer index
	static const UInt64 DetermineDataLayerByOwner					   = 1ull << 42; 			// data layer of the object should be determined by owner object (this is done on demand at first time)
	static const UInt64 CheckFlag1									   = 1ull << LastFlagPower;	// set by SharedAssociation11 for objects stored in newRightObjects, checked by Object's destructor

	static_assert (Internal	+ External + WasInternalFlag + Loadable + LoadingObject + LoadingLinks + ExternalLinks + HadInternalLinksFlag + LinksAreUnavailable + Const +
				   LogicalConst + Undeletable + UnauthorizedToModify + UnauthorizedToLogicallyModify + HasOwnerObjectFlag + HasOwnerLinkFlag + SharedByAssociation + SharedByReference + ContentBasedIdentity + ContextBasedIdentity +
				   Derived + ObjectModifiedOnTraceLine1 + ObjectModifiedOnTraceLine2 + ObjectModifiedOnTraceLine3 + LinkModifiedOnTraceLine1 + Pinned + ExternalOnDelete + EventReceptionIsDisabled + AssociationIndexNotification + DependencyNotification +
				   LazyDataNotification + DerivedDataNotification + ObjectModificationNotificationForRing + ObjectModificationNotificationForTimeline + LinkModificationNotificationForTimeline +	ObjectDeletionNotification + CreatedBySubThread + ModifiableWithoutModificationScope + LogicalConstModifiableWithoutModificationScope +
				   DataLayerBit1 + DataLayerBit2 + DataLayerBit3 + DetermineDataLayerByOwner + CheckFlag1 == (1ull << FlagCount) - 1, "Flag values are not distinct successive power of 2");

	static const UInt64 DataLayerPosition = Log2<DataLayerBit1>::Value;
	static const UInt64 DataLayerBits	  = DataLayerBit1 + DataLayerBit2 + DataLayerBit3;
	static const UInt64 MaxDataLayer	  = DataLayerBits >> DataLayerPosition;

	static const UInt64 ExistenceFlags				  = Internal | External;									// flags indicating a normal existing object (not Null)
	static const UInt64 AvailabilityFlags			  = Internal | Loadable;									// flags indicating an usable object
	static const UInt64 PhysicalModificationFlags	  = Const | UnauthorizedToModify;							// flags related to the physical modification of the object
	static const UInt64 LogicalModificationFlags	  = LogicalConst | UnauthorizedToLogicallyModify;			// flags related to the logical modification of the object
	static const UInt64 ModificationFlags			  = PhysicalModificationFlags | LogicalModificationFlags;	// flags related to the modification of the object
	static const UInt64 QueryRequestRelatedFlags	  = External | LazyDataNotification;						// flags that have effect on the query request (const method call)
	static const UInt64 ObjectModificationRequestRelatedFlags = External | AssociationIndexNotification | DependencyNotification | LazyDataNotification | ModificationFlags | ObjectModificationNotificationForRing | ObjectModificationNotificationForTimeline;	// flags that have effect on the object modification request (non-const method call)
	static const UInt64 LogicalConstObjectModificationRequestRelatedFlags = External | AssociationIndexNotification | DependencyNotification | LazyDataNotification | PhysicalModificationFlags;	// flags that have effect on the non-logical object modification request
	static const UInt64 TransactionRelatedFlags		  = LazyDataNotification | ObjectModifiedOnTraceLine1 | ObjectModifiedOnTraceLine2 | ObjectModifiedOnTraceLine3;	// flags to be saved / restored under transaction
	static const UInt64 DeletionFlags				  = Undeletable | ModificationFlags | HasOwnerLinkFlag | SharedByAssociation;	// flags related to the deletion of the object
	static const UInt64 HasOwnerFlags				  = HasOwnerObjectFlag | HasOwnerLinkFlag;					// flags indicating that the object is owned by an entity
	static const UInt64 GeneratedIdentityFlags		  = ContentBasedIdentity | ContextBasedIdentity;			// flags indicating generated (non-independent) identity
	static const UInt64 ObjectDeletionCheckFlags	  = SharedByAssociation | HasOwnerFlags | CheckFlag1;					// these flags should be 0 at object deletion after the links are destroyed
	static const UInt64 AutoDeletableFlags			  = Internal | SharedByReference;

	enum {
		ClockFlagIsCleared = 0,
		ClockFlagIsSet = 1		
	};

	enum PersistentFlags {
		P_ContentBasedIdentity = 0x1,
		P_ContextBasedIdentity = 0x2,

		P_GeneratedIdentityFlags = P_ContentBasedIdentity | P_ContextBasedIdentity
	};

	ObjectInfo (const ObjectInfo& source);				// disabled
	ObjectInfo&	operator= (const ObjectInfo& source);	// disabled

	void	SetLocationFlags ();

	void	LoadObject ();
	void	LoadLinks ();

public:
		// Default specifiable flags

	static const UInt64 DS_ContentBasedIdentity = ContentBasedIdentity;
	static const UInt64 DS_Pinned				= Pinned;
	static const UInt64 DS_Derived				= Derived;
	static const UInt64 DS_ModifiableWithoutModificationScope			  = ModifiableWithoutModificationScope;
	static const UInt64 DS_LogicalConstModifiableWithoutModificationScope = LogicalConstModifiableWithoutModificationScope;
	static const UInt64 DS_DataLayer1			= UInt64 (1) << DataLayerPosition;
	static const UInt64 DS_DataLayer2			= UInt64 (2) << DataLayerPosition;
	static const UInt64 DS_DataLayer3			= UInt64 (3) << DataLayerPosition;
	static const UInt64 DS_DataLayer4			= UInt64 (4) << DataLayerPosition;
	static const UInt64 DS_DataLayer5			= UInt64 (5) << DataLayerPosition;
	static const UInt64 DS_DataLayer6			= UInt64 (6) << DataLayerPosition;
	static const UInt64 DS_DataLayer7			= UInt64 (7) << DataLayerPosition;
	static const UInt64 DS_DetermineDataLayerByOwner = DetermineDataLayerByOwner;

	static const UInt64 ObjectTraceLine1 = ObjectModifiedOnTraceLine1;
	static const UInt64 ObjectTraceLine2 = ObjectModifiedOnTraceLine2;
	static const UInt64 ObjectTraceLine3 = ObjectModifiedOnTraceLine3;
	static const UInt64 LinkTraceLine1	 = LinkModifiedOnTraceLine1;

	ObjectInfo (Database* database, Object* memoryAddress);
	ObjectInfo (IdSpace* idSpace, Database* database, const Id& id, Object* memoryAddress);
   ~ObjectInfo ();

	ODB_FORCE_INLINE void	Acquire		  ();
	ODB_FORCE_INLINE bool	AcquireIfUsed ();
	ODB_FORCE_INLINE UInt32	Release		  ();

	ODB_FORCE_INLINE const GS::ClassInfo*	GetClassInfo () const;
	ODB_FORCE_INLINE bool					HasClassInfo () const;
	ODB_FORCE_INLINE void 					SetClassInfo (const GS::ClassInfo* newClassInfo);
	ODB_FORCE_INLINE const GS::Guid&		GetClassId	 () const;
	ODB_FORCE_INLINE bool					HasClassId	 () const;
	const char*								GetClassLogName () const;

	ODB_FORCE_INLINE IdSpace*	GetIdSpace () const;
	ODB_FORCE_INLINE IdSpace*	GetOriginalIdSpace () const;
	inline void					SetIdSpace (IdSpace* newIdSpace);

	ODB_FORCE_INLINE Database*	GetDatabase   () const;
	inline void					SetDatabase   (Database* newDatabase);
	void						ClearDatabase ();

	inline const Id&	GetId		  () const;
	inline const Id&	GetOriginalId () const;
	inline bool			HasId		  (const Id& id) const;
	inline bool			HasId		  () const;
	inline bool			HasOriginalId () const;
	void				SetId		  (const Id& newId);
	void				ClearId		  ();

	ODB_FORCE_INLINE UInt64	GetCreationStamp		() const;
	ODB_FORCE_INLINE UInt64	GetCurrentCreationStamp () const;
	ODB_FORCE_INLINE void	SetCreationStamp		(UInt64 newCreationStamp);

	ODB_FORCE_INLINE UInt64	GetModificationStamp		() const;
	ODB_FORCE_INLINE UInt64	GetCurrentModificationStamp () const;
	ODB_FORCE_INLINE void	SetModificationStamp		(UInt64 newModificationStamp);

	ODB_FORCE_INLINE bool	IsModifiedInSessionAfter (UInt64 startModificationStamp) const;

	ODB_FORCE_INLINE void	SetDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags);
	ODB_FORCE_INLINE void	ClearDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags);

	ODB_FORCE_INLINE UChar	GetPersistentFlags () const;
	ODB_FORCE_INLINE void	SetPersistentFlags (UChar newPersistentFlags);
	ODB_FORCE_INLINE static bool	HasContentBasedIdentity (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasContextBasedIdentity (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasIndependentIdentity  (UChar persistentFlags);
	ODB_FORCE_INLINE static bool	HasDependentIdentity	(UChar persistentFlags);
	ODB_FORCE_INLINE static void	ClearContentBasedIdentity (UChar& persistentFlags);
	ODB_FORCE_INLINE static void	ClearContextBasedIdentity (UChar& persistentFlags);

	ODB_FORCE_INLINE bool	HasOwnerObject		 () const;
	ODB_FORCE_INLINE void	SetObjectOwnership	 ();
	ODB_FORCE_INLINE void	ClearObjectOwnership ();

	ODB_FORCE_INLINE bool	HasOwnerLink	   () const;
	ODB_FORCE_INLINE void	SetLinkOwnership   ();
	ODB_FORCE_INLINE void	ClearLinkOwnership ();

	ODB_FORCE_INLINE bool	HasOwner () const;

	ODB_FORCE_INLINE bool	IsSharedByAssociation	 () const;
	ODB_FORCE_INLINE void	MarkAsSharedByAssociation ();
	ODB_FORCE_INLINE void	ClearSharingByAssociation ();

	ODB_FORCE_INLINE bool	IsSharedByReference	    () const;
	ODB_FORCE_INLINE void	MarkAsSharedByReference ();
	ODB_FORCE_INLINE void	ClearSharingByReference ();

	ODB_FORCE_INLINE bool	HasContentBasedIdentity	() const;
	ODB_FORCE_INLINE void	SetContentBasedIdentity ();
	ODB_FORCE_INLINE void	ClearContentBasedIdentity ();

	ODB_FORCE_INLINE bool	HasContextBasedIdentity	  () const;
	ODB_FORCE_INLINE void	SetContextBasedIdentity	  ();
	ODB_FORCE_INLINE void	ClearContextBasedIdentity ();

	ODB_FORCE_INLINE bool	HasIndependentIdentity () const;
	ODB_FORCE_INLINE bool	HasDependentIdentity   () const;

	ODB_FORCE_INLINE bool	IsDerived	 () const;
	void					SetAsCore	 ();
	void					SetAsDerived ();

	ODB_FORCE_INLINE void	MarkObjectAsModified ();
	ODB_FORCE_INLINE void	MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine);

	ODB_FORCE_INLINE bool	IsObjectModifiedOnTraceLine        (UInt64 objectTraceLine) const;
	ODB_FORCE_INLINE void	RestartObjectModificationTraceLine (UInt64 objectTraceLine);

	ODB_FORCE_INLINE void	MarkWithLinkModification  ();

	ODB_FORCE_INLINE bool	HasLinkModificationOnTraceLine	 (UInt64 linkTraceLine) const;
	ODB_FORCE_INLINE void	RestartLinkModificationTraceLine (UInt64 linkTraceLine);

	ODB_FORCE_INLINE bool	IsClockFlagSet () const;
	ODB_FORCE_INLINE void	SetClockFlag   ();
	ODB_FORCE_INLINE void	ClearClockFlag ();

	ODB_FORCE_INLINE void	MarkAsAccessed ();

	ODB_FORCE_INLINE bool	IsPinned () const;
	ODB_FORCE_INLINE void	Pin      ();
	ODB_FORCE_INLINE void	Unpin    ();

	ODB_FORCE_INLINE bool	IsConst        () const;
	ODB_FORCE_INLINE void	SetAsConst     ();
	ODB_FORCE_INLINE void	ClearConstness ();

	ODB_FORCE_INLINE bool	IsLogicalConst		  () const;
	ODB_FORCE_INLINE void	SetAsLogicalConst     ();
	ODB_FORCE_INLINE void	ClearLogicalConstness ();

	ODB_FORCE_INLINE bool	IsDeletingEnabled () const;
	ODB_FORCE_INLINE void	EnableDeleting	  ();
	ODB_FORCE_INLINE void	DisableDeleting	  ();

	ODB_FORCE_INLINE bool	IsAuthorizedToModify             () const;
	ODB_FORCE_INLINE void	AcquireModificationAuthorization ();
	ODB_FORCE_INLINE void	ReleaseModificationAuthorization ();

	ODB_FORCE_INLINE bool	IsAuthorizedToLogicallyModify		    () const;
	ODB_FORCE_INLINE void	AcquireLogicalModificationAuthorization ();
	ODB_FORCE_INLINE void	ReleaseLogicalModificationAuthorization ();

	ODB_FORCE_INLINE bool	IsModifiable			 () const;
	ODB_FORCE_INLINE bool	IsLogicalConstModifiable () const;
	ODB_FORCE_INLINE bool	IsDeletable				 () const;

	ODB_FORCE_INLINE bool	BecomesExternalOnDelete   () const;
	ODB_FORCE_INLINE void	SetExternalOnDeleteMode   ();
	ODB_FORCE_INLINE void	ClearExternalOnDeleteMode ();

	ODB_FORCE_INLINE bool	IsEventReceptionEnabled () const;
	ODB_FORCE_INLINE void	EnableEventReception    ();
	ODB_FORCE_INLINE void	DisableEventReception   ();

	ODB_FORCE_INLINE bool	HasQueryRequestRelatedFlags		   () const;
	ODB_FORCE_INLINE bool	HasObjectModificationRequestRelatedFlags () const;
	ODB_FORCE_INLINE bool	HasLogicalConstObjectModificationRequestRelatedFlags () const;
	ODB_FORCE_INLINE bool   HasOnlyObjectModificationNotificationForRingFlag () const;

	ODB_FORCE_INLINE UInt64	GetTransactionRelatedFlags  () const;
	ODB_FORCE_INLINE void	SetTransactionRelatedFlags  (UInt64 newFlags);

	ODB_FORCE_INLINE bool		IsInternal		   () const;
	ODB_FORCE_INLINE bool		IsExternal		   () const;
	ODB_FORCE_INLINE bool		IsNull			   () const;
	ODB_FORCE_INLINE bool		WasInternal		   () const;
	ODB_FORCE_INLINE bool		IsDeleting		   () const;
	ODB_FORCE_INLINE bool		IsDeleted		   () const;
	ODB_FORCE_INLINE bool		IsLoadingObject	   () const;
	ODB_FORCE_INLINE bool		IsLoadingLinks	   () const;
	ODB_FORCE_INLINE Object*	GetMemoryAddress   () const;
	ODB_FORCE_INLINE bool		HasCurrentMemoryAddress () const;
	ODB_FORCE_INLINE Object*	GetCurrentMemoryAddress () const;
	ODB_FORCE_INLINE bool		HasMemoryAddress   () const;
	void						SetMemoryAddress   (Object* newMemoryAddress);
	void						SetAsDeleted	   ();
	void						SetAsDeleting	   ();
	void						SetAsExternal	   ();
	void						ClearWasInternalFlag ();
	ODB_FORCE_INLINE bool		IsAvailable		   () const;
	void						SetAsLoadable	   ();
	void						ClearLoadableFlag  ();
	ODB_FORCE_INLINE void		SetAsLoadingObject ();
	ODB_FORCE_INLINE void		ClearLoadingObject ();
	ODB_FORCE_INLINE void		SetAsLoadingLinks  ();
	ODB_FORCE_INLINE void		ClearLoadingLinks  ();

	ODB_FORCE_INLINE bool		HasExternalLinks	   () const;
	ODB_FORCE_INLINE void		MarkWithExternalLinks  ();
	ODB_FORCE_INLINE void		ClearExternalLinksFlag ();
	ODB_FORCE_INLINE bool		HadInternalLinks	   () const;
	ODB_FORCE_INLINE void		MarkAsHadInternalLinks ();
	ODB_FORCE_INLINE void		ClearHadInternalLinksFlag ();
	ODB_FORCE_INLINE bool		AreLinksAvailable	   () const;
	ODB_FORCE_INLINE void		MarkAsLinksAreAvailable   ();
	ODB_FORCE_INLINE void		MarkAsLinksAreUnavailable ();

	ODB_FORCE_INLINE UInt32	GetReferenceCounter () const;

	ODB_FORCE_INLINE UShort	GetAccessLevel () const;
	inline void				SetAccessLevel (UShort newAccessLevel);

	ODB_FORCE_INLINE bool	IsAssociationIndexNotificationStarted () const;
	ODB_FORCE_INLINE void	StartAssociationIndexNotification	  ();
	ODB_FORCE_INLINE void	StopAssociationIndexNotification	  ();

	ODB_FORCE_INLINE bool	IsDependencyNotificationStarted	() const;
	ODB_FORCE_INLINE void	StartDependencyNotification		();
	ODB_FORCE_INLINE void	StopDependencyNotification		();

	ODB_FORCE_INLINE bool	HasLazyDataToBeInitialized	() const;
	ODB_FORCE_INLINE void	SetLazyDataInitialization	();
	ODB_FORCE_INLINE void	ClearLazyDataInitialization	();

	ODB_FORCE_INLINE bool   IsObjectModificationNotificationForRingStarted () const;
	ODB_FORCE_INLINE void   StartObjectModificationNotificationForRing     ();
	ODB_FORCE_INLINE void   StopObjectModificationNotificationForRing      ();

	ODB_FORCE_INLINE bool   IsObjectModificationNotificationForTimelineStarted () const;
	ODB_FORCE_INLINE void   StartObjectModificationNotificationForTimeline     ();
	ODB_FORCE_INLINE void   StopObjectModificationNotificationForTimeline      ();

	ODB_FORCE_INLINE bool   IsLinkModificationNotificationForTimelineStarted () const;
	ODB_FORCE_INLINE void   StartLinkModificationNotificationForTimeline     ();
	ODB_FORCE_INLINE void   StopLinkModificationNotificationForTimeline      ();

	ODB_FORCE_INLINE ObjectDataStore*		GetDataStore () const;
	void									SetDataStore (ObjectDataStore* newDataStore);

	ODB_FORCE_INLINE const ObjectDataStore*	GetLinks		   () const;
	ODB_FORCE_INLINE const ObjectDataStore*	GetCurrentLinks	   () const;
	ODB_FORCE_INLINE ObjectDataStore*		ModifyLinks		   ();
	ODB_FORCE_INLINE ObjectDataStore*		ModifyCurrentLinks ();

	ODB_FORCE_INLINE const ObjectDataStore*	GetIndices			 () const;
	ODB_FORCE_INLINE const ObjectDataStore*	GetCurrentIndices	 () const;
	ODB_FORCE_INLINE ObjectDataStore*		ModifyIndices		 ();
	ODB_FORCE_INLINE ObjectDataStore*		ModifyCurrentIndices ();

	ODB_FORCE_INLINE bool   IsNotificationOnDeleteSet () const;
	ODB_FORCE_INLINE void   SetNotificationOnDelete	  ();
	ODB_FORCE_INLINE void   ClearNotificationOnDelete ();

	ODB_FORCE_INLINE bool   IsModifiableWithoutModificationScope			 () const;
	ODB_FORCE_INLINE bool   IsLogicalConstModifiableWithoutModificationScope () const;

	ODB_FORCE_INLINE UInt32	GetDataLayer () const;
	void					SetDataLayer (UInt32 newDataLayer);

	ODB_FORCE_INLINE bool	IsDataLayerDeterminedByOwner () const;

	ODB_FORCE_INLINE bool   GetCheckFlag1	() const;
	ODB_FORCE_INLINE void   SetCheckFlag1	();
	ODB_FORCE_INLINE void   ClearCheckFlag1 ();

	ODB_FORCE_INLINE bool	AreObjectDeletionCheckFlagsCleared () const;

	ODB_FORCE_INLINE bool	IsAutoDeletable () const;

		// Memory management

	void*	operator new (size_t size);
	void	operator delete (void* pointer);

		// Debug, test

	void	PrintFlags (char (&result)[1024]) const;
};


#if defined (_MSC_VER) && defined (GS_32BIT)
#pragma pack(pop)
#endif

class ODB_DLL_EXPORT NullObjectInfoType: public ObjectInfo {
public:
	NullObjectInfoType ();
};


ODB_DLL_EXPORT extern NullObjectInfoType	NullObjectInfo;		// represents the nullptr address

}	// namespace ODB



ODB_FORCE_INLINE void	ODB::ObjectInfo::Acquire ()
{
	GS::AtomicIncrement (reinterpret_cast<volatile Int32*> (&referenceCounter));
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AcquireIfUsed ()
{
	UInt32 oldReferenceCounter = referenceCounter;
	GS::MemoryBarrierForVolatile ();	 // to ensure that referenceCounter is read from memory before it is modified

	while (oldReferenceCounter != 0) {
		if (GS::AtomicCompareAndSwap (reinterpret_cast<volatile Int32*> (&referenceCounter), static_cast<Int32> (oldReferenceCounter + 1), static_cast<Int32> (oldReferenceCounter)))
			return true;

		oldReferenceCounter = referenceCounter;
		GS::MemoryBarrierForVolatile ();	// to ensure that referenceCounter is read from memory before it is modified
	}

	return false;
}


ODB_FORCE_INLINE UInt32	ODB::ObjectInfo::Release ()
{
	DBASSERT (referenceCounter != 0);

	return static_cast<UInt32> (GS::AtomicDecrement (reinterpret_cast<volatile Int32*> (&referenceCounter)));
}


ODB_FORCE_INLINE const GS::ClassInfo*	ODB::ObjectInfo::GetClassInfo () const
{
	return classInfo;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasClassInfo () const
{
	return (classInfo != nullptr);
}


ODB_FORCE_INLINE void 	ODB::ObjectInfo::SetClassInfo (const GS::ClassInfo* newClassInfo)
{
	classInfo = newClassInfo;
}


ODB_FORCE_INLINE const GS::Guid&	ODB::ObjectInfo::GetClassId () const
{
	if (classInfo == nullptr)
		return GS::NULLGuid;
	else
		return classInfo->GetId ();
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasClassId () const
{
	return (classInfo != nullptr && classInfo->HasId ());
}


ODB_FORCE_INLINE ODB::IdSpace*	ODB::ObjectInfo::GetIdSpace () const
{
	if ((flags & ExistenceFlags) != 0)
		return idSpace;
	else
		return nullptr;
}


ODB_FORCE_INLINE ODB::IdSpace*	ODB::ObjectInfo::GetOriginalIdSpace () const
{
	return idSpace;
}


inline void		ODB::ObjectInfo::SetIdSpace (IdSpace* newIdSpace)
{
	DBASSERT (this != &NullObjectInfo);

	idSpace = newIdSpace;
}


ODB_FORCE_INLINE ODB::Database*		ODB::ObjectInfo::GetDatabase () const
{
	return database;
}


inline void		ODB::ObjectInfo::SetDatabase (Database* newDatabase)
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT (newDatabase != nullptr);

	database = newDatabase;
}


inline const ODB::Id&	ODB::ObjectInfo::GetId () const
{
	if ((flags & ExistenceFlags) != 0)
		return id;
	else
		return NullId;
}


inline const ODB::Id&	ODB::ObjectInfo::GetOriginalId () const
{
	return id;
}


inline bool		ODB::ObjectInfo::HasId (const Id& id) const
{
	return (((flags & ExistenceFlags) != 0 && this->id == id) || ((flags & ExistenceFlags) == 0 && id.IsNull ()));
}


inline bool		ODB::ObjectInfo::HasId () const
{
	return ((flags & ExistenceFlags) != 0 && !id.IsNull ());
}


inline bool		ODB::ObjectInfo::HasOriginalId () const
{
	return !id.IsNull ();
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCreationStamp () const
{
	if ((flags & WasInternalFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return creationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCurrentCreationStamp () const
{
	return creationStamp;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetCreationStamp (UInt64 newCreationStamp)
{
	creationStamp = newCreationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetModificationStamp () const
{
	if ((flags & WasInternalFlag) == 0 && (flags & ExistenceFlags) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return modificationStamp;
}


ODB_FORCE_INLINE UInt64		ODB::ObjectInfo::GetCurrentModificationStamp () const
{

	return modificationStamp;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetModificationStamp (UInt64 newModificationStamp)
{
	modificationStamp = newModificationStamp;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsModifiedInSessionAfter (UInt64 startModificationStamp) const
{
	return (modificationStamp > startModificationStamp);	// modification stamp is 0 before the first loading of FileDatabase objects so an object with stamp 0 is surely not be modified in this session => this method doesn't load so it should be used instead of GetModificationStamp in "GetModificationStamp > stamp" like expressions
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags)
{
	flags |= defaultSpecifiableFlags;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearDefaultSpecifiableFlags (UInt64 defaultSpecifiableFlags)
{
	flags &= ~defaultSpecifiableFlags;
}


ODB_FORCE_INLINE UChar	ODB::ObjectInfo::GetPersistentFlags () const
{
	UChar persistentFlags = 0;

	if (HasContentBasedIdentity ())
		persistentFlags |= P_ContentBasedIdentity;

	if (HasContextBasedIdentity ())
		persistentFlags |= P_ContextBasedIdentity;

	return persistentFlags;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetPersistentFlags (UChar newPersistentFlags)
{
	if ((newPersistentFlags & P_ContentBasedIdentity) != 0)
		SetContentBasedIdentity ();
	else
		ClearContentBasedIdentity ();

	if ((newPersistentFlags & P_ContextBasedIdentity) != 0)
		SetContextBasedIdentity ();
	else
		ClearContextBasedIdentity ();
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContentBasedIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_ContentBasedIdentity) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContextBasedIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_ContextBasedIdentity) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasIndependentIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_GeneratedIdentityFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasDependentIdentity (UChar persistentFlags)
{
	return ((persistentFlags & P_GeneratedIdentityFlags) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContentBasedIdentity (UChar& persistentFlags)
{
	persistentFlags &= ~P_ContentBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContextBasedIdentity (UChar& persistentFlags)
{
	persistentFlags &= ~P_ContextBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwnerObject () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & HasOwnerObjectFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetObjectOwnership ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= HasOwnerObjectFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearObjectOwnership ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~HasOwnerObjectFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwnerLink () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & HasOwnerLinkFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetLinkOwnership ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= HasOwnerLinkFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLinkOwnership ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~HasOwnerLinkFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOwner () const
{
	return ((flags & HasOwnerFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsSharedByAssociation () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & SharedByAssociation) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsSharedByAssociation ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= SharedByAssociation;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearSharingByAssociation ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~SharedByAssociation;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsSharedByReference () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & SharedByReference) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsSharedByReference ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= SharedByReference;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearSharingByReference ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~SharedByReference;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContentBasedIdentity () const
{
	return ((flags & ContentBasedIdentity) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetContentBasedIdentity ()
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT ((flags & ContextBasedIdentity) == 0);

	flags &= ~ContextBasedIdentity;
	flags |= ContentBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContentBasedIdentity ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ContentBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasContextBasedIdentity () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & ContextBasedIdentity) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetContextBasedIdentity ()
{
	DBASSERT (this != &NullObjectInfo);
	DBASSERT ((flags & ContentBasedIdentity) == 0);

	flags &= ~ContentBasedIdentity;
	flags |= ContextBasedIdentity;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearContextBasedIdentity ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ContextBasedIdentity;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasIndependentIdentity () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & GeneratedIdentityFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasDependentIdentity () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & GeneratedIdentityFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDerived () const
{
	if ((flags & HadInternalLinksFlag) == 0 && (flags & ExistenceFlags) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return ((flags & Derived) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkObjectAsModified ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= (ObjectModifiedOnTraceLine1 | ObjectModifiedOnTraceLine2 | ObjectModifiedOnTraceLine3);
	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags |= objectTraceLine;
	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsObjectModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	return ((flags & objectTraceLine) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::RestartObjectModificationTraceLine (UInt64 objectTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~objectTraceLine;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkWithLinkModification ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= LinkModifiedOnTraceLine1;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLinkModificationOnTraceLine (UInt64 linkTraceLine) const
{
	return ((flags & linkTraceLine) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::RestartLinkModificationTraceLine (UInt64 linkTraceLine)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~linkTraceLine;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsClockFlagSet () const
{
	return clockFlag == ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetClockFlag ()
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearClockFlag ()
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsCleared;	
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsAccessed ()
{
	DBASSERT (this != &NullObjectInfo);

	clockFlag = ClockFlagIsSet;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsPinned () const
{
	return ((flags & Pinned) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::Pin ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Pinned;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::Unpin ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Pinned;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsConst () const
{
	return ((flags & Const) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsConst ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Const;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearConstness ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Const;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLogicalConst () const
{
	return ((flags & LogicalConst) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsLogicalConst ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= LogicalConst;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLogicalConstness ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~LogicalConst;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeletingEnabled () const
{
	return ((flags & Undeletable) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::EnableDeleting ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~Undeletable;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::DisableDeleting ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= Undeletable;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAuthorizedToModify () const
{
	return ((flags & UnauthorizedToModify) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::AcquireModificationAuthorization ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~UnauthorizedToModify;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ReleaseModificationAuthorization ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= UnauthorizedToModify;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAuthorizedToLogicallyModify () const
{
	return ((flags & UnauthorizedToLogicallyModify) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::AcquireLogicalModificationAuthorization ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~UnauthorizedToLogicallyModify;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ReleaseLogicalModificationAuthorization ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= UnauthorizedToLogicallyModify;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsModifiable () const
{
	return ((flags & ModificationFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLogicalConstModifiable () const
{
	return ((flags & PhysicalModificationFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeletable () const
{
	return ((flags & DeletionFlags) == 0);
}


bool	ODB::ObjectInfo::BecomesExternalOnDelete () const
{
	return ((flags & ExternalOnDelete) != 0);
}


void	ODB::ObjectInfo::SetExternalOnDeleteMode ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= ExternalOnDelete;
}


void	ODB::ObjectInfo::ClearExternalOnDeleteMode ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~ExternalOnDelete;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsEventReceptionEnabled () const
{
	return ((flags & EventReceptionIsDisabled) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::EnableEventReception ()
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~EventReceptionIsDisabled;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::DisableEventReception ()
{
	DBASSERT (this != &NullObjectInfo);

	flags |= EventReceptionIsDisabled;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasQueryRequestRelatedFlags () const
{
	return ((flags & QueryRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasObjectModificationRequestRelatedFlags () const
{
	return ((flags & ObjectModificationRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLogicalConstObjectModificationRequestRelatedFlags () const
{
	return ((flags & LogicalConstObjectModificationRequestRelatedFlags) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasOnlyObjectModificationNotificationForRingFlag () const
{
	return ((flags & ObjectModificationRequestRelatedFlags) == ObjectModificationNotificationForRing);
}


ODB_FORCE_INLINE UInt64	ODB::ObjectInfo::GetTransactionRelatedFlags () const
{
	return (flags & TransactionRelatedFlags);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetTransactionRelatedFlags (UInt64 newFlags)
{
	DBASSERT (this != &NullObjectInfo);

	flags &= ~TransactionRelatedFlags;
	flags |= (newFlags & TransactionRelatedFlags);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsInternal () const
{
	return ((flags & Internal) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsExternal () const
{
	return ((flags & External) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsNull () const
{
	return ((flags & ExistenceFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::WasInternal () const
{
	return ((flags & WasInternalFlag) != 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeleting () const
{
	return (IsInternal () && memoryAddress == nullptr);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDeleted () const
{
	return (IsNull () && this != &NullObjectInfo);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsLoadingObject () const
{
	return ((flags & LoadingObject) != 0);
}


ODB_FORCE_INLINE bool    ODB::ObjectInfo::IsLoadingLinks () const
{
	return ((flags & LoadingLinks) != 0 && loadingLinks.Get ());
}


ODB_FORCE_INLINE ODB::Object*	ODB::ObjectInfo::GetMemoryAddress () const
{
	if ((flags & External) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return memoryAddress;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasCurrentMemoryAddress () const
{
	return memoryAddress != nullptr;
}

ODB_FORCE_INLINE ODB::Object*	ODB::ObjectInfo::GetCurrentMemoryAddress () const
{
	return memoryAddress;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasMemoryAddress () const
{
	if ((flags & External) != 0)
		const_cast<ObjectInfo*> (this)->LoadObject ();

	return (memoryAddress != nullptr);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAvailable () const
{
	return ((flags & AvailabilityFlags) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetAsLoadingObject ()
{
	DBASSERT ((flags & External) != 0);

	flags |= LoadingObject;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLoadingObject ()
{
	DBASSERT ((flags & LoadingObject) != 0);

	flags &= ~LoadingObject;

	SetLocationFlags ();
}


ODB_FORCE_INLINE void    ODB::ObjectInfo::SetAsLoadingLinks ()
{
	DBASSERT (!loadingLinks.Get ());

	flags |= LoadingLinks;

	loadingLinks.Set (true);
}


ODB_FORCE_INLINE void    ODB::ObjectInfo::ClearLoadingLinks ()
{
	DBASSERT ((flags & LoadingLinks) != 0);
	DBASSERT (loadingLinks.Get ());

	flags &= ~LoadingLinks;

	loadingLinks.Set (false);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasExternalLinks () const
{
	return ((flags & ExternalLinks) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkWithExternalLinks ()
{
	flags |= ExternalLinks;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearExternalLinksFlag ()
{
	flags &= ~ExternalLinks;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HadInternalLinks () const
{
	return ((flags & HadInternalLinksFlag) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsHadInternalLinks ()
{
	flags |= HadInternalLinksFlag;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearHadInternalLinksFlag ()
{
	flags &= ~HadInternalLinksFlag;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AreLinksAvailable () const
{
	return ((flags & ExistenceFlags) != 0 && (flags & LinksAreUnavailable) == 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsLinksAreAvailable ()
{
	flags &= ~LinksAreUnavailable;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::MarkAsLinksAreUnavailable ()
{
	flags |= LinksAreUnavailable;
}


ODB_FORCE_INLINE UInt32	ODB::ObjectInfo::GetReferenceCounter () const
{
	return referenceCounter;
}


ODB_FORCE_INLINE UShort		ODB::ObjectInfo::GetAccessLevel () const
{
	return accessLevel;
}


inline void		ODB::ObjectInfo::SetAccessLevel (UShort newAccessLevel)
{
	DBASSERT (this != &NullObjectInfo);

	accessLevel = newAccessLevel;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAssociationIndexNotificationStarted () const
{
	return ((flags & AssociationIndexNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StartAssociationIndexNotification ()
{
	flags |= AssociationIndexNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StopAssociationIndexNotification ()
{
	flags &= ~AssociationIndexNotification;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDependencyNotificationStarted () const
{
	return ((flags & DependencyNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StartDependencyNotification ()
{
	flags |= DependencyNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::StopDependencyNotification ()
{
	flags &= ~DependencyNotification;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::HasLazyDataToBeInitialized () const
{
	return ((flags & LazyDataNotification) != 0);
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::SetLazyDataInitialization ()
{
	flags |= LazyDataNotification;
}


ODB_FORCE_INLINE void	ODB::ObjectInfo::ClearLazyDataInitialization ()
{
	flags &= ~LazyDataNotification;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsObjectModificationNotificationForRingStarted () const
{
	return ((flags & ObjectModificationNotificationForRing) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartObjectModificationNotificationForRing ()
{
	flags |= ObjectModificationNotificationForRing;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopObjectModificationNotificationForRing ()
{
	flags &= ~ObjectModificationNotificationForRing;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsObjectModificationNotificationForTimelineStarted () const
{
	return ((flags & ObjectModificationNotificationForTimeline) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartObjectModificationNotificationForTimeline ()
{
	flags |= ObjectModificationNotificationForTimeline;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopObjectModificationNotificationForTimeline ()
{
	flags &= ~ObjectModificationNotificationForTimeline;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsLinkModificationNotificationForTimelineStarted () const
{
	return ((flags & LinkModificationNotificationForTimeline) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StartLinkModificationNotificationForTimeline ()
{
	flags |= LinkModificationNotificationForTimeline;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::StopLinkModificationNotificationForTimeline ()
{
	flags &= ~LinkModificationNotificationForTimeline;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsNotificationOnDeleteSet () const
{
	return ((flags & ObjectDeletionNotification) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::SetNotificationOnDelete ()
{
	flags |= ObjectDeletionNotification;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::ClearNotificationOnDelete ()
{
	flags &= ~ObjectDeletionNotification;
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsModifiableWithoutModificationScope () const
{
	return ((flags & ModifiableWithoutModificationScope) != 0);
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::IsLogicalConstModifiableWithoutModificationScope () const
{
	return ((flags & (ModifiableWithoutModificationScope | LogicalConstModifiableWithoutModificationScope)) != 0);		// if the object is modifiable then it is also logical const modifiable
}


ODB_FORCE_INLINE UInt32		ODB::ObjectInfo::GetDataLayer () const
{
	return ((flags & DataLayerBits) >> DataLayerPosition);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsDataLayerDeterminedByOwner () const
{
	return ((flags & DetermineDataLayerByOwner) != 0);
}


ODB_FORCE_INLINE bool   ODB::ObjectInfo::GetCheckFlag1 () const
{
	return ((flags & CheckFlag1) != 0);
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::SetCheckFlag1 ()
{
	flags |= CheckFlag1;
}


ODB_FORCE_INLINE void   ODB::ObjectInfo::ClearCheckFlag1 ()
{
	flags &= ~CheckFlag1;
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::AreObjectDeletionCheckFlagsCleared () const
{
	return ((flags & ObjectDeletionCheckFlags) == 0);
}


ODB_FORCE_INLINE bool	ODB::ObjectInfo::IsAutoDeletable () const
{
	return ((flags & AutoDeletableFlags) == AutoDeletableFlags);
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::GetDataStore () const
{
	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetLinks () const
{
	if ((flags & ExternalLinks) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetCurrentLinks () const
{
	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyLinks ()
{
	if ((flags & ExternalLinks) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyCurrentLinks ()
{
	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetIndices () const
{
	if ((flags & ExternalLinks) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE const ODB::ObjectDataStore*	ODB::ObjectInfo::GetCurrentIndices () const
{
	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyIndices ()
{
	if ((flags & ExternalLinks) != 0 && !IsLoadingLinks ())
		const_cast<ObjectInfo*> (this)->LoadLinks ();

	return objectDataStore;
}


ODB_FORCE_INLINE ODB::ObjectDataStore*	ODB::ObjectInfo::ModifyCurrentIndices ()
{
	return objectDataStore;
}
// _____________________________ Class ObjectInfo ______________________________


#endif
