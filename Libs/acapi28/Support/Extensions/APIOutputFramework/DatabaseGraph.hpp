#ifndef __DATABASEGRAPH_HPP__
#define __DATABASEGRAPH_HPP__

#include "APIdefs_Elements.h"
#include "IDatabaseSelector.hpp"
#include "Array.hpp"
#include "HashTable.hpp"
#include "CH.hpp"

namespace GSAPI {

// predeclarations
class DatabaseGraphNode;


/**
 * @stereotype singleton
 */
class DatabaseGraph {
private:
    DatabaseGraphNode*	root;
	bool				constructed;

private:
    DatabaseGraph (void);

	void BuildDatabaseGraph (void);
	void GetCurrentLinks (API_ElemTypeID typeID, GS::Array<API_DatabaseInfo>& links, GS::HashTable<API_DatabaseUnId, bool>* dependentDetailsHash = nullptr);
	void AddIndependentDatabases (API_WindowTypeID windowTypeID, GS::HashTable<API_DatabaseUnId, bool>* dependentDetailsHash = nullptr);
	// hot: az elozo ket fuggvenyben a ketfele hashtabla lehetne ugyanazon parameter, egyszerre ugyis csak az egyikfajta jon...
    bool AddLink (API_DatabaseInfo fromDB, API_DatabaseInfo toDB);

public:
    virtual ~DatabaseGraph (void);

	static DatabaseGraph& Instance ();

    GS::Array<API_DatabaseInfo> SelectDatabases (const GSAPI::IDatabaseSelector& selector) const;

	void Construct (void);
	void Clear (void);
};


class DatabaseGraphGuard
{
public:
	DatabaseGraphGuard ();
	virtual ~DatabaseGraphGuard ();
};

}


inline API_DatabaseUnId StripDatabaseUnId (const API_DatabaseUnId& dbUnId)
{
	API_DatabaseUnId strippedDBUnId;

	BNZeroMemory (&strippedDBUnId, sizeof (strippedDBUnId));
	strippedDBUnId.elemSetId = dbUnId.elemSetId;

	return strippedDBUnId;
}

inline API_DatabaseInfo StripDatabaseInfo (const API_DatabaseInfo& dbInfo)
{
	API_DatabaseInfo strippedDBInfo;

	BNZeroMemory (&strippedDBInfo, sizeof (strippedDBInfo));
	strippedDBInfo.typeID = dbInfo.typeID;
	strippedDBInfo.index = dbInfo.index;
	if (dbInfo.typeID == APIWind_DrawingID)
		strippedDBInfo.linkedElement = dbInfo.linkedElement;
	strippedDBInfo.databaseUnId = StripDatabaseUnId (dbInfo.databaseUnId);
	strippedDBInfo.masterLayoutUnId = StripDatabaseUnId (dbInfo.masterLayoutUnId);
	//CHTruncate (dbInfo.title, strippedDBInfo.title, sizeof (strippedDBInfo.title));
	//CHTruncate (dbInfo.name, strippedDBInfo.name, sizeof (strippedDBInfo.name));
	//CHTruncate (dbInfo.ref, strippedDBInfo.ref, sizeof (strippedDBInfo.ref));
	GS::ucsncpy (strippedDBInfo.title, dbInfo.title, GS::ArraySize (strippedDBInfo.title) - 1);
	GS::ucsncpy (strippedDBInfo.name, dbInfo.name, GS::ArraySize (strippedDBInfo.name) - 1);
	GS::ucsncpy (strippedDBInfo.ref, dbInfo.ref, GS::ArraySize (strippedDBInfo.ref) - 1);

	return strippedDBInfo;
}

inline ULong GenerateHashValue (const API_DatabaseUnId& from)
{
	return GS::GenerateBinaryHashValue (StripDatabaseUnId (from));
}


inline ULong GenerateHashValue (const API_DatabaseInfo& from)
{
	return GS::GenerateBinaryHashValue (StripDatabaseInfo (from));
}


#endif //__DATABASEGRAPH_HPP__
