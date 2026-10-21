#ifndef __IDATABASESELECTOR_HPP__
#define __IDATABASESELECTOR_HPP__

#include "DatabaseGraphNode.hpp"

namespace GSAPI {

/** @interface */
class IDatabaseSelector {
public:
	virtual	~IDatabaseSelector ();
    virtual GS::Array<API_DatabaseInfo> operator() (const DatabaseGraphNode* rootNode) const = 0;
};

}

#endif //__IDATABASESELECTOR_HPP__
