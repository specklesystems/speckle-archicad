
// *****************************************************************************
//
//                  Definitions for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBDEFINITIONS_HPP
#define ODBDEFINITIONS_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"
#include "GSRoot.hpp"


// -----------------------------------------------------------------------------

#if defined (OBJECTDATABASE_DLL_COMPILE)
	#define ODB_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define ODB_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif


#ifdef GS_BUILD_CTC
#define ODB_COVERAGE_TEST
#endif


#define ODB_FORCE_INLINE GS_FORCE_INLINE
#define ODB_NO_INLINE	 GS_NO_INLINE


#ifdef ODB_COVERAGE_TEST
#pragma warning (disable: 4702)
#pragma warning (disable: 4189)
#pragma warning (disable: 4390)
#pragma warning (disable: 4100)
#endif // ODB_COVERAGE_TEST


namespace ODB {

enum FilterMode {
	Include,
	Exclude
};

} // namespace ODB

#endif
