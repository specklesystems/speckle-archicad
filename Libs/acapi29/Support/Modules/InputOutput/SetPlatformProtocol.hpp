
// *****************************************************************************
//
//                       SetPlatformIProtocol, SetPlatformOProtocol
//
// Module: IO
// Namespace: IO
// Contact person: FM
//
// SG compatible
//
// *****************************************************************************


#if !defined GS_SETPLATFORMPROTOCOL_HPP
#define GS_SETPLATFORMPROTOCOL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

// from GSRoot
#include "Definitions.hpp"

// from InputOutput
#include "IOBase.hpp"

// ============================ Class SetPlatformIOProtocol ====================

namespace IO {

IO_DLL_EXPORT GSErrCode SetPlatformIProtocol (GS::IChannel& ch, GS::PlatformSign fromPlatform);
IO_DLL_EXPORT GSErrCode SetPlatformOProtocol (GS::OChannel& ch, GS::PlatformSign toPlatform);

IO_DLL_EXPORT GSErrCode SetNetworkByteOrderIProtocol (GS::IChannel& ch, GS::PlatformSign fromPlatform);
IO_DLL_EXPORT GSErrCode SetNetworkByteOrderOProtocol (GS::OChannel& ch, GS::PlatformSign toPlatform);

IO_DLL_EXPORT GSErrCode GetChannelIProtocolPlatform (GS::IChannel& ch, GS::PlatformSign* fromPlatform);
IO_DLL_EXPORT GSErrCode GetChannelOProtocolPlatform (GS::OChannel& ch, GS::PlatformSign* fromPlatform);

class IO_DLL_EXPORT PlatformIProtocolScope {
private:
	GS::IChannel&  ch;
	GS::IProtocol& oldInputProtocol;

	// no copy
	PlatformIProtocolScope (const PlatformIProtocolScope& src);
	PlatformIProtocolScope& operator= (const PlatformIProtocolScope& src);

public:
	PlatformIProtocolScope (GS::IChannel& ch, GS::PlatformSign fromPlatform);
	~ PlatformIProtocolScope ();
};

class IO_DLL_EXPORT PlatformOProtocolScope {
private:
	GS::OChannel&  ch;
	GS::OProtocol& oldOutputProtocol;

	// no copy
	PlatformOProtocolScope (const PlatformOProtocolScope& src);
	PlatformOProtocolScope& operator= (const PlatformOProtocolScope& src);

public:
	PlatformOProtocolScope (GS::OChannel& ch, GS::PlatformSign toPlatform);
	~ PlatformOProtocolScope ();
};

}	// namespace IO

// ____________________________ Class SetPlatformIOProtocol ____________________


#endif
