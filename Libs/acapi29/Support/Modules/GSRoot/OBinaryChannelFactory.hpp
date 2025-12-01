
// *****************************************************************************
//
// Declaration of OBinaryChannelFactory interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELFACTORY_HPP
#define GS_OBINARYCHANNELFACTORY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "OBinaryChannel.hpp"



// --- OBinaryChannelFactory class ---------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT OBinaryChannelFactory {

// Construction / destruction:
protected:
			 OBinaryChannelFactory () = default;
			 OBinaryChannelFactory (const OBinaryChannelFactory&) = default;
public:
	virtual ~OBinaryChannelFactory ();

// Operator overloading:
protected:
	OBinaryChannelFactory&		operator = (const OBinaryChannelFactory&) = default;

// Operations:
public:
	virtual OBinaryChannel*		GetOutputChannel () = 0;

};

typedef Ref<OBinaryChannelFactory, AtomicCounter> OBinaryChannelFactoryRef;

}

#endif // GS_OBINARYCHANNELFACTORY_HPP