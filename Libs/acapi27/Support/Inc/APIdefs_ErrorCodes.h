// *********************************************************************************************************************
// Error codes for the API module
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ERRORCODES_H)
#define APIDEFS_ERRORCODES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"


// --- Constant definitions	--------------------------------------------------------------------------------------------

const Int32 API_ModuleId = 262;
const Int32 APIErrorStart = GS::ErrorFlagMask | (API_ModuleId << 16);


enum APIErrCodes {
	APIERR_GENERAL					= APIErrorStart + 1,
	APIERR_MEMFULL					= APIErrorStart + 2,
	APIERR_CANCEL					= APIErrorStart + 3,

	APIERR_BADID					= APIErrorStart + 101,
	APIERR_BADINDEX					= APIErrorStart + 102,
	APIERR_BADNAME					= APIErrorStart + 103,
	APIERR_BADPARS					= APIErrorStart + 104,
	APIERR_BADPOLY					= APIErrorStart + 105,
	APIERR_BADDATABASE				= APIErrorStart + 106,
	APIERR_BADWINDOW				= APIErrorStart + 107,
	APIERR_BADKEYCODE				= APIErrorStart + 108,
	APIERR_BADPLATFORMSIGN			= APIErrorStart + 109,
	APIERR_BADPLANE					= APIErrorStart + 110,
	APIERR_BADUSERID				= APIErrorStart + 111,
	APIERR_BADVALUE					= APIErrorStart + 112,
	APIERR_BADELEMENTTYPE			= APIErrorStart + 113,
	APIERR_IRREGULARPOLY			= APIErrorStart + 114,
	APIERR_BADEXPRESSION			= APIErrorStart + 115,
	APIERR_BADGUID					= APIErrorStart + 116,
	APIERR_BADTOKEN					= APIErrorStart + 117,

	APIERR_NO3D						= APIErrorStart + 201,
	APIERR_NOMORE					= APIErrorStart + 202,
	APIERR_NOPLAN					= APIErrorStart + 203,
	APIERR_NOLIB					= APIErrorStart + 204,
	APIERR_NOLIBSECT				= APIErrorStart + 205,
	APIERR_NOSEL					= APIErrorStart + 206,
	APIERR_NOTEDITABLE				= APIErrorStart + 207,
	APIERR_NOTSUBTYPEOF				= APIErrorStart + 208,
	APIERR_NOTEQUALMAIN				= APIErrorStart + 209,
	APIERR_NOTEQUALREVISION			= APIErrorStart + 210,
	APIERR_NOTEAMWORKPROJECT		= APIErrorStart + 211,

	APIERR_NOUSERDATA				= APIErrorStart + 220,
	APIERR_MOREUSER					= APIErrorStart + 221,
	APIERR_LINKEXIST				= APIErrorStart + 222,
	APIERR_LINKNOTEXIST				= APIErrorStart + 223,
	APIERR_WINDEXIST				= APIErrorStart + 224,
	APIERR_WINDNOTEXIST				= APIErrorStart + 225,
	APIERR_UNDOEMPTY				= APIErrorStart + 226,
	APIERR_REFERENCEEXIST			= APIErrorStart + 227,
	APIERR_NAMEALREADYUSED			= APIErrorStart + 228,

	APIERR_ATTREXIST				= APIErrorStart + 301,
	APIERR_DELETED					= APIErrorStart + 302,
	APIERR_LOCKEDLAY				= APIErrorStart + 303,
	APIERR_HIDDENLAY				= APIErrorStart + 304,
	APIERR_INVALFLOOR				= APIErrorStart + 305,
	APIERR_NOTMINE					= APIErrorStart + 306,
	APIERR_NOACCESSRIGHT			= APIErrorStart + 307,
	APIERR_BADPROPERTY				= APIErrorStart + 308,
	APIERR_BADCLASSIFICATION		= APIErrorStart + 309,
	APIERR_NOTEXISTINGLAYER			= APIErrorStart + 310,
	APIERR_NOCURRATTRSET			= APIErrorStart + 311,

	APIERR_MODULNOTINSTALLED		= APIErrorStart + 401,
	APIERR_MODULCMDMINE				= APIErrorStart + 402,
	APIERR_MODULCMDNOTSUPPORTED		= APIErrorStart + 403,
	APIERR_MODULCMDVERSNOTSUPPORTED	= APIErrorStart + 404,
	APIERR_NOMODULEDATA				= APIErrorStart + 405,
	APIERR_DEPRECATEDCALL			= APIErrorStart + 406,

	APIERR_PAROVERLAP				= APIErrorStart + 501,
	APIERR_PARMISSING				= APIErrorStart + 502,
	APIERR_PAROVERFLOW				= APIErrorStart + 503,
	APIERR_PARIMPLICIT				= APIErrorStart + 504,

	APIERR_RUNOVERLAP				= APIErrorStart + 510,
	APIERR_RUNMISSING				= APIErrorStart + 511,
	APIERR_RUNOVERFLOW				= APIErrorStart + 512,
	APIERR_RUNIMPLICIT				= APIErrorStart + 513,
	APIERR_RUNPROTECTED				= APIErrorStart + 514,

	APIERR_EOLOVERLAP				= APIErrorStart + 520,

	APIERR_TABOVERLAP				= APIErrorStart + 530,

	APIERR_NOTINIT					= APIErrorStart + 901,
	APIERR_NESTING					= APIErrorStart + 902,
	APIERR_NOTSUPPORTED				= APIErrorStart + 903,
	APIERR_REFUSEDCMD				= APIErrorStart + 904,
	APIERR_REFUSEDPAR				= APIErrorStart + 905,
	APIERR_READONLY					= APIErrorStart + 906,
	APIERR_SERVICEFAILED			= APIErrorStart + 907,
	APIERR_COMMANDFAILED			= APIErrorStart + 908,
	APIERR_NEEDSUNDOSCOPE			= APIErrorStart + 909,
	APIERR_UNDOSCOPEMISUSE			= APIErrorStart + 910,

	APIERR_MISSINGCODE				= APIErrorStart + 1001,
	APIERR_MISSINGDEF				= APIErrorStart + 1002
};


// ---------------------------------------------------------------------------------------------------------------------

#endif
