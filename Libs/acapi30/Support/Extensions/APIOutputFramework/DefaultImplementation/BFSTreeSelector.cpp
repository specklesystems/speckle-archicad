#include "BFSTreeSelector.hpp"
#include "DatabaseGraph.hpp"

GSAPI::BFSTreeSelector::BFSTreeSelector () :
	onlyDatabasesOnList (false),
	userInputDatabases ()
{
}

GSAPI::BFSTreeSelector::BFSTreeSelector (const GS::Array<API_DatabaseInfo>& userDatabases) :
	onlyDatabasesOnList (true),
	userInputDatabases ()
{
	USize dbCount = userDatabases.GetSize ();
	for (USize i = 0; i < dbCount; i++) {
		userInputDatabases.Add (StripDatabaseInfo (userDatabases[i]), true);
	}
}

GS::Array<API_DatabaseInfo> GSAPI::BFSTreeSelector::operator() (const GSAPI::DatabaseGraphNode* rootNode) const
{
    GS::Array<const GSAPI::DatabaseGraphNode*> bfsQueue;
    Int32                                       index = 0;
    Int32                                       queueSize;

    bfsQueue.Push (rootNode);
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

    GS::Array<API_DatabaseInfo>   bfsDatabases;
    GS::Array<const GSAPI::DatabaseGraphNode*>::Iterator queueIt = bfsQueue.Begin ();
    const GS::Array<const GSAPI::DatabaseGraphNode*>::Iterator queueEnd = bfsQueue.End ();

    for (; queueIt != queueEnd; ++queueIt) {
		if (onlyDatabasesOnList) {
			if (userInputDatabases.ContainsKey (StripDatabaseInfo ((*queueIt)->GetDatabaseInfo ()))) {
				bfsDatabases.Push ((*queueIt)->GetDatabaseInfo ());
			}
		} else {
	        bfsDatabases.Push ((*queueIt)->GetDatabaseInfo ());
		}
    }

    return bfsDatabases;
}
