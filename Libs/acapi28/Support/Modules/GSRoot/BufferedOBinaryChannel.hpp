// *****************************************************************************
//
//                        BufferedOBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_BUFFEREDOBINARYCHANNEL_HPP
#define GS_BUFFEREDOBINARYCHANNEL_HPP

// --- Includes ----------------------------------------------------------------

#include	"Definitions.hpp"
#include	"FilterOBinaryChannel.hpp"

namespace GS {

// === Class BufferedOBinaryChannel ============================================

class GSROOT_DLL_EXPORT BufferedOBinaryChannel : public FilterOBinaryChannel {
public:
	static const USize DefaultBufferSize = 1024L;

						BufferedOBinaryChannel (OBinaryChannel& oc, USize buffCapacity = DefaultBufferSize);
						BufferedOBinaryChannel (const OBinaryChannelRef& ocr, USize buffCapacity = DefaultBufferSize);
	virtual				~BufferedOBinaryChannel ();

	virtual void		Write (const char* source, USize nOfCharsToWrite) override;
	virtual void		Flush () override;
	virtual void		Close () override;

private:
			void			FlushBuffer ();
			inline void		EnsureOpened ();
			void			FreeBuffers (); // noexcept

	USize					bufferCapacity;
	char*					buffer;
	USize					bufferSize;
};


// ___ Class BufferedOBinaryChannel ____________________________________________

}	// namespace GS


#endif
