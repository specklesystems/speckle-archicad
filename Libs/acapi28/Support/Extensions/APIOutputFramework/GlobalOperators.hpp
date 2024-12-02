#ifndef __GLOBALOPERATORS_HPP__
#define __GLOBALOPERATORS_HPP__

#include "Definitions.hpp"
#include "APIdefs_Database.h"
#include "BM.hpp"
#include "Channel.hpp"
#include "GSAPIWrappers.hpp"
#include "UniString.hpp"
#include "APIFunctionsEnvironment.hpp"

#include <type_traits>

inline bool operator< (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)
{
	return leftOp.elemSetId < rightOp.elemSetId;
}

inline bool operator<= (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)
{
	return ((leftOp < rightOp) || (leftOp == rightOp));
}

inline bool operator> (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)
{
	return !(leftOp <= rightOp);
}

inline bool operator>= (const API_DatabaseUnId& leftOp, const API_DatabaseUnId& rightOp)
{
	return ((leftOp > rightOp) || (leftOp == rightOp));
}

inline bool operator< (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo rightInfo)
{
	if ((leftInfo.databaseUnId < rightInfo.databaseUnId) ||
		((leftInfo.databaseUnId == rightInfo.databaseUnId) &&
		 ((leftInfo.typeID < rightInfo.typeID) ||
		  ((leftInfo.typeID == rightInfo.typeID) &&
		   (leftInfo.typeID == APIWind_DrawingID) &&
		   (leftInfo.linkedElement < rightInfo.linkedElement)))))
	{
		return true;
	} else {
		return false;
	}
}

inline bool operator<= (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo& rightInfo)
{
	return ((leftInfo < rightInfo) || (leftInfo == rightInfo));
}

inline bool operator> (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo& rightInfo)
{
	return !(leftInfo <= rightInfo);
}

inline bool operator>= (const API_DatabaseInfo& leftInfo, const API_DatabaseInfo& rightInfo)
{
	return ((leftInfo > rightInfo) || (leftInfo == rightInfo));
}

namespace GSAPI {

inline bool operator== (const GSAPI::PrimElement& leftPrimElem, const GSAPI::PrimElement& rightPrimElem)
{
	if (BNCompareMemory (&leftPrimElem.primElem, &rightPrimElem.primElem, sizeof (leftPrimElem.primElem)) != 0) {
		return false;
	} else {
		if (((leftPrimElem.shapeProcParam1 != nullptr) && (rightPrimElem.shapeProcParam1 == nullptr)) ||
			((leftPrimElem.shapeProcParam1 == nullptr) && (rightPrimElem.shapeProcParam1 != nullptr)) ||
			((leftPrimElem.shapeProcParam2 != nullptr) && (rightPrimElem.shapeProcParam2 == nullptr)) ||
			((leftPrimElem.shapeProcParam2 == nullptr) && (rightPrimElem.shapeProcParam2 != nullptr)) ||
			((leftPrimElem.shapeProcParam3 != nullptr) && (rightPrimElem.shapeProcParam3 == nullptr)) ||
			((leftPrimElem.shapeProcParam3 == nullptr) && (rightPrimElem.shapeProcParam3 != nullptr)))
		{
			return false;
		} else {
			if (leftPrimElem.shapeProcParam1 != nullptr) {
				GSSize leftSize = BMGetPtrSize (leftPrimElem.shapeProcParam1);
				if (leftSize != BMGetPtrSize (rightPrimElem.shapeProcParam1)) {
					return false;
				} else {
					if (BNCompareMemory (leftPrimElem.shapeProcParam1, rightPrimElem.shapeProcParam1, leftSize) != 0) {
						return false;
					}
				}
			}
			if (leftPrimElem.shapeProcParam2 != nullptr) {
				GSSize leftSize = BMGetPtrSize (leftPrimElem.shapeProcParam2);
				if (leftSize != BMGetPtrSize (rightPrimElem.shapeProcParam2)) {
					return false;
				} else {
					if (BNCompareMemory (leftPrimElem.shapeProcParam2, rightPrimElem.shapeProcParam2, leftSize) != 0) {
						return false;
					}
				}
			}
			if (leftPrimElem.shapeProcParam3 != nullptr) {
				GSSize leftSize = BMGetPtrSize (leftPrimElem.shapeProcParam3);
				if (leftSize != BMGetPtrSize (rightPrimElem.shapeProcParam3)) {
					return false;
				} else {
					if (BNCompareMemory (leftPrimElem.shapeProcParam3, rightPrimElem.shapeProcParam3, leftSize) != 0) {
						return false;
					}
				}
			}
			return true;
		}
	}
}

inline bool operator!= (const GSAPI::PrimElement& leftPrimElem, const GSAPI::PrimElement& rightPrimElem)
{
    return (!(leftPrimElem == rightPrimElem));
}

template <typename ArrayType, UInt32 ArraySize>
void Copy (ArrayType (& leftArray)[ArraySize], ArrayType const (& rightArray) [ArraySize])
{
	for (UInt32 i = 0; i < ArraySize; i++) {
		leftArray[i] = rightArray[i];
	}
}

template <typename ElemType, typename = std::enable_if_t<!std::is_array_v<ElemType>>>
void Copy (ElemType& leftElem, const ElemType& rightElem)
{
	leftElem = rightElem;
}

}	// namespace GSAPI


