#ifndef __BFSTREESELECTOR_HPP__
#define __BFSTREESELECTOR_HPP__

#include "IDatabaseSelector.hpp"
#include "HashTable.hpp"
#include "GlobalOperators.hpp"

namespace GSAPI {

class BFSTreeSelector : public GSAPI::IDatabaseSelector {
private:
	bool                                  onlyDatabasesOnList;
	GS::HashTable<API_DatabaseInfo, bool> userInputDatabases;

public:
	BFSTreeSelector ();
	BFSTreeSelector (const GS::Array<API_DatabaseInfo>& userDatabases);

	virtual GS::Array<API_DatabaseInfo> operator() (const DatabaseGraphNode* rootNode) const override;
};

}

#endif //__BFSTREESELECTOR_HPP__
