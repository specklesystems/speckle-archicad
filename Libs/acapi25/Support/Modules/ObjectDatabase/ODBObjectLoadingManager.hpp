
// *****************************************************************************
//
//                          Class ObjectLoadingManager
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBOBJECTLOADINGMANAGER_HPP
#define ODBOBJECTLOADINGMANAGER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBObjectLoader.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace ODB { class Id; }
namespace ODB { class IdSpace; }



// ======================== Class ObjectLoadingManager =========================

namespace ODB {

class ODB_DLL_EXPORT ObjectLoadingManager {
private:
	class LoadablesTable;

	LoadablesTable* loadables;	// stores loadable-loader pairs

	ObjectLoadingManager ();

	ObjectLoadingManager (const ObjectLoadingManager& source);				// disabled
	ObjectLoadingManager&	operator= (const ObjectLoadingManager& source);	// disabled

public:
	static ObjectLoadingManager	singleton;	// don't use this instance directly!

	virtual ~ObjectLoadingManager ();

	bool	Register   (Ref<Object> loadable, Ref<Object> loader);
	bool	Unregister (Ref<Object> loadable);

		// Module private methods

#ifdef ODB_MODULE_PRIVATE

	bool	LoadObject (const Id& id, IdSpace* idSpace);

#endif
};


ODB_DLL_EXPORT extern ObjectLoadingManager&	objectLoadingManager;	// single global ObjectLoadingManager instance

}	// namespace ODB
// ________________________ Class ObjectLoadingManager _________________________


#endif
