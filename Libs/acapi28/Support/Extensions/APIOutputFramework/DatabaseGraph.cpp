#include "APIFunctionsEnvironment.hpp"

// Framework includes
#include "DatabaseGraph.hpp"
#include "IDatabaseSelector.hpp"
#include "DatabaseGraphNode.hpp"
#include "GlobalOperators.hpp"


GSAPI::DatabaseGraph::DatabaseGraph (void) :
	constructed (false)
{
	Construct ();
}

GSAPI::DatabaseGraph::~DatabaseGraph (void)
{
	Clear ();
}


GSAPI::DatabaseGraph& GSAPI::DatabaseGraph::Instance ()
{
	static GSAPI::DatabaseGraph databaseGraph;

	return databaseGraph;
}


void GSAPI::DatabaseGraph::Construct (void)
{
	if (constructed)
		return;

	API_DatabaseInfo savedDatabaseInfo;
	API_DatabaseInfo floorPlanDBInfo;
	BNZeroMemory (&savedDatabaseInfo, sizeof (savedDatabaseInfo));
	BNZeroMemory (&floorPlanDBInfo, sizeof (floorPlanDBInfo));

	GSErrCode dbError = ACAPI_Database_GetCurrentDatabase (&savedDatabaseInfo);
	if (dbError != NoError) {
		// TODO: throw exception
	}
	if (savedDatabaseInfo.typeID == APIWind_FloorPlanID) {
		floorPlanDBInfo = savedDatabaseInfo;
	} else {
		// switch to FloorPlan
		floorPlanDBInfo.typeID = APIWind_FloorPlanID;
		dbError = ACAPI_Database_ChangeCurrentDatabase (&floorPlanDBInfo);
		if (dbError != NoError) {
			// TODO: throw exception
		}

		// Store FloorPlan API_DatabaseInfo
		GSErrCode dbError = ACAPI_Database_GetCurrentDatabase (&floorPlanDBInfo);
		if (dbError != NoError) {
			// TODO: throw exception
		}
	}
	root = new DatabaseGraphNode (StripDatabaseInfo (floorPlanDBInfo));
	BuildDatabaseGraph ();

	// Switch back
	dbError = ACAPI_Database_ChangeCurrentDatabase (&savedDatabaseInfo);
	if (dbError != NoError) {
		// TODO: throw exception
	}

	constructed = true;
}


void GSAPI::DatabaseGraph::BuildDatabaseGraph ()
{
    GS::Array<API_DatabaseInfo> dbList;
    GS::HashTable<API_DatabaseUnId, bool> dependentDetailHash;
    GS::HashTable<API_DatabaseUnId, bool> dependentWorksheetHash;

    dbList.Push (root->GetDatabaseInfo ());

	bool onFloorPlan = true;
    while (!dbList.IsEmpty ()) {
        API_DatabaseInfo currentDB = dbList.Pop ();

		if (!onFloorPlan) {
			GSErrCode changeError = ACAPI_Database_ChangeCurrentDatabase (&currentDB);
			if (changeError != NoError) {
				continue;
			}
		}

        GS::Array<API_DatabaseInfo> currentLinks;
        GetCurrentLinks (API_CutPlaneID, currentLinks);
        GetCurrentLinks (API_ElevationID, currentLinks);
        GetCurrentLinks (API_InteriorElevationID, currentLinks);
        GetCurrentLinks (API_DetailID, currentLinks, &dependentDetailHash);
        GetCurrentLinks (API_WorksheetID, currentLinks, &dependentWorksheetHash);

        GS::Array<API_DatabaseInfo>::Iterator linkIt = currentLinks.Begin ();
        GS::Array<API_DatabaseInfo>::Iterator linksEnd = currentLinks.End ();
        for (; linkIt != linksEnd; ++linkIt) {
            if (!AddLink (currentDB, *linkIt)) {
                dbList.Push (StripDatabaseInfo (*linkIt));
            }
        }

		if (onFloorPlan) {
			onFloorPlan = false;
		}
    }

	// add independent databases under root
	AddIndependentDatabases (APIWind_DetailID, &dependentDetailHash);
	AddIndependentDatabases (APIWind_WorksheetID, &dependentWorksheetHash);
	AddIndependentDatabases (APIWind_LayoutID);
	AddIndependentDatabases (APIWind_MasterLayoutID);
	AddIndependentDatabases (APIWind_DocumentFrom3DID);		// ERR#143134
}


