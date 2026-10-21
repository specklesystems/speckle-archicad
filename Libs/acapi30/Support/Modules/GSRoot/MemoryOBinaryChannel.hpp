// *****************************************************************************
//
//                        MemoryOBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_MEMORYOBINARYOCHANNEL_HPP
#define GS_MEMORYOBINARYOCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"OBinaryChannel.hpp"
#include	"ChannelExceptions.hpp"

namespace GS {

DECLARE_EXCEPTION_CLASS (MemoryOBinaryChannelBufferFullException,  IOException, Error, GSROOT_DLL_EXPORT)

// ============================== Class MemoryOBinaryChannel ===================

class GSROOT_DLL_EXPORT MemoryOBinaryChannel : public OBinaryChannel {
public:
						MemoryOBinaryChannel ();
						MemoryOBinaryChannel (char* buffer, USize capacity, USize used = 0, bool reallocable = false);
	virtual				~MemoryOBinaryChannel ();

	virtual void		Write (const char* source, USize nOfCharsToWrite) override;
	virtual void		Flush () override;
	virtual void		Close () override;

	USize				GetSize ();
	char*				GetBuffer ();
	char*				ReleaseBuffer ();

	void				Reset ();

private:
	void				EnsureCapacity (USize minSize);

	char*				p;
	USize				size;
	USize				capacity;
	bool				reallocable;
	bool				closed;
};


// ______________________________ Class MemoryOBinaryChannel ___________________

}	// namespace GS


#endif
