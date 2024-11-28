// *****************************************************************************
// File:			Win32CommunicationPlusInterface.hpp
//
// Description:		Includes Communication Related Windows Headers
//
// Namespace:		-
//
// Contact person:	MM
//
// SG compatible
// *****************************************************************************

#if !defined (WIN32COMMUNICATIONINTERFACE_HPP)
#define	WIN32COMMUNICATIONINTERFACE_HPP

#pragma once


// -- Includes -----------------------------------------------------------------

#include "Win32Interface.hpp"

#pragma warning (push)
#pragma warning (disable : 4995)

#include <wininet.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>

#include <Iptypes.h>
#include <IPExport.h>
#include <IcmpAPI.h>
#include <Iphlpapi.h>


#pragma warning (pop)

#endif
