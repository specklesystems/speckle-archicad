#ifndef PATTERN_IDENTIFIER_HPP
#define PATTERN_IDENTIFIER_HPP

#pragma once

#include "CADInfrastructureExport.hpp"

#include "ADBAttributeIndex.hpp"

// from GSRoot
#include "HashSet.hpp"


CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_FirstPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_GrayPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_BlackPattern;	/* sm043 100% heccs for Rooms */
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_WhitePattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_SpecGrayPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_LightGrayPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_DarkGrayPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_LastPattern;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	AC_NoPattern;
										  
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Solid;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Dash_6_6;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Dash_1_6;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Dash_5_3;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Dash_12_12;
CADINFRASTRUCTURE_DLL_EXPORT extern const ADB::AttributeIndex	Dash_2_12;

CADINFRASTRUCTURE_DLL_EXPORT const GS::HashSet<ADB::AttributeIndex>&	GetACPatterns ();


#endif // PATTERN_IDENTIFIER_HPP