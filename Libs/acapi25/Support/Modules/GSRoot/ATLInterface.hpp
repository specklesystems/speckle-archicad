// *****************************************************************************
// File:			ATLInterface.hpp
//
// Description:		Includes ATL Headers
//
// Namespace:		-
//
// Contact person:	MM
//
// SG compatible
// *****************************************************************************

#if !defined (ATLINTERFACE_HPP)
#define	ATLINTERFACE_HPP

#pragma once


// -- Includes -----------------------------------------------------------------

#include "Win32Interface.hpp"

#pragma warning (push)
#pragma warning (disable : 4127 4995)

#include <atlbase.h>
#include <atlcom.h>
#include <atlsecurity.h>

#pragma warning (pop)

#pragma warning (disable: 4995)	// TODO: M-261

#endif
