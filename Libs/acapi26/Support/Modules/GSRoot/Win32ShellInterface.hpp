// *****************************************************************************
// File:			Win32ShellInterface.hpp
//
// Description:		Includes Windows Shell  Headers
//
// Namespace:		-
//
// Contact person:	MM
//
// SG compatible
// *****************************************************************************

#if !defined (WIN32SHELLINTERFACE_HPP)
#define	WIN32SHELLINTERFACE_HPP

#pragma once


// -- Includes -----------------------------------------------------------------

#include "Win32Interface.hpp"

#pragma warning (push)
#pragma warning (disable : 4995 4091)

#include <shellapi.h>
#include <shobjidl.h>
#include <Shlwapi.h>
#include <ShlGuid.h>
#include <ShlObj.h>

#pragma warning (pop)

#endif
