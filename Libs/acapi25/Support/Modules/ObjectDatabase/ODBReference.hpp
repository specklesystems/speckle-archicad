// *****************************************************************************
//
//                           Classes Ref and ConstRef
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// *****************************************************************************


#ifndef ODBREFERENCE_HPP
#define ODBREFERENCE_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ObjectInfo.hpp"

#include <functional>


namespace ODB {
ODB_DLL_EXPORT void		LogCallStack (GS::EventLogLine& mainLogLine, const char* file, int line, const char* function);
}



// end



namespace ODB { class Object; }
namespace ODB { class Database; }
namespace ODB { class DynamicClass; }
namespace ODB { class IdSpace; }
namespace ODB { template <class Type> class Ref; }
namespace ODB { template <class Type> class ConstRef; }
namespace ODB { template <class Type> class RefList; }
namespace ODB { template <class Type> class ConstRef; }
namespace ODB { template <class Type> class ConstRefList; }
namespace GS { template <class Type, USize BufferCapacity> class ArrayFB; }
namespace GS { template <class Type> class Optional; }


// -------------------------------- Definitions --------------------------------

#ifdef CHECKED_VERSION
#define CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD		   CheckDatabaseQueryForCurrentThread ();
#define CHECK_DATABASE_MODIFICATION_FOR_CURRENT_THREAD CheckDatabaseModificationForCurrentThread ();
#else
#define CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD
#define CHECK_DATABASE_MODIFICATION_FOR_CURRENT_THREAD
#endif


// ========================== Class CommonRefUntyped ===========================

namespace ODB {

enum ReferToExistingSelector {		// refer to existing object, don't create new external reference
	ReferToExisting
};

enum TypeCastSelector {				// refer to existing object with a specific type
	TypeCast
};


enum SkipTypeCompatibilityViolationSelector {
	SkipTypeCompatibilityViolation
};


enum IdRecalculationLevel {			// controls recalculation of identifiers of objects with dependent identity
	MultiLevelIdRecalculation,		// identifiers are recalculated across all levels
	SingleLevelIdRecalculation		// identifiers are recalculated from the parent level only
};

enum ReferToObjectSelector { ReferToObject };
enum AcquireInfoSelector { AcquireInfo };
enum PassInfoSelector { PassInfo };

using ContextIdList = GS::ArrayFB<Id, 8>;

static const UInt64 ObjectTraceLine1 = ObjectInfo::ObjectTraceLine1;
static const UInt64 ObjectTraceLine2 = ObjectInfo::ObjectTraceLine2;
static const UInt64 ObjectTraceLine3 = ObjectInfo::ObjectTraceLine3;
static const UInt64 LinkTraceLine1	 = ObjectInfo::LinkTraceLine1;

ODB_DLL_EXPORT extern const GS::SerializationContext::Pointer	DeletedObjectIdSelector;

enum IdType { CurrentId, OriginalId };

using DeletedObjectIdSelectorFunction = std::function<IdType (const ConstRef<Object>& object)>;


template <class Type>
constexpr bool	IsObject = GS::IsCompatible<Type, Object>;


class ODB_DLL_EXPORT CommonRefUntyped {
private:
	static GS::ClassInfo classInfo;

protected:
	ObjectInfo* info;	// stores information about the referred object

	friend class Pin;					// to allow the Pin class to access the info record
	friend class EventReceptionLock;	// to allow the EventReceptionLock class to access the info record

	static ObjectInfo*		NewObjectInfo (Object* target);

	void	Init (const Id& id, IdSpace* idSpace = nullptr);
	void	Init (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);

	inline void	AcquireObjectInfo ();
	inline void	ReleaseObjectInfo ();
	void		SetObjectInfo	  (ObjectInfo* newInfo);
	void		DeleteObjectInfo  ();

	void		ProcessQueryRequestRelatedFlags		   () const;
	Object*		ProcessLogicalConstModificationRequest () const;
	void		ProcessLinkModificationRelatedFlags	   () const;

	void		InitializeLazyData	 () const;
	void		CalculateDerivedData () const;

	Id			CalculateContextId (const GS::Guid& classId, const Id* contextIdFromContent, const ContextIdList& contextIdList) const;

	GSErrCode	ReidentifyContextIdVersion2 (GS::IChannel& ic, Id* reidentifiedId);
	GSErrCode	ReidentifyContextIdVersion3 (GS::IChannel& ic, Id* reidentifiedId);

	ConstRef<Object>	GetScope () const;

	GSErrCode	ReadRefVersion1 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion2 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion3 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion4 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion5 (GS::IChannel& ic, IdSpace* inputIdSpace);
	GSErrCode	ReadRefVersion6 (GS::IChannel& ic, IdSpace* inputIdSpace);

	GSErrCode	WriteRefVersion1 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion2 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion3 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion4 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion5 (const Id& id, GS::OChannel& oc) const;
	GSErrCode	WriteRefVersion6 (GS::OChannel& oc) const;

	GSErrCode	WriteOriginalRefVersion6 (GS::OChannel& oc) const;

	bool		ClassHasOldOutputVersion	   () const;
	bool		OldClassVersionWasContextBased () const;
	bool		OldClassVersionWasContentBased () const;

	static GS::Optional<UInt32>	GetDataLayer (const Ref<Object>& object);

	bool		IsDataLayerDeterminedByOwner () const;
	void		DetermineDataLayerByOwner () const;

	void		CheckDatabaseQueryForCurrentThread		  () const;
	void		CheckDatabaseModificationForCurrentThread () const;

	void		DeleteTarget ();

	void		TypeCompatibilityViolation ();

public:
		// Identifier query and generation

	inline const Id&	GetId         () const;
	inline const Id&	GetOriginalId () const;
	inline bool			HasId         () const;
	inline bool			HasOriginalId () const;

	void				SetId (const Id& id, IdSpace* idSpace = nullptr) const;

	void				GenerateId		  (IdSpace* idSpace = nullptr) const;
	Id					GenerateContextId (IdSpace* idSpace = nullptr) const;
	Id					GenerateContentId (IdSpace* idSpace = nullptr) const;

	Id					CalculateContextId (const ContextIdList& contextIdList) const;
	Id					CalculateContentId (const Id& scopeId) const;
	static Id			CalculateContentId (const GS::Guid& classId, const Id& contentId, const Id& scopeId);

	void				RegenerateId		 () const;
	Id					RecalculateId		 (IdRecalculationLevel level = MultiLevelIdRecalculation) const;
	Id					RecalculateContextId (IdRecalculationLevel level = MultiLevelIdRecalculation) const;
	Id					RecalculateContentId (IdRecalculationLevel level = MultiLevelIdRecalculation) const;

	void				GetDirectIdGenerators (RefList<Object>* result) const;
	void				GetDirectIdGenerators (ConstRefList<Object>* result) const;

	inline bool			HasContentBasedIdentity	() const;
	inline void			SetContentBasedIdentity () const;
	inline void			ClearContentBasedIdentity () const;

	inline bool			HasContextBasedIdentity () const;
	inline void			SetContextBasedIdentity () const;
	inline void			ClearContextBasedIdentity () const;

	inline bool			HasIndependentIdentity () const;
	inline bool			HasDependentIdentity   () const;

		// Location query

	inline bool		IsNull      () const;
	inline bool		IsAvailable () const;
	inline bool		HadInternalLinks () const;

	inline IdSpace*	GetIdSpace () const;
	inline IdSpace*	GetOriginalIdSpace () const;

	inline Database*	GetDatabase  () const;
	bool				IsInDatabase () const;

		// Constness query

	inline bool		IsConst		   () const;
	inline bool		IsLogicalConst () const;

		// Modification control

	inline UInt64	GetCreationStamp			() const;
	inline UInt64	GetCurrentCreationStamp     () const;
	inline UInt64	GetModificationStamp		() const;
	inline UInt64	GetCurrentModificationStamp () const;

	inline bool		IsModifiedInSessionAfter (UInt64 startModificationStamp) const;

	inline bool		IsObjectModifiedOnTraceLine		   (UInt64 objectTraceLine) const;
	inline void		RestartObjectModificationTraceLine (UInt64 objectTraceLine) const;

	inline void		SetNotificationOnDelete () const;

		// Swap control

	inline void		Pin      (bool loadIfExternal = true) const;
	inline void		Unpin    () const;
	inline bool		IsPinned () const;

		// Meta data query

	ODB_FORCE_INLINE const GS::ClassInfo*	GetClassInfo () const;
	ODB_FORCE_INLINE bool					HasClassInfo () const;
	ODB_FORCE_INLINE const GS::Guid&		GetClassId	 () const;
	ODB_FORCE_INLINE bool					HasClassId	 () const;

	const DynamicClass*						GetDynamicClass () const;
	bool									HasDynamicClass () const;

		// Dynamic property query

	inline bool		HasOwnerObject () const;
	inline bool		HasOwnerLink   () const;
	inline bool		HasOwner	   () const;

