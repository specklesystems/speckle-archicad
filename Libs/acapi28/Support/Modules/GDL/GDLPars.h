
// **************************************************************************
//
//         PUBLIC HEADER FILE OF THE GDL PARAMETER MANAGER FUNCTIONS
//
//
// Contact person: HK
//
// [somewhat SG compatible]
//
// **************************************************************************


#ifndef GDLPars_H_
#define GDLPars_H_

#pragma once

#include	"RealNumber.h"	//EPS
#include	"comProc.h"		// MessageProc
#include	"GDLExport.h"
#include	"Optional.hpp"
#include	"UniString.hpp"
#include	"Md5.hpp"

namespace GDL
{
class ParameterGetter;
class ParameterAccessor;
class Parameters;
}

class SymbolParametersSectionContent;



#define INVALID_STORAGE_CATEGORY DBBREAK_STR ("Invalid storage type.")


GDL_DLL_EXPORT
bool GDLIsIntType (short tp);

GDL_DLL_EXPORT
bool GDLIsNumType (short tp);

GDL_DLL_EXPORT
bool GDLIsStringType (short tp);

GDL_DLL_EXPORT
bool GDLIsDictType (short tp);

GDL_DLL_EXPORT
bool GDLIsAttrIndType (short tp);

GDL_DLL_EXPORT
bool GDLIsPenIndType (short tp);



// **************************************************************************
//
//                        Check consistency of variable handle
//
// **************************************************************************
//
// Useful when variable handles are read in from file, network or uncertain sources. That's why it is not even the
// handle that is passed, but instead the variables' starting position in memory and the memory length.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
bool GDLIsAddParPtrCorrect (const char* addParPtr, Int32 varHdlSize);
// ---------------------------------------------------------------------------
//	Arguments:
//		vars:		starting position of memory buffer containing variables.
//		sz:			length of memory buffer containing variables.
//
//	Return value:
//		true if consistency test is passed, false if failed.


// **************************************************************************
//
//                         Swap parameter handle
//
// **************************************************************************
//
// Swap the platform of the given parameter handle.
// --------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr GDLSwapAddParHdl (GS::PlatformSign inplatform, GSHandle addParHdl, short version, GS::PlatformSign toplatform);
// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:	the parameter handle,
//		version:	version number of the parameter handle,
//		platform:	the new platform.


// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:	the parameter handle,
//		width:		the A parameter. There are old versions of the handle which do not contain this parameter.
//					It can be given with this parameter,
//		height:		the B parameter. There are old versions of the handle which do not contain this parameter.
//					It can be given with this parameter,
//		version:	version number of the old parameter handle,


// **************************************************************************
//
//             Compare types of parameter handles without the values
//
// **************************************************************************
//
// Compare two parameter handles.
// --------------------------------------------------------------------------
GDL_DLL_EXPORT
bool GDLCompareAddParHdls (const GDL::ParameterGetter& defAddParHdl, GDL::ParameterAccessor& oldAddParHdl, bool* modifOldPar);
// --------------------------------------------------------------------------
// Arguments:
//		defAddParHdl:	the default handle,
//		oldAddParHdl:	the original handle, this contains the original parameters.
//	Return argument:
//		modifOldPar:	if the original handle came from old file it will be modified,
//						this parameter shows it.
//	Return value:		true if the handles are the same.


// **************************************************************************
//
//           		Calc the checksum of a parameter handle
//
// **************************************************************************
//
// Calcs the checksum of a parameter handle.
// --------------------------------------------------------------------------
enum class CheckSumMode {
	SkipScriptControlledParamFlags,
	IncludeScriptControlledParamFlags
};

GDL_DLL_EXPORT
Int32 GDLCalcInt32CheckSumAddParHdl (const GDL::ParameterGetter& addParHdl,
									 CheckSumMode checkSumMode = CheckSumMode::SkipScriptControlledParamFlags);
GDL_DLL_EXPORT
MD5::FingerPrint GDLCalcMD5CheckSumAddParHdl (const GDL::ParameterGetter& addParHdl,
											  GS::Optional<double>		  discretizationEps = EPS,
											  CheckSumMode checkSumMode = CheckSumMode::SkipScriptControlledParamFlags);


// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:		the parameter handle
//		sumVars:		if it is not nullptr, the summarized numeric values
//	Return value:		the checksum.


// **************************************************************************
//
//           Compare two parameters of two handles; name, type and value must be the same
//
// **************************************************************************
//
// --------------------------------------------------------------------------

GDL_DLL_EXPORT
bool GDLEqualAddParEntries (const GDL::ParameterGetter& addParPtr_1,
							const Int32					parIndex_1,
							const GDL::ParameterGetter& addParPtr_2,
							const Int32					parIndex_2,
							const double				eps = EPS);

// --------------------------------------------------------------------------
// Arguments:
//		addParHdl_1 and addParHdl_2 : the two parameter handles
//		parIndex_1 and parIndex_2 :   the index of corresponding parameters to be compared
//		eps :						  is used to compare real numbers
//	Return value:		true if the two parameters are equal.


// **************************************************************************
//
//           Compare parameter handles with the values of parameters
//
// **************************************************************************
//
// Compare two parameter handles.
// --------------------------------------------------------------------------

GDL_DLL_EXPORT
bool GDLEqualAddPars (const GDL::ParameterGetter& defAddParHdl, const GDL::ParameterGetter& actAddParHdl);

// --------------------------------------------------------------------------
// Arguments:
//		defAddParHdl,
//		actAddParHdl:	the two parameter handles
//	Return value:		true if the handles are equal.


// **************************************************************************
//
//                            Merge parameter handles
//
// **************************************************************************
//
// Merges two parameter handles and makes a new one.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr GDLMergeAddParHdls (const GDL::Parameters& defAddParHdl, const GDL::Parameters& oldAddParHdl, GDL::Parameters& newAddParHdl);


enum class MergeAddParHdlsToCurrentResult {
	UseDefault,
	UseNew
};

GDL_DLL_EXPORT
MergeAddParHdlsToCurrentResult GDLMergeAddParHdlsToCurrentCreate (const GDL::ParameterGetter& defAddParHdl,
																  const GDL::ParameterGetter& oldAddParHdl,
																  GDL::Parameters&			  newAddParHdl);

GDL_DLL_EXPORT
GSErr GDLOverrideExistingParHdl (const GDL::ParameterGetter& oldAddParHdl,
								 const GDL::ParameterGetter& overrideAddParHdl,
								 GDL::Parameters&			 newAddParHdl);

// ---------------------------------------------------------------------------
// Arguments:
//		defAddParHdl:	the default parameter handle,
//		oldAddParHdl:	the original handle, this contains the original parameters.
//	Return value:
//		Error if memory error


// **************************************************************************
//
//                 Append parameters to an existing other handle
//
// **************************************************************************
//
// Appends parameters to an existing handle only if it does not already contain
// them.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr GDLAppendDiffVars (const GDL::ParameterGetter& oldParams, GDL::Parameters& newParams);
// ---------------------------------------------------------------------------
//	Arguments:
//		oldParams:  the parameters to append
//		newParams:	the new parameters, containing as a result the appended values from
//					oldParams
//	Return value:
//		Error if memory error


#endif
