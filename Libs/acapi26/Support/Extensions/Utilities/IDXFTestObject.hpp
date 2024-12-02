#if !defined (_IDXFTESTOBJECT_HPP_)
#define	_IDXFTESTOBJECT_HPP_

class OdDbDatabase;

namespace OD {

class IDXFTestObject {
public:
	IDXFTestObject	();
	virtual ~IDXFTestObject	();

	virtual void CheckOdDB (const OdDbDatabase* db) = 0;
};


}	// namespace OD

#endif //_IDXFTESTOBJECT_HPP_