	inline bool		IsSharedByAssociation () const;
	inline bool		IsSharedByReference () const;

	inline bool		IsDerived () const;

	inline UInt32	GetDataLayer () const;

		// I/O

	GSErrCode			ReadRef			 (GS::IChannel& ic, IdSpace* inputIdSpace = nullptr);
	GSErrCode			WriteRef		 (GS::OChannel& oc) const;
	GSErrCode			WriteOriginalRef (GS::OChannel& oc) const;
	inline GSErrCode	WriteId			 (GS::OChannel& oc) const;

	GSErrCode		ReadRefXML  (GS::XMLIChannel& ic, IdSpace* inputIdSpace = nullptr);
	GSErrCode		WriteRefXML (GS::XMLOChannel& oc) const;

	GSErrCode		StoreRef (GS::ObjectState& os) const;
	GSErrCode		RestoreRef (const GS::ObjectState& os, IdSpace* inputIdSpace = nullptr);

		// Other

	ULong	GenerateHashValue () const;

		// Module private methods

#ifdef ODB_MODULE_PRIVATE

	inline void		SetAsCore	 () const;
	inline void		SetAsDerived () const;

	inline bool		IsInternal  () const;
	inline bool		IsExternal  () const;

	inline bool		WasInternal () const;
	inline bool		IsDeleting  () const;

	inline bool		IsLoadingObject () const;
	inline bool		IsLoadingLinks  () const;

	inline void		PrintFlags (char (&result)[1024]) const;

	inline UChar	GetPersistentFlags () const;
	inline void		SetPersistentFlags (UChar newPersistentFlags) const;

	inline void		MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine) const;

	inline bool		HasLinkModificationOnTraceLine	 (UInt64 linkTraceLine) const;
	inline void		RestartLinkModificationTraceLine (UInt64 linkTraceLine) const;

	inline void		SetObjectOwnership	 () const;
	inline void		ClearObjectOwnership () const;

	inline ULong	GetReferenceCounter () const;

	inline UShort	GetAccessLevel () const;
	inline void		SetAccessLevel (UShort newAccessLevel) const;

	inline ObjectDataStore*			GetDataStore () const;
	inline void						SetDataStore (ObjectDataStore* newDataStore) const;

	inline const ObjectDataStore*	GetLinks		   () const;
	inline const ObjectDataStore*	GetCurrentLinks	   () const;
	inline ObjectDataStore*			ModifyLinks		   () const;
	inline ObjectDataStore*			ModifyCurrentLinks () const;

	inline const ObjectDataStore*	GetIndices			 () const;
	inline const ObjectDataStore*	GetCurrentIndices	 () const;
	inline ObjectDataStore*			ModifyIndices		 () const;
	inline ObjectDataStore*			ModifyCurrentIndices () const;

	inline bool		IsObjectModificationNotificationForRingStarted () const;
	inline void		StartObjectModificationNotificationForRing	   () const;
	inline void		StopObjectModificationNotificationForRing	   () const;

	inline bool		IsObjectModificationNotificationForTimelineStarted () const;
	inline void		StartObjectModificationNotificationForTimeline	   () const;
	inline void		StopObjectModificationNotificationForTimeline	   () const;

	inline bool		IsLinkModificationNotificationForTimelineStarted () const;
	inline void		StartLinkModificationNotificationForTimeline	 () const;
	inline void		StopLinkModificationNotificationForTimeline		 () const;

	inline bool		IsNotificationOnDeleteSet () const;
	inline void		ClearNotificationOnDelete () const;

	inline bool		IsLogicalConstModifiableWithoutModificationScope () const;

	inline bool		GetCheckFlag1	() const;
	inline void		SetCheckFlag1	() const;
	inline void		ClearCheckFlag1 () const;

	inline bool		AreObjectDeletionCheckFlagsCleared () const;

	inline void		LoadLinks () const;

#endif

	inline const Object* GetConstMemoryAddress () const;
	
	inline void		EnableEventReception  () const;
	inline void		DisableEventReception () const;
	
	inline bool		IsModifiableWithoutModificationScope () const;
	
	inline void		MarkObjectAsModified () const;
	inline void		MarkWithLinkModification () const;
	
	ODB_FORCE_INLINE ObjectInfo*	GetObjectInfo () const;
};


inline GSErrCode	Read  (GS::IChannel& ic, CommonRefUntyped& ref);
inline GSErrCode	Write (GS::OChannel& oc, const CommonRefUntyped& ref);

inline GSErrCode	WriteOriginal (GS::OChannel& oc, const CommonRefUntyped& ref);

GS_FORCE_INLINE void	Append (GS::FastLogger::LogComposer& logComposer, const CommonRefUntyped& ref);

}	// namespace ODB



inline void		ODB::CommonRefUntyped::AcquireObjectInfo ()
{
	info->Acquire ();
}


inline void		ODB::CommonRefUntyped::ReleaseObjectInfo ()
{
	bool isAutoDeletable = info->IsAutoDeletable ();	// must be queried before Release to avoid race conditions where ObjectInfo is deleted after Release (when reference counter decreases to 0) -> previous version queried this information in "else if (info->IsAutoDeletable ())" condition causing occasional multithreaded crashes
    UInt32 newReferenceCounter = info->Release ();

    if (newReferenceCounter <= 1) {				// optimization: one test is used for special cases
		if (newReferenceCounter == 0) {
			DeleteObjectInfo ();
		} else if (isAutoDeletable) {	// object is internal and has one reference (thisRef) and is shared by reference so it should be deleted
			info->ClearSharingByReference ();	// to prevent recursive deletion if destructor of the object deleted by DeleteTarget increments reference counter by copying thisRef (because when the reference counter is decremented again in the destructor new deletion will be started)
			DeleteTarget ();
		}
    }
}



inline const ODB::Id&	ODB::CommonRefUntyped::GetId () const
{
	return info->GetId ();
}


inline const ODB::Id&	ODB::CommonRefUntyped::GetOriginalId () const
{
	return info->GetOriginalId ();
}


inline bool		ODB::CommonRefUntyped::HasId () const
{
	return info->HasId ();
}


inline bool		ODB::CommonRefUntyped::HasOriginalId () const
{
	return info->HasOriginalId ();
}


