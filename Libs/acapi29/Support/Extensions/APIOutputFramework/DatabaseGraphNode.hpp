#ifndef __DATABASEGRAPHNODE_HPP__
#define __DATABASEGRAPHNODE_HPP__

#include "Array.hpp"
#include "APIdefs_Database.h"

namespace GSAPI {

class DatabaseGraphNode {
private:
    API_DatabaseInfo node;
    GS::Array<DatabaseGraphNode*> children;

public:
    DatabaseGraphNode (API_DatabaseInfo dbInfo);
    virtual ~DatabaseGraphNode (void);

    bool HasChild (DatabaseGraphNode* child);
    void AddChild (DatabaseGraphNode* child);
    const GS::Array<DatabaseGraphNode*>& GetChildren (void) const;
    API_DatabaseInfo GetDatabaseInfo (void) const;
};

}

#endif //__DATABASEGRAPHNODE_HPP__
