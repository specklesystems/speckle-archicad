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

#include "ChannelExceptions.hpp"
#include "Ref.hpp"

#include <cstddef>


namespace GS {

// ============================== Class OBinaryChannel =========================

class GSROOT_DLL_EXPORT OBinaryChannel {
public:
	void				Write (const std::byte* source, USize byteCount);
	virtual void		Write (const char* source, USize nOfCharToWrite) = 0;
	virtual void		Flush () = 0;
	virtual void		Close () = 0;

	virtual				~OBinaryChannel ();
};


inline void OBinaryChannel::Write (const std::byte* source, USize byteCount)
{
	Write (reinterpret_cast<const char*> (source), byteCount);
}


// ______________________________ Class OBinaryChannel _________________________

typedef Ref<OBinaryChannel, AtomicCounter>	OBinaryChannelRef;

}	// namespace GS


#endif
