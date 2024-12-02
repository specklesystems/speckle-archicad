// *****************************************************************************
//
//                        IBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNEL_HPP
#define GS_OBINARYCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"ChannelExceptions.hpp"
#include	"Ref.hpp"

namespace GS {

// ============================== Class OBinaryChannel =========================

class GSROOT_DLL_EXPORT OBinaryChannel {
public:
	virtual void		Write (const char* source, USize nOfCharToWrite) = 0;
	virtual void		Flush () = 0;
	virtual void		Close () = 0;

	virtual				~OBinaryChannel ();
};

// ______________________________ Class OBinaryChannel _________________________

typedef Ref<OBinaryChannel, AtomicCounter>	OBinaryChannelRef;

}	// namespace GS


#endif
