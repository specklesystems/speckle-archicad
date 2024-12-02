#if !defined (_IDXFTESTOBJECT_HPP_)
#define	_IDXFTESTOBJECT_HPP_

// from TeighaForDWG
#include "GSPreTeighaForDWGInclude.hpp"
#include "DbDatabase.h"
#include "GSPostTeighaForDWGInclude.hpp"

namespace OD {

class IDXFTestObject {
public:
	IDXFTestObject	();
	virtual ~IDXFTestObject	();

	void SetOdDbDatabase (const OdDbDatabasePtr db);

	virtual void CheckOdDbDatabase ();

protected:
	OdDbDatabasePtr db;
};


}	// namespace OD

#endif //_IDXFTESTOBJECT_HPP_