inline bool		ODB::CommonRefUntyped::HasContentBasedIdentity () const
{
	return info->HasContentBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::SetContentBasedIdentity () const
{
	info->SetContentBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::ClearContentBasedIdentity () const
{
	info->ClearContentBasedIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasContextBasedIdentity () const
{
	return info->HasContextBasedIdentity ();
}

inline void		ODB::CommonRefUntyped::SetContextBasedIdentity () const
{
	info->SetContextBasedIdentity ();
}


inline void		ODB::CommonRefUntyped::ClearContextBasedIdentity () const
{
	info->ClearContextBasedIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasIndependentIdentity () const
{
	return info->HasIndependentIdentity ();
}


inline bool		ODB::CommonRefUntyped::HasDependentIdentity () const
{
	return info->HasDependentIdentity ();
}


inline bool		ODB::CommonRefUntyped::IsNull () const
{
	return info->IsNull ();
}


inline bool		ODB::CommonRefUntyped::IsAvailable () const
{
	return info->IsAvailable ();
}


inline bool		ODB::CommonRefUntyped::HadInternalLinks () const
{
	return info->HadInternalLinks ();
}


inline ODB::IdSpace*	ODB::CommonRefUntyped::GetIdSpace () const
{
	return info->GetIdSpace ();
}


inline ODB::IdSpace*	ODB::CommonRefUntyped::GetOriginalIdSpace () const
{
	return info->GetOriginalIdSpace ();
}


inline ODB::Database*	ODB::CommonRefUntyped::GetDatabase () const
{
	return info->GetDatabase ();
}


inline bool		ODB::CommonRefUntyped::IsConst () const
{
	return info->IsConst ();
}


inline bool		ODB::CommonRefUntyped::IsLogicalConst () const
{
	return info->IsLogicalConst ();
}


inline UInt64	ODB::CommonRefUntyped::GetCreationStamp () const
{
	return info->GetCreationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetCurrentCreationStamp () const
{
	return info->GetCurrentCreationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetModificationStamp () const
{
	return info->GetModificationStamp ();
}


inline UInt64	ODB::CommonRefUntyped::GetCurrentModificationStamp () const
{
	return info->GetCurrentModificationStamp ();
}


inline bool		ODB::CommonRefUntyped::IsModifiedInSessionAfter (UInt64 startModificationStamp) const
{
	return info->IsModifiedInSessionAfter (startModificationStamp);
}


inline bool		ODB::CommonRefUntyped::IsObjectModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	return info->IsObjectModifiedOnTraceLine (objectTraceLine);
}


inline void		ODB::CommonRefUntyped::RestartObjectModificationTraceLine (UInt64 objectTraceLine) const
{
	info->RestartObjectModificationTraceLine (objectTraceLine);
}


inline void		ODB::CommonRefUntyped::SetNotificationOnDelete () const
{
	info->SetNotificationOnDelete ();
}


inline void		ODB::CommonRefUntyped::Pin (bool loadIfExternal) const
{
	if (loadIfExternal)
		info->GetMemoryAddress ();	// loads the object into the memory if it is external

	info->Pin ();
}


inline void		ODB::CommonRefUntyped::Unpin () const
{
	info->Unpin ();
}


inline bool		ODB::CommonRefUntyped::IsPinned () const
{
	return info->IsPinned ();
}


ODB_FORCE_INLINE const GS::ClassInfo*	ODB::CommonRefUntyped::GetClassInfo () const
{
	return info->GetClassInfo ();
}


ODB_FORCE_INLINE bool	ODB::CommonRefUntyped::HasClassInfo () const
{
	return info->HasClassInfo ();
}


ODB_FORCE_INLINE const GS::Guid&	ODB::CommonRefUntyped::GetClassId () const
{
	return info->GetClassId ();
}


ODB_FORCE_INLINE bool	ODB::CommonRefUntyped::HasClassId () const
{
	return info->HasClassId ();
}


inline bool		ODB::CommonRefUntyped::HasOwnerObject () const
{
	return info->HasOwnerObject ();
}


inline bool		ODB::CommonRefUntyped::HasOwnerLink () const
{
	return info->HasOwnerLink ();
}


inline bool		ODB::CommonRefUntyped::HasOwner () const
{
	return info->HasOwner ();
}


inline bool		ODB::CommonRefUntyped::IsSharedByAssociation () const
{
	return info->IsSharedByAssociation ();
}


inline bool		ODB::CommonRefUntyped::IsSharedByReference () const
{
	return info->IsSharedByReference ();
}


inline bool		ODB::CommonRefUntyped::IsDerived () const
{
	return info->IsDerived ();
}


inline UInt32	ODB::CommonRefUntyped::GetDataLayer () const
{
	if (info->IsDataLayerDeterminedByOwner ())
		DetermineDataLayerByOwner ();

	return info->GetDataLayer (); 
}


inline GSErrCode	ODB::CommonRefUntyped::WriteId (GS::OChannel& oc) const
{
	return info->GetId ().Write (oc);
}


ODB_FORCE_INLINE ULong	ODB::CommonRefUntyped::GenerateHashValue () const
{
#if defined (GS_64BIT)
	return static_cast<ULong> ((((UInt64) info >> 32) & 0xFFFFFFFFUL) + ((UInt64) info & 0xFFFFFFFFUL));;
#else
	return (ULong)(GS::UIntPtr) info;
#endif
}


GS_FORCE_INLINE void	ODB::Append (GS::FastLogger::LogComposer& logComposer, const CommonRefUntyped& ref)
{
	logComposer.Append (ref.GetId ().ToGuid ());
}


#ifdef ODB_MODULE_PRIVATE

inline void		ODB::CommonRefUntyped::SetAsCore () const
{
	info->SetAsCore ();
}


inline void		ODB::CommonRefUntyped::SetAsDerived () const
{
	info->SetAsDerived ();
}


inline bool		ODB::CommonRefUntyped::IsInternal () const
{
	return info->IsInternal ();
}


inline bool		ODB::CommonRefUntyped::IsExternal () const
{
	return info->IsExternal ();
}


inline bool		ODB::CommonRefUntyped::WasInternal () const
{
	return info->WasInternal ();
}


inline bool		ODB::CommonRefUntyped::IsDeleting () const
{
	return info->IsDeleting ();
}


inline bool		ODB::CommonRefUntyped::IsLoadingObject () const
{
	return info->IsLoadingObject ();
}


inline bool		ODB::CommonRefUntyped::IsLoadingLinks () const
{
	return info->IsLoadingLinks ();
}


inline void		ODB::CommonRefUntyped::PrintFlags (char (&result)[1024]) const
{
	return info->PrintFlags (result);
}


inline UChar	ODB::CommonRefUntyped::GetPersistentFlags () const
{
	return info->GetPersistentFlags ();
}


inline void		ODB::CommonRefUntyped::SetPersistentFlags (UChar newPersistentFlags) const
{
	info->SetPersistentFlags (newPersistentFlags);
}


inline void		ODB::CommonRefUntyped::MarkObjectAsModifiedOnTraceLine (UInt64 objectTraceLine) const
{
	info->MarkObjectAsModifiedOnTraceLine (objectTraceLine);
}


inline bool		ODB::CommonRefUntyped::HasLinkModificationOnTraceLine (UInt64 linkTraceLine) const
{
	return info->HasLinkModificationOnTraceLine (linkTraceLine);
}


inline void		ODB::CommonRefUntyped::RestartLinkModificationTraceLine (UInt64 linkTraceLine) const
{
	info->RestartLinkModificationTraceLine (linkTraceLine);
}


inline void		ODB::CommonRefUntyped::SetObjectOwnership () const
{
	info->SetObjectOwnership ();
}


inline void		ODB::CommonRefUntyped::ClearObjectOwnership () const
{
	info->ClearObjectOwnership ();
}


inline ULong	ODB::CommonRefUntyped::GetReferenceCounter () const
{
	return info->GetReferenceCounter ();
}


inline UShort	ODB::CommonRefUntyped::GetAccessLevel () const
{
	return info->GetAccessLevel ();
}


inline void		ODB::CommonRefUntyped::SetAccessLevel (UShort newAccessLevel) const
{
	info->SetAccessLevel (newAccessLevel);
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetDataStore () const
{
	return info->GetDataStore ();
}


inline void		ODB::CommonRefUntyped::SetDataStore (ObjectDataStore* newDataStore) const
{
	info->SetDataStore (newDataStore);
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetLinks () const
{
	return info->GetLinks ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetCurrentLinks () const
{
	return info->GetCurrentLinks ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyLinks () const
{
	if (info->IsLinkModificationNotificationForTimelineStarted () && !info->IsLoadingLinks ())	// !IsLoadingLinks: loaded links are currently stored with link modification
		ProcessLinkModificationRelatedFlags ();

	return info->ModifyLinks ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyCurrentLinks () const
{
	if (info->IsLinkModificationNotificationForTimelineStarted ())
		ProcessLinkModificationRelatedFlags ();

	return info->ModifyCurrentLinks ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetIndices () const
{
	return info->GetIndices ();
}


inline const ODB::ObjectDataStore*	ODB::CommonRefUntyped::GetCurrentIndices () const
{
	return info->GetCurrentIndices ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyIndices () const
{
	return info->ModifyIndices ();
}


inline ODB::ObjectDataStore*	ODB::CommonRefUntyped::ModifyCurrentIndices () const
{
	return info->ModifyCurrentIndices ();
}


inline bool		ODB::CommonRefUntyped::IsObjectModificationNotificationForRingStarted () const
{
	return info->IsObjectModificationNotificationForRingStarted ();
}


inline void		ODB::CommonRefUntyped::StartObjectModificationNotificationForRing () const
{
	info->StartObjectModificationNotificationForRing ();
}


inline void		ODB::CommonRefUntyped::StopObjectModificationNotificationForRing () const
{
	info->StopObjectModificationNotificationForRing ();
}


inline bool		ODB::CommonRefUntyped::IsObjectModificationNotificationForTimelineStarted () const
{
	return info->IsObjectModificationNotificationForTimelineStarted ();
}


inline void		ODB::CommonRefUntyped::StartObjectModificationNotificationForTimeline () const
{
	info->StartObjectModificationNotificationForTimeline ();
}


inline void		ODB::CommonRefUntyped::StopObjectModificationNotificationForTimeline () const
{
	info->StopObjectModificationNotificationForTimeline ();
}


inline bool		ODB::CommonRefUntyped::IsLinkModificationNotificationForTimelineStarted () const
{
	return info->IsLinkModificationNotificationForTimelineStarted ();
}


inline void		ODB::CommonRefUntyped::StartLinkModificationNotificationForTimeline () const
{
	info->StartLinkModificationNotificationForTimeline ();
}


inline void		ODB::CommonRefUntyped::StopLinkModificationNotificationForTimeline () const
{
	info->StopLinkModificationNotificationForTimeline ();
}


inline bool		ODB::CommonRefUntyped::IsNotificationOnDeleteSet () const
{
	return info->IsNotificationOnDeleteSet ();
}


inline void		ODB::CommonRefUntyped::ClearNotificationOnDelete () const
{
	info->ClearNotificationOnDelete ();
}


inline bool   ODB::CommonRefUntyped::IsLogicalConstModifiableWithoutModificationScope () const
{
	return info->IsLogicalConstModifiableWithoutModificationScope ();
}


inline bool		ODB::CommonRefUntyped::GetCheckFlag1 () const
{
	return info->GetCheckFlag1 ();
}


inline void		ODB::CommonRefUntyped::SetCheckFlag1 () const
{
	info->SetCheckFlag1 ();
}


inline void		ODB::CommonRefUntyped::ClearCheckFlag1 () const
{
	info->ClearCheckFlag1 ();
}


inline bool		ODB::CommonRefUntyped::AreObjectDeletionCheckFlagsCleared () const
{
	return info->AreObjectDeletionCheckFlagsCleared ();
}


inline void		ODB::CommonRefUntyped::LoadLinks () const
{
	info->GetLinks ();
}

#endif


inline const ODB::Object*	ODB::CommonRefUntyped::GetConstMemoryAddress () const
{
	return info->GetMemoryAddress ();
}


inline void		ODB::CommonRefUntyped::EnableEventReception () const
{
	info->EnableEventReception ();
}


inline void		ODB::CommonRefUntyped::DisableEventReception () const
{
	info->DisableEventReception ();
}


inline bool   ODB::CommonRefUntyped::IsModifiableWithoutModificationScope () const
{
	return info->IsModifiableWithoutModificationScope ();
}


inline void		ODB::CommonRefUntyped::MarkObjectAsModified () const
{
	info->MarkObjectAsModified ();
}


inline void		ODB::CommonRefUntyped::MarkWithLinkModification () const
{
	info->MarkWithLinkModification ();
}


ODB_FORCE_INLINE ODB::ObjectInfo*	ODB::CommonRefUntyped::GetObjectInfo () const
{
	return info;
}


inline GSErrCode	ODB::Read (GS::IChannel& ic, CommonRefUntyped& ref)
{
	return ref.ReadRef (ic);
}


inline GSErrCode	ODB::Write (GS::OChannel& oc, const CommonRefUntyped& ref)
{
	return ref.WriteRef (oc);
}


inline GSErrCode	ODB::WriteOriginal (GS::OChannel& oc, const ODB::CommonRefUntyped& ref)
{
	return ref.WriteOriginalRef (oc);
}



// ============================= Class RefUntyped ==============================

namespace ODB {

enum LogicalConstSelector {
	LogicalConst				// indicates modification that doesn't affect the user level logical state of the object, only the implementation level
};

enum ConstSelector {
	Const						// indicates modification that doesn't affect the state of the object in any way that is relevant to ODB mechanisms (eg. Attach/Detach, isolated enumeration)
};

enum ModificationAuthorizationControl {		// controls the checking of the authorization to modify the object
	CheckModificationAuthorization,				// check the authorization to modify the object
	IgnoreModificationAuthorization				// ignore the authorization to modify the object
};


class ODB_DLL_EXPORT RefUntyped : public CommonRefUntyped {
protected:
	Object*		ProcessModificationRequest () const;
	Object*		ProcessModificationRequest (ModificationAuthorizationControl control) const;

	Object*		ProcessPointerConversionRequest () const;

public:
		// Reviving

	GSErrCode		Revive (IdSpace* idSpace = nullptr) const;

		// Modification control

	inline void		SetAsConst     () const;
	inline void		ClearConstness () const;

	inline void		SetAsLogicalConst     () const;
	inline void		ClearLogicalConstness () const;

	inline bool		IsDeletingEnabled () const;
	inline void		EnableDeleting	  () const;
	inline void		DisableDeleting	  () const;

	inline bool		IsAuthorizedToModify             () const;
	inline void		AcquireModificationAuthorization () const;
	inline void		ReleaseModificationAuthorization () const;

	inline bool		IsAuthorizedToLogicallyModify           () const;
	inline void		AcquireLogicalModificationAuthorization () const;
	inline void		ReleaseLogicalModificationAuthorization () const;

	inline bool		IsModifiable			 () const;
	inline bool		IsLogicalConstModifiable () const;
	inline bool		IsDeletable				 () const;

		// Lazy and derived data management

	inline bool		HasLazyDataToBeInitialized	() const;
	inline void		SetLazyDataInitialization	() const;
	inline void		ClearLazyDataInitialization	() const;

	inline bool		HasDerivedDataToBeInitialized  () const;
	inline void		SetDerivedDataInitialization   () const;
	inline void		ClearDerivedDataInitialization () const;

		// Module private methods

/* Module private method!!! */	void			SetIdSpace (IdSpace* newIdSpace) const;

/* Module private method!!! */	inline void		SetDatabase   (Database* newDatabase) const;
/* Module private method!!! */	inline void		ClearDatabase () const;

/* Module private method!!! */	void			ChangeId	(const Id& newId, IdSpace* newIdSpace) const;
/* Module private method!!! */	void			Reidentify	() const;
/* Module private method!!! */	void			Reidentify	(const Id& newId) const;

/* Module private method!!! */	inline void		SetCreationStamp     (UInt64 newCreationStamp) const;
/* Module private method!!! */	inline void		SetModificationStamp (UInt64 newModificationStamp) const;

/* Module private method!!! */	inline void		SetLinkOwnership   () const;
/* Module private method!!! */	inline void		ClearLinkOwnership () const;

/* Module private method!!! */	inline void		MarkAsSharedByAssociation () const;
/* Module private method!!! */	inline void		ClearSharingByAssociation () const;

/* Module private method!!! */	inline void		MarkAsSharedByReference () const;
/* Module private method!!! */	inline void		ClearSharingByReference () const;

/* Module private method!!! */	inline void		SetContextBasedIdentity	  () const;
/* Module private method!!! */	inline void		ClearContextBasedIdentity () const;

/* Module private method!!! */	inline bool		IsClockFlagSet () const;
/* Module private method!!! */	inline void		SetClockFlag   () const;
/* Module private method!!! */	inline void		ClearClockFlag () const;

/* Module private method!!! */	inline bool		BecomesExternalOnDelete   () const;
/* Module private method!!! */	inline void		SetExternalOnDeleteMode   () const;
/* Module private method!!! */	inline void		ClearExternalOnDeleteMode () const;

/* Module private method!!! */	inline bool		IsEventReceptionEnabled () const;

/* Module private method!!! */	inline UInt64	GetTransactionRelatedFlags  () const;
/* Module private method!!! */	inline void		SetTransactionRelatedFlags  (UInt64 newFlags) const;

/* Module private method!!! */	inline Object*	GetMemoryAddress   () const;
/* Module private method!!! */	inline void		SetTarget          (const GS::ClassInfo* classInfo, Object* object) const;
/* Module private method!!! */	inline void		SetClassInfo       (const GS::ClassInfo* classInfo) const;
/* Module private method!!! */	void			SetAsDeleted       () const;
/* Module private method!!! */	inline void		SetAsDeleting      () const;
/* Module private method!!! */	inline void		SetAsExternal      () const;
/* Module private method!!! */	inline void		ClearWasInternalFlag () const;
/* Module private method!!! */	inline void		SetAsLoadable	   () const;
/* Module private method!!! */	inline void		ClearLoadableFlag  () const;
/* Module private method!!! */	inline void		SetAsLoadingObject () const;
/* Module private method!!! */	inline void		ClearLoadingObject () const;
/* Module private method!!! */	inline void		SetAsLoadingLinks  () const;
/* Module private method!!! */	inline void		ClearLoadingLinks  () const;
/* Module private method!!! */	inline bool		HasExternalLinks	   () const;
/* Module private method!!! */	inline void		MarkWithExternalLinks  () const;
/* Module private method!!! */	inline void		ClearExternalLinksFlag () const;
/* Module private method!!! */	inline void		MarkAsHadInternalLinks () const;
/* Module private method!!! */	inline void		ClearHadInternalLinksFlag () const;
/* Module private method!!! */	inline bool		AreLinksAvailable () const;
/* Module private method!!! */	inline void		MarkAsLinksAreAvailable   () const;
/* Module private method!!! */	inline void		MarkAsLinksAreUnavailable () const;

/* Module private method!!! */	inline void		StartAssociationIndexNotification () const;
/* Module private method!!! */	inline void		StopAssociationIndexNotification  () const;


	class ODB_DLL_EXPORT ClassForDeleteAndBoolConversion {
	private:
		static void		Delete (void* pointer);

	public:
		ODB_FORCE_INLINE void	operator delete (void* pointer) noexcept (false) { if (pointer != nullptr) Delete (pointer); }
	};

/* Module private method!!! */	ODB_FORCE_INLINE operator ClassForDeleteAndBoolConversion* () const;

};

}	// namespace ODB


inline void		ODB::RefUntyped::SetAsConst () const
{
	info->SetAsConst ();
}


inline void		ODB::RefUntyped::ClearConstness () const
{
	info->ClearConstness ();
}


inline void		ODB::RefUntyped::SetAsLogicalConst () const
{
	info->SetAsLogicalConst ();
}


inline void		ODB::RefUntyped::ClearLogicalConstness () const
{
	info->ClearLogicalConstness ();
}


inline bool		ODB::RefUntyped::IsDeletingEnabled () const
{
	return info->IsDeletingEnabled ();
}


inline void		ODB::RefUntyped::EnableDeleting () const
{
	info->EnableDeleting ();
}


inline void		ODB::RefUntyped::DisableDeleting () const
{
	info->DisableDeleting ();
}


inline bool		ODB::RefUntyped::IsAuthorizedToModify () const
{
	return info->IsAuthorizedToModify ();
}


inline void		ODB::RefUntyped::AcquireModificationAuthorization () const
{
	info->AcquireModificationAuthorization ();
}


inline void		ODB::RefUntyped::ReleaseModificationAuthorization () const
{
	info->ReleaseModificationAuthorization ();
}


inline bool		ODB::RefUntyped::IsAuthorizedToLogicallyModify () const
{
	return info->IsAuthorizedToLogicallyModify ();
}


inline void		ODB::RefUntyped::AcquireLogicalModificationAuthorization () const
{
	info->AcquireLogicalModificationAuthorization ();
}


inline void		ODB::RefUntyped::ReleaseLogicalModificationAuthorization () const
{
	info->ReleaseLogicalModificationAuthorization ();
}


inline bool		ODB::RefUntyped::IsModifiable () const
{
	return info->IsModifiable ();
}


inline bool		ODB::RefUntyped::IsLogicalConstModifiable () const
{
	return info->IsLogicalConstModifiable ();
}


inline bool		ODB::RefUntyped::IsDeletable () const
{
	return info->IsDeletable ();
}


inline bool		ODB::RefUntyped::HasLazyDataToBeInitialized	() const
{
	return info->HasLazyDataToBeInitialized ();
}


inline void		ODB::RefUntyped::SetLazyDataInitialization () const
{
	info->SetLazyDataInitialization ();
}


inline void		ODB::RefUntyped::ClearLazyDataInitialization () const
{
	info->ClearLazyDataInitialization ();
}


inline void		ODB::RefUntyped::SetDatabase (Database* newDatabase) const
{
	info->SetDatabase (newDatabase);
}


inline void		ODB::RefUntyped::ClearDatabase () const
{
	info->ClearDatabase ();
}


inline void		ODB::RefUntyped::SetCreationStamp (UInt64 newCreationStamp) const
{
	info->SetCreationStamp (newCreationStamp);
}


inline void		ODB::RefUntyped::SetModificationStamp (UInt64 newModificationStamp) const
{
	info->SetModificationStamp (newModificationStamp);
}


inline void		ODB::RefUntyped::SetLinkOwnership () const
{
	info->SetLinkOwnership ();
}


inline void		ODB::RefUntyped::ClearLinkOwnership () const
{
	info->ClearLinkOwnership ();
}


inline void		ODB::RefUntyped::MarkAsSharedByAssociation () const
{
	info->MarkAsSharedByAssociation ();
}


inline void		ODB::RefUntyped::ClearSharingByAssociation () const
{
	info->ClearSharingByAssociation ();
}


inline void		ODB::RefUntyped::MarkAsSharedByReference () const
{
	info->MarkAsSharedByReference ();
}


inline void		ODB::RefUntyped::ClearSharingByReference () const
{
	info->ClearSharingByReference ();
}


inline void		ODB::RefUntyped::SetContextBasedIdentity () const
{
	info->SetContextBasedIdentity ();
}


inline void		ODB::RefUntyped::ClearContextBasedIdentity () const
{
	info->ClearContextBasedIdentity ();
}


inline bool		ODB::RefUntyped::IsClockFlagSet () const
{
	return info->IsClockFlagSet ();;
}


inline void		ODB::RefUntyped::SetClockFlag () const
{
	info->SetClockFlag ();
}


inline void		ODB::RefUntyped::ClearClockFlag () const
{
	info->ClearClockFlag ();
}


inline bool		ODB::RefUntyped::BecomesExternalOnDelete () const
{
	return info->BecomesExternalOnDelete ();;
}


inline void		ODB::RefUntyped::SetExternalOnDeleteMode () const
{
	info->SetExternalOnDeleteMode ();
}


inline void		ODB::RefUntyped::ClearExternalOnDeleteMode () const
{
	info->ClearExternalOnDeleteMode ();
}


inline bool		ODB::RefUntyped::IsEventReceptionEnabled () const
{
	return info->IsEventReceptionEnabled ();;
}


inline UInt64	ODB::RefUntyped::GetTransactionRelatedFlags () const
{
	return info->GetTransactionRelatedFlags ();
}


inline void		ODB::RefUntyped::SetTransactionRelatedFlags (UInt64 newFlags) const
{
	info->SetTransactionRelatedFlags (newFlags);
}


inline ODB::Object*		ODB::RefUntyped::GetMemoryAddress () const
{
	return info->GetMemoryAddress ();
}


inline void		ODB::RefUntyped::SetTarget (const GS::ClassInfo* classInfo, Object* object) const
{
	SetClassInfo (classInfo);

	info->SetMemoryAddress (object);
}


inline void		ODB::RefUntyped::SetClassInfo (const GS::ClassInfo* classInfo) const
{
	if (classInfo != nullptr)
		info->SetDefaultSpecifiableFlags (classInfo->GetObjectDefaults ());

	info->SetClassInfo (classInfo);
}


inline void		ODB::RefUntyped::SetAsDeleting () const
{
	info->SetAsDeleting ();
}


inline void		ODB::RefUntyped::SetAsExternal () const
{
	info->SetAsExternal ();
}


inline void		ODB::RefUntyped::ClearWasInternalFlag () const
{
	info->ClearWasInternalFlag ();
}


inline void		ODB::RefUntyped::SetAsLoadable () const
{
	info->SetAsLoadable ();
}


inline void		ODB::RefUntyped::ClearLoadableFlag () const
{
	info->ClearLoadableFlag ();
}


inline void		ODB::RefUntyped::SetAsLoadingObject () const
{
	info->SetAsLoadingObject ();
}


inline void		ODB::RefUntyped::ClearLoadingObject () const
{
	info->ClearLoadingObject ();
}


inline void		ODB::RefUntyped::SetAsLoadingLinks () const
{
	info->SetAsLoadingLinks ();
}


inline void		ODB::RefUntyped::ClearLoadingLinks () const
{
	info->ClearLoadingLinks ();
}


inline bool		ODB::RefUntyped::HasExternalLinks () const
{
	return info->HasExternalLinks ();
}


inline void		ODB::RefUntyped::MarkWithExternalLinks () const
{
	info->MarkWithExternalLinks ();
}


inline void		ODB::RefUntyped::ClearExternalLinksFlag () const
{
	info->ClearExternalLinksFlag ();
}


inline void		ODB::RefUntyped::MarkAsHadInternalLinks () const
{
	info->MarkAsHadInternalLinks ();
}


inline void		ODB::RefUntyped::ClearHadInternalLinksFlag () const
{
	info->ClearHadInternalLinksFlag ();
}


inline bool		ODB::RefUntyped::AreLinksAvailable () const
{
	return info->AreLinksAvailable ();
}


inline void		ODB::RefUntyped::MarkAsLinksAreAvailable () const
{
	info->MarkAsLinksAreAvailable ();
}


inline void		ODB::RefUntyped::MarkAsLinksAreUnavailable () const
{
	info->MarkAsLinksAreUnavailable ();
}


inline void		ODB::RefUntyped::StartAssociationIndexNotification () const
{
	info->StartAssociationIndexNotification ();
}


inline void		ODB::RefUntyped::StopAssociationIndexNotification () const
{
	info->StopAssociationIndexNotification ();
}


ODB_FORCE_INLINE ODB::RefUntyped::operator ODB::RefUntyped::ClassForDeleteAndBoolConversion* () const
{
	return reinterpret_cast<ClassForDeleteAndBoolConversion*> (info->GetMemoryAddress ());
}


// ================================= Class Ref =================================

namespace ODB {

class NullRefType;


template <class Type>
class Ref : public RefUntyped {
private:
	template <class T> friend class Ref;		// to allow different Ref<T> to access each other's members
	template <class T> friend class ConstRef;	// to allow assignment and comparison between ConstRef and Ref

	class X {};	// helper type for the safe comparison against nullptr

public:
	using ObjectType = Type;

		// Constructors, destructor, assignment

	ODB_FORCE_INLINE Ref ();
	ODB_FORCE_INLINE Ref (std::nullptr_t);
	inline           Ref (Type* object);
	ODB_FORCE_INLINE Ref (const NullRefType&);
	ODB_FORCE_INLINE explicit Ref (const Id& id, IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE Ref (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE Ref (ReferToExistingSelector, TypeCastSelector, const Id& id, const IdSpace* idSpace = nullptr);

	ODB_FORCE_INLINE Ref (const Ref& source);
	ODB_FORCE_INLINE Ref (Ref&& source);

	template <class SourceType>
	ODB_FORCE_INLINE Ref (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE Ref (Ref<SourceType>&& source);

	inline Ref&				operator= (Type* object);
	ODB_FORCE_INLINE Ref&	operator= (const Ref& source);
	ODB_FORCE_INLINE Ref&	operator= (Ref&& source);

	template <class SourceType>
	ODB_FORCE_INLINE Ref&	operator= (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE Ref&	operator= (Ref<SourceType>&& source);

	ODB_FORCE_INLINE ~Ref ();

		// Comparison

	ODB_FORCE_INLINE bool		operator== (const Ref& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const Ref<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const ConstRef<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator== (const X*) const;
	ODB_FORCE_INLINE bool		operator!= (const Ref& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const Ref<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const ConstRef<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator!= (const X*) const;

		// Dereferencing

	ODB_FORCE_INLINE const Type*	operator-> () const;
	ODB_FORCE_INLINE const Type&	operator* () const;
	ODB_FORCE_INLINE Type*			operator() () const;
	ODB_FORCE_INLINE Type*			operator() (LogicalConstSelector) const;
	ODB_FORCE_INLINE Type*			operator() (ModificationAuthorizationControl control) const;

	template <class Type2 = Type>
	ODB_FORCE_INLINE typename Type2::ConstMethods*	operator() (ConstSelector) const;

	ODB_FORCE_INLINE Type*			ToPtr      () const;
	ODB_FORCE_INLINE const Type*	ToConstPtr () const;

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const Ref<BaseType>&	As () const;

	ODB_FORCE_INLINE const Ref<Object>&		AsObject () const;

	ODB_FORCE_INLINE const ConstRef<Type>&	AsConst () const;

		// Module private methods
								
/* Module private method!!! */	inline Ref (ReferToObjectSelector, const GS::ClassInfo* classInfo, Object* target);
/* Module private method!!! */	inline Ref (AcquireInfoSelector, ObjectInfo* objectInfo);
/* Module private method!!! */	inline Ref (PassInfoSelector, ObjectInfo* objectInfo);
};


template <class Type>
class ConstMethods {
public:
	Type*				GetPtr () { return const_cast<Type*> (reinterpret_cast<const Ref<Type>*> (this)->operator-> ()); }
	const Ref<Type>&	GetRef () { return *reinterpret_cast<const Ref<Type>*> (this); }
};


template <class Type>
inline GSErrCode	Store  (GS::ObjectState& os, const Ref<Type>& ref);

template <class Type>
inline GSErrCode	Restore (const GS::ObjectState& os, Ref<Type>& ref);


class ODB_DLL_EXPORT NullRefType : public Ref<Object> {};

ODB_DLL_EXPORT extern const NullRefType	NullRef;	// Null reference

using ObjectRef = Ref<Object>;

}	// namespace ODB


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref ()
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (std::nullptr_t)
{
	info = &NullObjectInfo;
}


template <class Type>
inline ODB::Ref<Type>::Ref (Type* object)
{
	if (object == nullptr) {
		info = &NullObjectInfo;
	} else {
		DBASSERT (dynamic_cast<Type*> (static_cast<Object*> (object)) != nullptr);

		info = object->GetRef ().info;
		AcquireObjectInfo ();
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const NullRefType&)
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Id& id, IdSpace* idSpace)
{
	Init (id, idSpace);

	if (info->HasCurrentMemoryAddress () && dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
		TypeCompatibilityViolation ();
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (ReferToExistingSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);

	if (info->HasCurrentMemoryAddress () && dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
		TypeCompatibilityViolation ();
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (ReferToExistingSelector, TypeCastSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);

	if (info->HasCurrentMemoryAddress ()) {
		if (dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
			SetObjectInfo (&NullObjectInfo);
	} else {
		if (info->HasClassInfo ()) {
			if (!GS::IsSame<Type, Object>)
				if (!info->GetClassInfo ()->IsCompatibleWith (Type::GetClassInfoStatic ()))
					SetObjectInfo (&NullObjectInfo);
		}
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Ref& source)
{
	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (Ref&& source)
{
	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>::Ref (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
inline ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Type* object)
{
	if (object == nullptr) {
		SetObjectInfo (&NullObjectInfo);
	} else {
		DBASSERT (dynamic_cast<Type*> (static_cast<Object*> (object)) != nullptr);

		SetObjectInfo (object->GetRef ().info);
	}

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (const Ref& source)
{
	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Ref&& source)
{
	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::Ref<Type>&	ODB::Ref<Type>::operator= (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::Ref<Type>::~Ref ()
{
	if (info != &NullObjectInfo)
		ReleaseObjectInfo ();

	info = reinterpret_cast<ObjectInfo*> (GS::BadPointer);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const Ref& rightOp) const
{
	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const X*) const
{
	return !info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const Ref& rightOp) const
{
	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const X*) const
{
	return info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::Ref<Type>::operator-> () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type&	ODB::Ref<Type>::operator* () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return *static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() () const
{
	return static_cast<Type*> (ProcessModificationRequest ());
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() (LogicalConstSelector) const
{
	return static_cast<Type*> (ProcessLogicalConstModificationRequest ());
}


template <class Type>
template <class Type2>
ODB_FORCE_INLINE typename Type2::ConstMethods*	ODB::Ref<Type>::operator() (ConstSelector) const
{
	return const_cast<typename Type::ConstMethods*> (reinterpret_cast<const typename Type::ConstMethods*> (this));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::operator() (ModificationAuthorizationControl control) const
{
	return static_cast<Type*> (ProcessModificationRequest (control));
}


template <class Type>
ODB_FORCE_INLINE Type*	ODB::Ref<Type>::ToPtr () const
{
	return static_cast<Type*> (ProcessPointerConversionRequest ());
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::Ref<Type>::ToConstPtr () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	const Type* pointer = static_cast<Type*> (info->GetCurrentMemoryAddress ());

	if (pointer != nullptr)
		info->MarkAsAccessed ();

	return pointer;
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::Ref<BaseType>&	ODB::Ref<Type>::As () const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "'Type' is not compatible with 'BaseType'.");

	return reinterpret_cast<const Ref<BaseType>&> (*this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::Ref<ODB::Object>&	ODB::Ref<Type>::AsObject () const
{
	return reinterpret_cast<const Ref<Object>&> (*this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::ConstRef<Type>&		ODB::Ref<Type>::AsConst () const
{
	return reinterpret_cast<const ConstRef<Type>&> (*this);
}


template <class Type>
inline ODB::Ref<Type>::Ref (ReferToObjectSelector, const GS::ClassInfo* classInfo, Object* target)
{
	info = NewObjectInfo (target);

	AcquireObjectInfo ();

	SetClassInfo (classInfo);
}


template <class Type>
inline ODB::Ref<Type>::Ref (AcquireInfoSelector, ObjectInfo* objectInfo)
{
	if (objectInfo == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = objectInfo;
		AcquireObjectInfo ();
	}
}


template <class Type>
inline ODB::Ref<Type>::Ref (PassInfoSelector, ObjectInfo* objectInfo)
{
	info = objectInfo;
}


template <class Type>
GSErrCode	ODB::Store (GS::ObjectState& os, const Ref<Type>& ref)
{
	return ref.StoreRef (os);
}


template <class Type>
GSErrCode	ODB::Restore (const GS::ObjectState& os, Ref<Type>& ref)
{
	return ref.RestoreRef (os);
}


// =========================== Class ConstRefUntyped ===========================

namespace ODB {

class ODB_DLL_EXPORT ConstRefUntyped : public CommonRefUntyped {
private:
	class ClassForBoolConversion {
	private:
		void	operator delete (void* pointer);	// deleting through ConstRef is not allowed
	};

public:
	ODB_FORCE_INLINE operator const ClassForBoolConversion* () const;
};

}	// namespace ODB



ODB_FORCE_INLINE ODB::ConstRefUntyped::operator const ODB::ConstRefUntyped::ClassForBoolConversion* () const
{
	return reinterpret_cast<ClassForBoolConversion*> (info->GetMemoryAddress ());
}


// ============================== Class ConstRef ===============================

namespace ODB {

template <class Type>
class ConstRef : public ConstRefUntyped {
private:
	template <class T> friend class ConstRef;	// to allow different ConstRef<T> to access each other's mebers
	template <class T> friend class Ref;		// to allow comparison between Ref and ConstRef

	class X {};	// helper type for the safe comparison against nullptr

public:
	using ObjectType = Type;

		// Constructors, destructor, assigment

	ODB_FORCE_INLINE ConstRef ();
	ODB_FORCE_INLINE ConstRef (std::nullptr_t);
	inline           ConstRef (const Type* object);
	ODB_FORCE_INLINE ConstRef (const NullRefType&);
	ODB_FORCE_INLINE explicit ConstRef (const Id& id, IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE ConstRef (ReferToExistingSelector, const Id& id, const IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE ConstRef (ReferToExistingSelector, SkipTypeCompatibilityViolationSelector, const Id& id, const IdSpace* idSpace = nullptr);
	ODB_FORCE_INLINE ConstRef (ReferToExistingSelector, TypeCastSelector, const Id& id, const IdSpace* idSpace = nullptr);

	ODB_FORCE_INLINE ConstRef (const ConstRef& source);
	ODB_FORCE_INLINE ConstRef (ConstRef&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (const ConstRef<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (ConstRef<SourceType>&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef (Ref<SourceType>&& source);


	inline ConstRef&	        operator= (const Type* object);
	ODB_FORCE_INLINE ConstRef&	operator= (const ConstRef& source);
	ODB_FORCE_INLINE ConstRef&	operator= (ConstRef&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (const ConstRef<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (ConstRef<SourceType>&& source);

	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (const Ref<SourceType>& source);
	template <class SourceType>
	ODB_FORCE_INLINE ConstRef&	operator= (Ref<SourceType>&& source);

	ODB_FORCE_INLINE ~ConstRef ();

		// Comparison

	ODB_FORCE_INLINE bool		operator== (const ConstRef& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const ConstRef<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator== (const Ref<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator== (const X*) const;
	ODB_FORCE_INLINE bool		operator!= (const ConstRef& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const ConstRef<RightType>& rightOp) const;
	template <class RightType>
	ODB_FORCE_INLINE bool		operator!= (const Ref<RightType>& rightOp) const;
	ODB_FORCE_INLINE bool		operator!= (const X*) const;

		// Dereferencing

	ODB_FORCE_INLINE const Type*	operator-> () const;
	ODB_FORCE_INLINE const Type&	operator* () const;

	ODB_FORCE_INLINE const Type*	ToPtr () const;

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const ConstRef<BaseType>&	As () const;

	ODB_FORCE_INLINE const ConstRef<Object>&	AsObject () const;

		// ObjectState

	GSErrCode	Store (GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);

		// Module private methods

/* Module private method!!! */	inline ConstRef (AcquireInfoSelector, ObjectInfo* objectInfo);
};

using ObjectConstRef = ConstRef<Object>;

}	// namespace ODB


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef ()
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (std::nullptr_t)
{
	info = &NullObjectInfo;
}


template <class Type>
inline ODB::ConstRef<Type>::ConstRef (const Type* object)
{
	if (object == nullptr) {
		info = &NullObjectInfo;
	} else {
		DBASSERT (dynamic_cast<const Type*> (static_cast<const Object*> (object)) != nullptr);

		info = object->GetRef ().info;
		AcquireObjectInfo ();
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const NullRefType&)
{
	info = &NullObjectInfo;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const Id& id, IdSpace* idSpace)
{
	Init (id, idSpace);

	if (info->HasCurrentMemoryAddress () && dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
		TypeCompatibilityViolation ();
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ReferToExistingSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);

	if (info->HasCurrentMemoryAddress () && dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
		TypeCompatibilityViolation ();
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ReferToExistingSelector, SkipTypeCompatibilityViolationSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ReferToExistingSelector, TypeCastSelector, const Id& id, const IdSpace* idSpace)
{
	Init (ReferToExisting, id, idSpace);

	if (info->HasCurrentMemoryAddress ()) {
		if (dynamic_cast<Type*> (info->GetCurrentMemoryAddress ()) == nullptr)
			SetObjectInfo (&NullObjectInfo);
	} else {
		if (info->HasClassInfo ()) {
			if (!GS::IsSame<Type, Object>)
				if (!info->GetClassInfo ()->IsCompatibleWith (Type::GetClassInfoStatic ()))
					SetObjectInfo (&NullObjectInfo);
		}
	}
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const ConstRef& source)
{
	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ConstRef&& source)
{
	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const ConstRef<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (ConstRef<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	if (info != &NullObjectInfo)
		AcquireObjectInfo ();
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>::ConstRef (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	info = source.info;
	source.info = &NullObjectInfo;
}


template <class Type>
inline ODB::ConstRef<Type>&		ODB::ConstRef<Type>::operator= (const Type* object)
{
	if (object == nullptr) {
		SetObjectInfo (&NullObjectInfo);
	} else {
		DBASSERT (dynamic_cast<const Type*> (static_cast<const Object*> (object)) != nullptr);

		SetObjectInfo (object->GetRef ().info);
	}

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const ConstRef& source)
{
	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (ConstRef&& source)
{
	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const ConstRef<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (ConstRef<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (const Ref<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	SetObjectInfo (source.info);

	return *this;
}


template <class Type>
template <class SourceType>
ODB_FORCE_INLINE ODB::ConstRef<Type>&	ODB::ConstRef<Type>::operator= (Ref<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "'SourceType' is not compatible with 'Type'.");

	GS::Swap (info, source.info);

	return *this;
}


template <class Type>
ODB_FORCE_INLINE ODB::ConstRef<Type>::~ConstRef ()
{
	if (info != &NullObjectInfo)
		ReleaseObjectInfo ();

	info = reinterpret_cast<ObjectInfo*> (GS::BadPointer);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const ConstRef& rightOp) const
{
	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator== (const X*) const
{
	return !info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const ConstRef& rightOp) const
{
	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const Ref<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


template <class Type>
ODB_FORCE_INLINE bool	ODB::ConstRef<Type>::operator!= (const X*) const
{
	return info->HasMemoryAddress ();
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ConstRef<Type>::operator-> () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type&	ODB::ConstRef<Type>::operator* () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	info->MarkAsAccessed ();

	return *static_cast<Type*> (info->GetCurrentMemoryAddress ());
}


template <class Type>
ODB_FORCE_INLINE const Type*	ODB::ConstRef<Type>::ToPtr () const
{
	CHECK_DATABASE_QUERY_FOR_CURRENT_THREAD

	if (info->HasQueryRequestRelatedFlags ())
		ProcessQueryRequestRelatedFlags ();

	const Type* pointer = static_cast<Type*> (info->GetCurrentMemoryAddress ());

	if (pointer != nullptr)
		info->MarkAsAccessed ();

	return pointer;
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::ConstRef<BaseType>&		ODB::ConstRef<Type>::As () const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "'Type' is not compatible with 'BaseType'.");

	return reinterpret_cast<const ConstRef<BaseType>&> (*this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::ConstRef<ODB::Object>&	ODB::ConstRef<Type>::AsObject () const
{
	return reinterpret_cast<const ConstRef<Object>&> (*this);
}


template <class Type>
inline ODB::ConstRef<Type>::ConstRef (AcquireInfoSelector, ObjectInfo* objectInfo)
{
	if (objectInfo == nullptr) {
		info = &NullObjectInfo;
	} else {
		info = objectInfo;
		AcquireObjectInfo ();
	}
}


template <class Type>
GSErrCode	ODB::ConstRef<Type>::Store (GS::ObjectState& os) const
{
	return StoreRef (os);
}


template <class Type>
GSErrCode	ODB::ConstRef<Type>::Restore (const GS::ObjectState& os)
{
	return RestoreRef (os);
}


// ================================== Casting ==================================

namespace ODB {

namespace Imp {

template <class ToType, class FromType, class Choice = void>
class CastDispatcher {
	static_assert (GS::IsClass<ToType>, "'ToType' should be a class.");
	static_assert (GS::AlwaysFalse<ToType>, "To be able to cast to interface types, you must #include \"ODBIRef.hpp\".");
};


template <class ToType, class FromType>
class CastDispatcher<ToType, FromType, EnableIf<IsObject<ToType> && IsObject<FromType>>> {
public:
	static const Ref<ToType>&	StaticCast (const Ref<FromType>& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");
	
		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading
	
		return reinterpret_cast<const Ref<ToType>&> (from);
	}


	static Ref<ToType>&&	StaticCast (Ref<FromType>&& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<Ref<ToType>&&> (from);
	}


	static const ConstRef<ToType>&		StaticCast (const ConstRef<FromType>& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<const ConstRef<ToType>&> (from);
	}


	static ConstRef<ToType>&&		StaticCast (ConstRef<FromType>&& from)
	{
		static_assert (GS::AreRelated<FromType, ToType>, "'FromType' and 'ToType' are unrelated.");

		DBASSERT ((!from.HasClassInfo () && !from.IsAvailable ()) || DynamicCast (from) != NullRef);	// !IsAvailable is used instead of (GetConstMemoryAddress () == nullptr) condition because if the object is not available then DynamicCast causes assert due to unsuccessful loading

		return reinterpret_cast<ConstRef<ToType>&&> (from);
	}


	static const Ref<ToType>&		DynamicCast (const Ref<FromType>& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<const Ref<ToType>&> (from);
			else
				return reinterpret_cast<const Ref<ToType>&> (NullRef);
		}
	
		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<const Ref<ToType>&> (from);
		else
			return reinterpret_cast<const Ref<ToType>&> (NullRef);
	}


	static Ref<ToType>		DynamicCast (Ref<FromType>&& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<Ref<ToType>&&> (from);
			else
				return NullRef;
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<Ref<ToType>&&> (from);
		else
			return NullRef;
	}


	static const ConstRef<ToType>&		DynamicCast (const ConstRef<FromType>& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<const ConstRef<ToType>&> (from);
			else
				return reinterpret_cast<const ConstRef<ToType>&> (NullRef);
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<const ConstRef<ToType>&> (from);
		else
			return reinterpret_cast<const ConstRef<ToType>&> (NullRef);
	}


	static ConstRef<ToType>		DynamicCast (ConstRef<FromType>&& from)
	{
		if (from.HasClassInfo ()) {
			if (from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ()))
				return reinterpret_cast<ConstRef<ToType>&&> (from);
			else
				return NullRef;
		}

		if (dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr)
			return reinterpret_cast<ConstRef<ToType>&&> (from);
		else
			return NullRef;
	}


	static bool		IsType (const Ref<FromType>& from)
	{
		if (from.HasClassInfo ())
			return from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ());
	
		return dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr;
	}


	static bool		IsType (const ConstRef<FromType>& from)
	{
		if (from.HasClassInfo ())
			return from.GetClassInfo ()->IsCompatibleWith (ToType::GetClassInfoStatic ());

		return dynamic_cast<const ToType*> (from.GetConstMemoryAddress ()) != nullptr;
	}
};

}	// namespace Imp


template <class ToType, class FromType>
decltype (auto)		StaticCast (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (Ref<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		StaticCast (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (from);
}


template <class ToType, class FromType>
auto				StaticCast (ConstRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::StaticCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (Ref<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (from);
}


template <class ToType, class FromType>
decltype (auto)		DynamicCast (ConstRef<FromType>&& from)
{
	return Imp::CastDispatcher<ToType, FromType>::DynamicCast (std::move (from));
}


template <class ToType, class FromType>
bool	IsType (const Ref<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class ToType, class FromType>
bool	IsType (const ConstRef<FromType>& from)
{
	return Imp::CastDispatcher<ToType, FromType>::IsType (from);
}


template <class ToType, class FromType>
bool	IsExactType (const Ref<FromType>& from)
{
	return from.GetClassInfo () == ToType::GetClassInfoStatic ();
}


template <class ToType, class FromType>
bool	IsExactType (const ConstRef<FromType>& from)
{
	return from.GetClassInfo () == ToType::GetClassInfoStatic ();
}


template <class Type>
Ref<Type>			ConstCast (Ref<Type> /*from*/)
{
	static_assert (GS::AlwaysFalse<Type>, "No need to const cast an ODB::Ref, because it is already not const.");
	return {};
}


template <class Type>
const Ref<Type>&	ConstCast (const ConstRef<Type>& from)
{
	return reinterpret_cast<const Ref<Type>&> (from);
}


template <class Type>
Ref<Type>&			ConstCast (ConstRef<Type>& from)
{
	return reinterpret_cast<Ref<Type>&> (from);
}


template <class Type>
Ref<Type>			ConstCast (ConstRef<Type>&& from)
{
	return reinterpret_cast<Ref<Type>&&> (from);
}


template <class Type>
Type*	LogicalConstCast (const ConstRef<Type>& from)
{
	return reinterpret_cast<const Ref<Type>*> (&from)->operator() (LogicalConst);
}

}	// namespace ODB


// ================================= Class Ref =================================

template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator== (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info == rightOp.info);
}


template <class Type>
template <class RightType>
ODB_FORCE_INLINE bool	ODB::Ref<Type>::operator!= (const ConstRef<RightType>& rightOp) const
{
	static_assert (GS::AreRelated<Type, RightType>, "'Type' and 'RightType' are unrelated.");

	return (info != rightOp.info);
}


// ================================= Class Pin =================================

namespace ODB {

class ODB_DLL_EXPORT Pin {
private:
	CommonRefUntyped* object;		// reference to the object to be pinned
	bool			  wasPinned;	// stores the initial pinning state

	Pin (const Pin& source);				// disabled
	Pin&	operator= (const Pin& source);	// disabled

	void*	operator new (size_t) throw () { return nullptr; }			// disabled
	void	operator delete (void*) {}								// disabled
	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}						// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}							// disabled

public:
		// Constructors, destructor

	inline explicit Pin (const CommonRefUntyped& object, bool loadIfExternal = true);

	inline ~Pin ();
};

}	// namespace ODB



inline ODB::Pin::Pin (const CommonRefUntyped& object, bool loadIfExternal):
	object	  (const_cast<CommonRefUntyped*> (&object)),
	wasPinned (object.IsPinned ())
{
	this->object->AcquireObjectInfo ();
	this->object->Pin (loadIfExternal);
}


inline ODB::Pin::~Pin ()
{
	if (!wasPinned)
		object->Unpin ();
	object->ReleaseObjectInfo ();
}


// ============================ Class LoadingScope =============================

namespace  ODB {

class ObjectLoadingScope {
private:
	Ref<Object>& object;

	ObjectLoadingScope (const ObjectLoadingScope& source);				// disabled
	ObjectLoadingScope&	operator= (const ObjectLoadingScope& source);	// disabled

public:
	ObjectLoadingScope (Ref<Object>& object) : object (object) { object.SetAsLoadingObject (); }
	~ObjectLoadingScope () { object.ClearLoadingObject (); }
};

class LinkLoadingScope {
private:
	Ref<Object>& object;

	LinkLoadingScope (const LinkLoadingScope& source);				// disabled
	LinkLoadingScope&	operator= (const LinkLoadingScope& source);	// disabled

public:
	LinkLoadingScope (Ref<Object>& object) : object (object) { object.SetAsLoadingLinks (); }
	~LinkLoadingScope () { object.ClearLoadingLinks (); }
};

}	// namespace ODB


// ========================= Class EventReceptionLock ==========================

namespace ODB {

class ODB_DLL_EXPORT EventReceptionLock {
private:
	CommonRefUntyped* object;		// reference to the object to be locked
	bool			  wasEnabled;	// stores the initial event reception state

	EventReceptionLock (const EventReceptionLock& source);				// disabled
	EventReceptionLock&	operator= (const EventReceptionLock& source);	// disabled

	void*	operator new (size_t) throw () { return nullptr; }			// disabled
	void	operator delete (void*) {}								// disabled
	void*	operator new (size_t, void*) throw () { return nullptr; }	// disabled
	void	operator delete (void*, void*) {}						// disabled
	void*	operator new[] (size_t) throw () { return nullptr; }		// disabled
	void	operator delete[] (void*) {}							// disabled

public:
		// Constructors, destructor

	inline explicit EventReceptionLock (const CommonRefUntyped& object);

	inline ~EventReceptionLock ();
};

}	// namespace ODB


inline ODB::EventReceptionLock::EventReceptionLock (const CommonRefUntyped& object):
	object	   (const_cast<CommonRefUntyped*> (&object)),
	wasEnabled (object.info->IsEventReceptionEnabled ())
{
	this->object->AcquireObjectInfo ();
	this->object->DisableEventReception ();
}


inline ODB::EventReceptionLock::~EventReceptionLock ()
{
	if (wasEnabled)
		object->EnableEventReception ();
	object->ReleaseObjectInfo ();
}


// ================================= NewShared =================================

namespace ODB {

template <class Class, typename... Args>
ODB::Ref<Class> NewShared (Args&&... args)
{
	ODB::Ref<Class> ref = new Class (std::forward<Args> (args)...);
	ref.MarkAsSharedByReference ();
	return ref;
}

}	// namespace ODB


// ======================= Object based assert subjects ========================

namespace ODB {

struct ObjectAssertSubject {
	Ref<Object> object;
	GSErrCode	errorCode;

	ObjectAssertSubject (const Ref<Object>& object, GSErrCode errorCode = NoError) : object (object), errorCode (errorCode) {}
};


struct ConstObjectAssertSubject {
	ConstRef<Object> object;
	GSErrCode		 errorCode;

	ConstObjectAssertSubject (const ConstRef<Object>& object, GSErrCode errorCode = NoError) : object (object), errorCode (errorCode) {}
};

inline auto		Subject (const Ref<Object>& object)	     { return GS::Subject (object); }
inline auto		Subject (const ConstRef<Object>& object) { return GS::Subject (object); }

inline auto		Subject (const Ref<Object>& object, GSErrCode errorCode)	  { return GS::Subject (ObjectAssertSubject (object, errorCode)); }
inline auto		Subject (const ConstRef<Object>& object, GSErrCode errorCode) { return GS::Subject (ConstObjectAssertSubject (object, errorCode)); }


ODB_DLL_EXPORT GS::String	LogAssertSubject (GS::FastLogger::LogComposer& logComposer, const ObjectAssertSubject& subject);
ODB_DLL_EXPORT GS::String	LogAssertSubject (GS::FastLogger::LogComposer& logComposer, const ConstObjectAssertSubject& subject);

}	// namespace ODB


#endif
