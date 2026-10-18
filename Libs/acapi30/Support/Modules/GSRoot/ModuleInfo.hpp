// *****************************************************************************
// File:			ModuleInfo.hpp
//
// Description:		ModuleInfo class
//
// Project:			GSRoot
//
// Namespace:		GS
//
// Contact person:	SzA
//
// *****************************************************************************

#ifndef MODULEINFO_HPP
#define MODULEINFO_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Array.hpp"
#include "UniString.hpp"


namespace GS {


// --- ModuleInfo class declaration -------------------------------------------------

class GSROOT_DLL_EXPORT ModuleInfo
{
public:

		// Definitions

	typedef struct moduleInfoStructure {
		UniString	moduleName;
		UniString	versionString;
		Int32		buildNumber;
		bool		isOurModule;
	} ModuleInfoStructure;

private:
	Array <ModuleInfoStructure>		moduleInfoArr;

	void	CollectModuleInfo ();

public:

		// Constructors

	ModuleInfo ();

		// Content query

	UInt32					NumberOfSharedLibraries ();
	ModuleInfoStructure		Get (UInt32 index);

};


}	// namespace GS

#endif
