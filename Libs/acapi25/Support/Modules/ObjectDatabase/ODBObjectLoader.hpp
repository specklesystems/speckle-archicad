
// *****************************************************************************
//
//                              Class ObjectLoader
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBOBJECTLOADER_HPP
#define ODBOBJECTLOADER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace ODB { class Object; }
namespace ODB { template <class Type> class Ref; }



// ============================ Class ObjectLoader =============================

namespace ODB {

class ODB_DLL_EXPORT ObjectLoader {
public:
	virtual ~ObjectLoader ();

	virtual bool	LoadObject (const Ref<Object>& object);
};


class ODB_DLL_EXPORT ConstObjectLoader {
public:
	virtual ~ConstObjectLoader ();

	virtual bool	LoadObject (const Ref<Object>& object) const;
};

}	// namespace ODB
// ____________________________ Class ObjectLoader _____________________________


#endif
