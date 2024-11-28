// *****************************************************************************
//
//                        IBinaryChannelUtilites
//
// Module:			GSRoot
// Namespace:		IBinaryChannelUtilites
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELUTILITIES_HPP
#define GS_IBINARYCHANNELUTILITIES_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"

namespace GS {

// --------------------------------- Predeclarations ---------------------------

class IBinaryChannel;
class IChannelX;
class IProtocolX;
class UniString;

// === namespace IBinaryChannelUtilites ========================================

namespace IBinaryChannelUtilities
{

enum StringSerializationType {
	LengthPrefixed,
	ZeroTerminated,
	NotTerminated
};

GSROOT_DLL_EXPORT UInt64 Skip (IBinaryChannel& ch, UInt64 toSkip);
GSROOT_DLL_EXPORT USize ReadFully (IBinaryChannel& ch, char* destination, USize nOfCharsToRead);
GSROOT_DLL_EXPORT UInt64 Skip (IChannelX& ch, UInt64 toSkip);
GSROOT_DLL_EXPORT USize ReadFully (IChannelX& ch, char* destination, USize nOfCharsToRead);

GSROOT_DLL_EXPORT char*			ReadCString (IBinaryChannel& ic, const IProtocolX& protocol, StringSerializationType st);
GSROOT_DLL_EXPORT char*			ReadCString (IChannelX& ic, StringSerializationType st);

GSROOT_DLL_EXPORT GS::UniString ReadUniStringAsUTF8 (IBinaryChannel& ic, const IProtocolX& protocol, StringSerializationType st, bool removeBOM = false, bool requireBOM = false);
GSROOT_DLL_EXPORT GS::UniString ReadUniStringAsUTF8 (IChannelX& ic, StringSerializationType st, bool removeBOM = false, bool requireBOM = false);

}

// ___ namespace IBinaryChannelUtilites ________________________________________

}	// namespace GS


#endif
