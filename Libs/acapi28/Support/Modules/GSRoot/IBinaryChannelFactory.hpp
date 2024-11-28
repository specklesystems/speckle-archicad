
// *****************************************************************************
//
// Declaration of IBinaryChannelFactory interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELFACTORY_HPP
#define GS_IBINARYCHANNELFACTORY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannel.hpp"



// --- IBinaryChannelFactory class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT IBinaryChannelFactory {

// Construction / destruction:
protected:
			 IBinaryChannelFactory () = default;
			 IBinaryChannelFactory (const IBinaryChannelFactory&) = default;
public:
	virtual ~IBinaryChannelFactory ();

// Operator overloading:
public:
	IBinaryChannelFactory&		operator = (const IBinaryChannelFactory&) = default;

// Operations:
public:
	virtual IBinaryChannel*		GetInputChannel () const = 0;

};

typedef Ref<IBinaryChannelFactory, AtomicCounter> IBinaryChannelFactoryRef;

}

#endif // GS_IBINARYCHANNELFACTORY_HPP