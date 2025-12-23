// *****************************************************************************
//
//                        ChunkedOBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_CHUNKEDOBINARYSUBCHANNEL_HPP
#define GS_CHUNKEDOBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"OBinarySubChannel.hpp"
#include	"OProtocolX.hpp"
#include	"MemoryOBinaryChannel.hpp"
#include	"IOBinProtocolXs.hpp"
#include	"Owner.hpp"


namespace GS {

class OChannelX;

// === Class ChunkedOBinarySubChannel ==========================================
// SubChannel that splitted to blocks. Data is not kept in memory

class GSROOT_DLL_EXPORT ChunkedOBinarySubChannel : public OBinarySubChannel {
public:
						ChunkedOBinarySubChannel (OBinaryChannel&			oc, const OProtocolX& protocol = GetBinOProtocolX (), USize maxBlockSize = 1024UL);
						ChunkedOBinarySubChannel (const OBinaryChannelRef&	ocr, const OProtocolX& protocol = GetBinOProtocolX (), USize maxBlockSize = 1024UL);
						ChunkedOBinarySubChannel (OChannelX&			ocx, USize maxBlockSize = 1024UL);
	virtual				~ChunkedOBinarySubChannel ();

	virtual void		Write (const char* source, USize nOfCharToWrite) override;
	virtual void		Flush () override;
	virtual void		Close () override;

private:
									ChunkedOBinarySubChannel (const ChunkedOBinarySubChannel& source);	// disabled
	ChunkedOBinarySubChannel&		operator= (const ChunkedOBinarySubChannel& source);					// disabled

	void				WriteBlockDataIfNeeded ();
	void				WriteBlockData ();

	const OProtocolX&	protocol;
	Owner<char[]>		buffer;
	USize				bufferCapacity;
	USize				bufferSize;
	bool				closed;
};


// ___ Class ChunkedOBinarySubChannel __________________________________________

}	// namespace GS


#endif
