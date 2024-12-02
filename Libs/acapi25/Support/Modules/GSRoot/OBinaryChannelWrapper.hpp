
// *****************************************************************************
//
// Declaration of OBinaryChannelWrapper class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELWRAPPER_HPP
#define GS_OBINARYCHANNELWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FilterOBinaryChannel.hpp"



// --- OBinaryChannelWrapper class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT OBinaryChannelWrapper : public FilterOBinaryChannel {

// Construction / destruction:
public:
	explicit OBinaryChannelWrapper (const OBinaryChannelRef& outputChannel);
	explicit OBinaryChannelWrapper (OBinaryChannel& outputChannel);
			 OBinaryChannelWrapper (const OBinaryChannelWrapper&) = delete;
    virtual ~OBinaryChannelWrapper ();

// Operator overloading:
public:
	OBinaryChannelWrapper&	operator = (const OBinaryChannelWrapper&) = delete;

};

}

#endif // GS_OBINARYCHANNELWRAPPER_HPP