namespace GS {

inline GSErrCode Write (OChannel& oc, const API_DatabaseUnId& unId)
{
	GS::Guid gsGuid = APIGuid2GSGuid (unId.elemSetId);
	return gsGuid.Write (oc);
}

inline GSErrCode Read (IChannel& ic, API_DatabaseUnId& unId)
{
	GS::Guid gsGuid;
	GSErrCode err = gsGuid.Read (ic);

	if (err == NoError)
		unId.elemSetId = GSGuid2APIGuid (gsGuid);

	return err;
}

inline GSErrCode Write (OChannel& oc, const API_DatabaseInfo& dbInfo)
{
	oc.Write (static_cast<short> (dbInfo.typeID));
	oc.Write (dbInfo.index);
	Write (oc, dbInfo.databaseUnId);
	Write (oc, dbInfo.masterLayoutUnId);
	oc.Write (GS::UniString (dbInfo.title));
	oc.Write (GS::UniString (dbInfo.name));
	return oc.Write (GS::UniString (dbInfo.ref));
}

inline GSErrCode Read (IChannel& ic, API_DatabaseInfo& dbInfo)
{
	short enumTemp = API_ZombieWindowID;
	ic.Read (enumTemp);
	dbInfo.typeID = static_cast<API_WindowTypeID> (enumTemp);

	ic.Read (dbInfo.index);
	Read (ic, dbInfo.databaseUnId);
	Read (ic, dbInfo.masterLayoutUnId);
	GS::UniString	tmp;
	ic.Read (tmp);
	GS::ucsncpy (dbInfo.title, tmp.ToUStr(), GS::ArraySize (dbInfo.title) - 1);
	ic.Read (tmp);
	GS::ucsncpy (dbInfo.name, tmp.ToUStr(), GS::ArraySize (dbInfo.name) - 1);
	GSErrCode	err = ic.Read (tmp);
	GS::ucsncpy (dbInfo.ref, tmp.ToUStr(), GS::ArraySize (dbInfo.ref) - 1);
	return err;
}

}	// namespace GS


// auxiliary structures for AC17 compatibility

struct API_DatabaseUnId_17 {
	short		filler;
	short		userId;
	UInt32		databaseId;

	API_DatabaseUnId_17 () : filler (0), userId (0), databaseId (0)
	{
	}

	API_DatabaseUnId_17 (const API_DatabaseUnId& unId) : filler (0), userId (0), databaseId (0)
	{
		ACAPI_Database_GetDBUnIdFromGuid (const_cast<API_Guid*> (&unId.elemSetId), &userId, &databaseId);
	}

	API_DatabaseUnId	ConvertToCurrentVersion (void) const
	{
		API_DatabaseUnId unId;
		BNZeroMemory (&unId, sizeof (API_DatabaseUnId));
		ACAPI_Database_GetGuidFromDBUnId (const_cast<short*> (&userId), const_cast<UInt32*> (&databaseId), &unId.elemSetId);
		return unId;
	}
};

struct API_DatabaseInfo_17 {
	API_WindowTypeID				typeID;
	Int32							index;						// database/window index
	API_DatabaseUnId_17				databaseUnId;				// database unique ID
	API_DatabaseUnId_17				masterLayoutUnId;			// for Layouts only; database unique ID of the master layout
	GS::uchar_t						title[API_UniLongNameLen];	// title of the database (generally "ref"+" "+"name") - output only
	GS::uchar_t						name[API_UniLongNameLen];	// name of the database
	GS::uchar_t						ref[API_UniLongNameLen];	// reference string/id of the database
	API_Guid						linkedElement;				// element linked to the database or drawing guid if (typeID == APIWind_DrawingID) (e.g. section to a section database); the element, never the section segment!
	API_DatabaseUnId_17				linkedDatabaseUnId;			// for databases linked to elements (section, detail, etc.): the database containing the element
	Int32							linkedSegmentMemoIndex;		// for interior elevations
	Int32							filler_1[3];

