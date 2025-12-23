#include "APIFunctionsEnvironment.hpp"

// Framework includes
#include "DatabaseGraphNode.hpp"

GSAPI::DatabaseGraphNode::DatabaseGraphNode (API_DatabaseInfo dbInfo)
{
    node = dbInfo;
}

GSAPI::DatabaseGraphNode::~DatabaseGraphNode (void)
{
}

bool GSAPI::DatabaseGraphNode::HasChild (DatabaseGraphNode* child)
{
    return (children.FindFirst (child) != MaxUIndex);
}

void GSAPI::DatabaseGraphNode::AddChild (GSAPI::DatabaseGraphNode* child)
{
    children.Push (child);
}

const GS::Array<GSAPI::DatabaseGraphNode*>& GSAPI::DatabaseGraphNode::GetChildren (void) const
{
    return children;
}

API_DatabaseInfo GSAPI::DatabaseGraphNode::GetDatabaseInfo (void) const
{
    return node;
}
