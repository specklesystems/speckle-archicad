// *****************************************************************************
//
//                        BufferedIBinaryChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_BUFFEREDIBINARYCHANNEL_HPP
#define GS_BUFFEREDIBINARYCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"FilterIBinaryChannel.hpp"
 #include	<string.h>

namespace GS {

// ============================== Class BufferedIBinaryChannel =================

class GSROOT_DLL_EXPORT BufferedIBinaryChannel : public FilterIBinaryChannel {
public:
						BufferedIBinaryChannel (IBinaryChannel& ic, USize buffCapacity = 1024UL);
						BufferedIBinaryChannel (const IBinaryChannelRef& ic, USize buffCapacity = 1024UL);
	virtual				~BufferedIBinaryChannel ();

	virtual USize		Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;
	virtual UInt64		GetAvailable () const override;
	virtual void		Close () override;

	inline USize		FastRead (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode);
	inline void			FastRead (char* destination, USize nOfCharToRead, ReadAllModeSelector readAllMode = ReadAllMode);

protected:
	const char*			GetBufferStart () const						{ return buffStart; }
	USize				GetBytesInBuffer () const					{ return TruncateTo32Bit (buffEnd - buffStart); }
	void				IncreaseBufferStart (USize bytes)			{ buffStart += bytes; }
	bool				HasInBuffer (USize bytes) const				{ return USize(buffEnd - buffStart) >= bytes; }

private:
								BufferedIBinaryChannel (const BufferedIBinaryChannel& source);	// disabled
	BufferedIBinaryChannel&	operator= (const BufferedIBinaryChannel& source);				// disabled

	USize					buffCapacity;
	char*					buffer;
	const char*				buffStart;
	const char*				buffEnd;

};


inline USize		BufferedIBinaryChannel::FastRead (char* destination, USize nOfCharToRead, ReadSomeModeSelector /*readSomeMode = ReadSomeMode*/)
{
	if (GetBytesInBuffer () > 0) {
		USize tocopy = GS::Min (GetBytesInBuffer (), nOfCharToRead);
		memcpy (destination, GetBufferStart (), tocopy);
		IncreaseBufferStart (tocopy);
		return tocopy;
	} else {
		return Read (destination, nOfCharToRead, ReadSomeMode);
	}
}


inline void		BufferedIBinaryChannel::FastRead (char* destination, USize nOfCharToRead, ReadAllModeSelector /*readAllMode = ReadAllMode*/)
{
	if (GetBytesInBuffer () >= nOfCharToRead) {
		memcpy (destination, GetBufferStart (), nOfCharToRead);
		IncreaseBufferStart (nOfCharToRead);
	} else {
		IBinaryChannel::Read (destination, nOfCharToRead, ReadAllMode);
	}
}



// ______________________________ Class IBinaryChannel _________________________

}	// namespace GS


#endif
