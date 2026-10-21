// *****************************************************************************
// MPI (Modeler Programming Interface) Add-On interface calling convention
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIINTERFACEBASETYPES_HPP)
#define MPIINTERFACEBASETYPES_HPP

#pragma once

#if defined (WINDOWS)
	#define	MPI_ADD_ON_CALL	__cdecl
#else
	#define	MPI_ADD_ON_CALL
#endif


/////////////////////////////////////////////////////////////////////////////
// Import-export macros

#include "PlatformDLLExport.hpp"

#define MPI_ADD_ON_EXPORT		extern "C" PLATFORM_DLL_EXPORT
inline constexpr short MPIAddOnVersion = 10;

// 6: 2022.02.11 SA v26 RC1

#endif
