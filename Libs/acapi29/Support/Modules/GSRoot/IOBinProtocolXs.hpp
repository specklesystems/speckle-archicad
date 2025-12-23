// *****************************************************************************
//
//                        IOBinProtocolXs
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_IOBINPROTOCOLX_HPP
#define GS_IOBINPROTOCOLX_HPP

// --------------------------------- Includes ----------------------------------

#include	"GSRootExport.hpp"
#include	"Definitions.hpp"

namespace GS {

class IProtocolX;
class OProtocolX;

// === IProtocol's =============================================================

GSROOT_DLL_EXPORT const IProtocolX&		GetBinIProtocolX ();
GSROOT_DLL_EXPORT const IProtocolX&		GetNetworkByteOrderIProtocolX ();
GSROOT_DLL_EXPORT const IProtocolX&		GetPlatformIProtocolX (PlatformSign in);

// === OProtocol's =============================================================

GSROOT_DLL_EXPORT const OProtocolX&		GetBinOProtocolX ();
GSROOT_DLL_EXPORT const OProtocolX&		GetNetworkByteOrderOProtocolX ();
GSROOT_DLL_EXPORT const OProtocolX&		GetPlatformOProtocolX (PlatformSign out);

}	// namespace GS


#endif
