
// *****************************************************************************
//
// Declaration of IBinaryChannelWrapper class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELWRAPPER_HPP
#define GS_IBINARYCHANNELWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FilterIBinaryChannel.hpp"



// --- IBinaryChannelWrapper class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT IBinaryChannelWrapper : public FilterIBinaryChannel {

// Construction / destruction:
public:
	explicit IBinaryChannelWrapper (const IBinaryChannelRef& inputChannel);
	explicit IBinaryChannelWrapper (IBinaryChannel& inputChannel);
			 IBinaryChannelWrapper (const IBinaryChannelWrapper&) = delete;
    virtual ~IBinaryChannelWrapper ();
	
// Operator overloading:
public:
	IBinaryChannelWrapper&	operator = (const IBinaryChannelWrapper&) = delete;

};

}

#endif // GS_IBINARYCHANNELWRAPPER_HPP