void GSAPI::DatabaseGraph::GetCurrentLinks (API_ElemTypeID typeID,
                                            GS::Array<API_DatabaseInfo>& links,
                                            GS::HashTable<API_DatabaseUnId, bool>* dependentHash /*= nullptr*/)
{
	GS::Array<API_Guid> elemList;
    ACAPI_Element_GetElemList (typeID, &elemList);
	for (GS::Array<API_Guid>::ConstIterator it = elemList.Enumerate (); it != nullptr; ++it) {
        API_Element element;
        element = {};

        element.header.guid = *it;
        GSErrCode getError = ACAPI_Element_Get (&element);
        if (getError == NoError) {
            API_DatabaseInfo dbInfo;
            BNZeroMemory (&dbInfo, sizeof (API_DatabaseInfo));

            switch (typeID) {
                case API_CutPlaneID:	{
											dbInfo.databaseUnId = element.cutPlane.segment.databaseID;
											GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
											if (dbError != NoError) {
												dbInfo.typeID = APIWind_SectionID;
											}
										}
										break;

                case API_ElevationID:	{
											dbInfo.databaseUnId = element.elevation.segment.databaseID;
											GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
											if (dbError != NoError) {
												dbInfo.typeID = APIWind_ElevationID;
											}
										}
										break;

                case API_InteriorElevationID:	{
											API_ElementMemo		memo;
											ACAPI_Element_GetMemo (element.header.guid, &memo, APIMemoMask_SectionSegments);
											if (memo.intElevSegments != nullptr) {
												for (ULong jj = 0; jj < element.interiorElevation.nSegments; jj++) {
													dbInfo.databaseUnId = memo.intElevSegments[jj].databaseID;
													GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
													if (dbError != NoError) {
														dbInfo.typeID = APIWind_InteriorElevationID;
														links.Push (dbInfo);
													}
												}
												ACAPI_DisposeElemMemoHdls (&memo);
												continue;
											}
										}
										break;

				case API_DetailID:		{
                                            dbInfo.databaseUnId = element.detail.databaseID;
											GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
											if (dbError != NoError) {
												dbInfo.typeID = APIWind_DetailID;
											}
											if (dependentHash != nullptr) {
												dependentHash->Put (StripDatabaseUnId (dbInfo.databaseUnId), true);
											}
										}
                                        break;

				case API_WorksheetID:	{
                                            dbInfo.databaseUnId = element.worksheet.databaseID;
											GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
											if (dbError != NoError) {
												dbInfo.typeID = APIWind_WorksheetID;
											}
											if (dependentHash != nullptr) {
												dependentHash->Put (StripDatabaseUnId (dbInfo.databaseUnId), true);
											}
										}
                                        break;

				default:                break;

            }
            links.Push (dbInfo);
        }
    }
}


void GSAPI::DatabaseGraph::AddIndependentDatabases (API_WindowTypeID windowTypeID,
                                                    GS::HashTable<API_DatabaseUnId, bool>* dependentHash /*= nullptr*/)
{
	const GS::Array<API_DatabaseUnId> dbUnIdList = ACAPI_Database_GetDatabasesForType (windowTypeID);
	for (const API_DatabaseUnId id : dbUnIdList) {
		if ((windowTypeID == APIWind_DetailID || windowTypeID == APIWind_WorksheetID) &&
			(dependentHash != nullptr) &&
			(dependentHash->ContainsKey (StripDatabaseUnId (id))))
		{
			continue;
		}

		API_DatabaseInfo dbInfo = {};
		dbInfo.databaseUnId = id;

		GSErrCode dbError = ACAPI_Window_GetDatabaseInfo (&dbInfo);
		if (dbError != NoError) {
			dbInfo.typeID = windowTypeID;
		}
		root->AddChild (new DatabaseGraphNode (StripDatabaseInfo (dbInfo)));
	}
}


bool GSAPI::DatabaseGraph::AddLink (API_DatabaseInfo fromDB, API_DatabaseInfo toDB)
{
    GSAPI::DatabaseGraphNode* fromNode = nullptr;
    GSAPI::DatabaseGraphNode* toNode = nullptr;
    GS::Array<GSAPI::DatabaseGraphNode*> nodeList;

    nodeList.Push (root);
    while ((!nodeList.IsEmpty ()) && ((fromNode == nullptr) || (toNode == nullptr))) {
        GSAPI::DatabaseGraphNode* currentNode = nodeList.Pop ();
        API_DatabaseInfo currentInfo = currentNode->GetDatabaseInfo ();
        if (currentInfo == fromDB) {
            fromNode = currentNode;
        }
        if (currentInfo == toDB) {
            toNode = currentNode;
        }
        const GS::Array<GSAPI::DatabaseGraphNode*>& currentChildren = currentNode->GetChildren ();
        nodeList.Insert (nodeList.GetSize (), currentChildren.Begin (), currentChildren.End ());
    }
    if (fromNode == nullptr) {
        // TODO: throw exception
    }
    if (toNode != nullptr) {
        if (!fromNode->HasChild (toNode)) {
            fromNode->AddChild (toNode);
        }
        return true;
    } else {
        fromNode->AddChild (new GSAPI::DatabaseGraphNode (toDB));
        return false;
    }
}


void GSAPI::DatabaseGraph::Clear (void)
{
	if (!constructed)
		return;

	GS::Array<const GSAPI::DatabaseGraphNode*> bfsQueue;
	UInt32                              index = 0;
	UInt32                              queueSize;

	bfsQueue.Push (root);
	queueSize = bfsQueue.GetSize ();
	while (index < queueSize) {
		const GSAPI::DatabaseGraphNode* currentNode = bfsQueue[index];
		const GS::Array<GSAPI::DatabaseGraphNode*>& children = currentNode->GetChildren ();
		GS::Array<GSAPI::DatabaseGraphNode*>::ConstIterator childIt = children.Begin ();
		const GS::Array<GSAPI::DatabaseGraphNode*>::ConstIterator childrenEnd = children.End ();

		for (; childIt != childrenEnd; ++childIt) {
			if (bfsQueue.FindFirst (*childIt) == MaxUIndex) {
				bfsQueue.Push (*childIt);
			}
		}
		index++;
		queueSize = bfsQueue.GetSize ();
	}

	for (index = 0; index < queueSize; index++) {
		delete (bfsQueue[index]);
	}

	constructed = false;
}


GS::Array<API_DatabaseInfo> GSAPI::DatabaseGraph::SelectDatabases (const GSAPI::IDatabaseSelector& selector) const
{
    return selector (root);
}


GSAPI::DatabaseGraphGuard::DatabaseGraphGuard ()
{
	DatabaseGraph::Instance ().Construct ();
}


GSAPI::DatabaseGraphGuard::~DatabaseGraphGuard ()
{
	DatabaseGraph::Instance ().Clear ();
}