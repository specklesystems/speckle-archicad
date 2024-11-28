
// *****************************************************************************
//
//	                  Asserts for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
//
// *****************************************************************************


#ifndef ODBASSERT_HPP
#define ODBASSERT_HPP

// --------------------------------- Includes ----------------------------------

#include "GSAssert.hpp"
#include "ODBDefinitions.hpp"


// -----------------------------------------------------------------------------

#define ODBTASSERT				GSTASSERT
#define ODBTASSERT_R			GSTASSERT_R
#define ODBTASSERT_RNULL		GSTASSERT_RNULL
#define ODBTASSERT_F			GSTASSERT_F
#define ODBTASSERT_FAILED		GSTASSERT_FAILED

#define	ODBTASSERT_NOERROR		GSTASSERT_NOERROR
#define	ODBTASSERT_NOERROR_R	GSTASSERT_NOERROR_R
#define ODBTASSERT_NOERROR_R2	GSTASSERT_NOERROR_R2

#define	ODBTRETURN_ON_ERROR		GSTRETURN_ON_ERROR
#define	ODBTRETURN_ON_ERROR_R2	GSTRETURN_ON_ERROR_R2

#define ODBASSERT				GSASSERT
#define ODBASSERT_R				GSASSERT_R
#define ODBASSERT_RNULL			GSASSERT_RNULL
#define ODBASSERT_F				GSASSERT_F
#define ODBASSERT_FAILED		GSASSERT_FAILED

#define	ODBASSERT_NOERROR		GSASSERT_NOERROR
#define	ODBASSERT_NOERROR_R		GSASSERT_NOERROR_R
#define	ODBASSERT_NOERROR_R2	GSASSERT_NOERROR_R2

#define	ODBRETURN_ON_ERROR		GSRETURN_ON_ERROR
#define	ODBRETURN_ON_ERROR_R2	GSRETURN_ON_ERROR_R2

#define ODBWASSERT				GSTWASSERT
#define ODBWASSERT_R			GSTWASSERT_R
#define ODBWASSERT_RNULL		GSTWASSERT_RNULL
#define ODBWASSERT_F			GSTWASSERT_F
#define ODBWASSERT_FAILED		GSTWASSERT_FAILED

#define DEFINE_ODBAssertLogLine		static GS::ErrorLogLine		AssertErrorLogLine		("ODB error assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), ODB::ModuleName, "Assert");
#define DEFINE_ODBWAssertLogLine	static GS::WarningLogLine	AssertWarningLogLine	("ODB warning assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), ODB::ModuleName, "Assert");


namespace ODB {

ODB_DLL_EXPORT extern const char* ModuleName;

ODB_DLL_EXPORT void		EnableAssert	();
ODB_DLL_EXPORT void		DisableAssert   ();
ODB_DLL_EXPORT bool		IsAssertEnabled ();

ODB_DLL_EXPORT bool		IsAssertFailed  ();
ODB_DLL_EXPORT UInt32	GetAssertFailureCount	  ();
ODB_DLL_EXPORT void		ClearAssertFailureCounter ();

ODB_DLL_EXPORT void		AssertionFailed ();
ODB_DLL_EXPORT void		UnimplementedMethodError ();

} // namespace ODB

#endif // ODBASSERT_HPP