	API_DatabaseInfo_17 () :
		typeID					(API_ZombieWindowID),
		index					(0),
		databaseUnId			(),
		masterLayoutUnId		(),
		linkedElement			(APINULLGuid),
		linkedDatabaseUnId		(),
		linkedSegmentMemoIndex	(0)
	{
		BNZeroMemory (title, sizeof (title));
		BNZeroMemory (name, sizeof (name));
		BNZeroMemory (ref, sizeof (ref));
		BNZeroMemory (filler_1, sizeof (filler_1));
	}

	API_DatabaseInfo_17 (const API_DatabaseInfo& dbInfo) :
		typeID					(dbInfo.typeID),
		index					(dbInfo.index),
		databaseUnId			(dbInfo.databaseUnId),
		masterLayoutUnId		(dbInfo.masterLayoutUnId),
		linkedElement			(dbInfo.linkedElement),
		linkedDatabaseUnId		(dbInfo.linkedDatabaseUnId),
		linkedSegmentMemoIndex	(dbInfo.linkedSegmentMemoIndex)
	{
		GS::ucsncpy (title, dbInfo.title, GS::ArraySize (title) - 1);
		GS::ucsncpy (name, dbInfo.name, GS::ArraySize (name) - 1);
		GS::ucsncpy (ref, dbInfo.ref, GS::ArraySize (ref) - 1);
		BNZeroMemory (filler_1, sizeof (filler_1));
	}

	API_DatabaseInfo	ConvertToCurrentVersion (void) const
	{
		API_DatabaseInfo dbInfo;
		BNZeroMemory (&dbInfo, sizeof (API_DatabaseInfo));
		dbInfo.typeID = typeID;
		dbInfo.index = index;
		dbInfo.databaseUnId = databaseUnId.ConvertToCurrentVersion ();
		dbInfo.masterLayoutUnId = masterLayoutUnId.ConvertToCurrentVersion ();
		GS::ucsncpy (dbInfo.title, title, GS::ArraySize (dbInfo.title) - 1);
		GS::ucsncpy (dbInfo.name, name, GS::ArraySize (dbInfo.name) - 1);
		GS::ucsncpy (dbInfo.ref, ref, GS::ArraySize (dbInfo.ref) - 1);
		dbInfo.linkedElement = linkedElement;
		dbInfo.linkedDatabaseUnId = linkedDatabaseUnId.ConvertToCurrentVersion ();
		dbInfo.linkedSegmentMemoIndex = linkedSegmentMemoIndex;
		return dbInfo;
	}
};


namespace GS {

inline GSErrCode Write (OChannel& oc, const API_DatabaseUnId_17& unId)
{
	oc.Write (unId.userId);
	return oc.Write (unId.databaseId);
}

inline GSErrCode Read (IChannel& ic, API_DatabaseUnId_17& unId)
{
	ic.Read (unId.userId);
	return ic.Read (unId.databaseId);
}

inline GSErrCode Write (OChannel& oc, const API_DatabaseInfo_17& dbInfo)
{
	oc.Write (static_cast<short> (dbInfo.typeID));
	oc.Write (dbInfo.index);
	Write (oc, dbInfo.databaseUnId);
	Write (oc, dbInfo.masterLayoutUnId);
	oc.Write (GS::UniString (dbInfo.title));
	oc.Write (GS::UniString (dbInfo.name));
	return oc.Write (GS::UniString (dbInfo.ref));
}

inline GSErrCode Read (IChannel& ic, API_DatabaseInfo_17& dbInfo)
{
	short enumTemp = API_ZombieWindowID;
	ic.Read (enumTemp);
	dbInfo.typeID = static_cast<API_WindowTypeID> (enumTemp);

	ic.Read (dbInfo.index);
	Read (ic, dbInfo.databaseUnId);
	Read (ic, dbInfo.masterLayoutUnId);
	GS::UniString	tmp;
	ic.Read (tmp);
	GS::ucsncpy (dbInfo.title, tmp.ToUStr(), GS::ArraySize (dbInfo.title) - 1);
	ic.Read (tmp);
	GS::ucsncpy (dbInfo.name, tmp.ToUStr(), GS::ArraySize (dbInfo.name) - 1);
	GSErrCode	err = ic.Read (tmp);
	GS::ucsncpy (dbInfo.ref, tmp.ToUStr(), GS::ArraySize (dbInfo.ref) - 1);
	return err;
}

}	// namespace GS

#endif  // __GLOBALOPERATORS_HPP__
