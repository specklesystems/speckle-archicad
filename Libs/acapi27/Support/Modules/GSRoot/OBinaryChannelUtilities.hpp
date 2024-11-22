// *****************************************************************************
//
//                        OBinaryChannelUtilites
//
// Module:			GSRoot
// Namespace:		OBinaryChannelUtilites
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELUTILITIES_HPP
#define GS_OBINARYCHANNELUTILITIES_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"

namespace GS {

// --------------------------------- Predeclarations ---------------------------

class OBinaryChannel;
class OChannelX;
class OProtocolX;
class UniString;

// === namespace OBinaryChannelUtilities =======================================

namespace OBinaryChannelUtilities
{

enum StringSerializationType {
	LengthPrefixed,
	ZeroTerminated,
	NotTerminated
};

GSROOT_DLL_EXPORT void WriteCString (OBinaryChannel& oc, const OProtocolX& protocol, const char* str, StringSerializationType st);
GSROOT_DLL_EXPORT void WriteCString (OChannelX& oc, const char* str, StringSerializationType st);

GSROOT_DLL_EXPORT void WriteUniStringAsUTF8 (OBinaryChannel& oc, const OProtocolX& protocol, const GS::UniString& str, StringSerializationType st, bool writeBOM = false);
GSROOT_DLL_EXPORT void WriteUniStringAsUTF8 (OChannelX& oc, const GS::UniString& str, StringSerializationType st, bool writeBOM = false);

}

// ___ namespace OBinaryChannelUtilities _______________________________________

}	// namespace GS


#endif
