// *****************************************************************************
//
//                        ChunkedIBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_CHUNKYIBINARYSUBCHANNEL_HPP
#define GS_CHUNKYIBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"IBinarySubChannel.hpp"
#include	"IProtocolX.hpp"
#include	"IOBinProtocolXs.hpp"


namespace GS {

class IChannelX;

// === Class ChunkedIBinarySubChannel ==========================================

class GSROOT_DLL_EXPORT ChunkedIBinarySubChannel : public IBinarySubChannel {
public:
						ChunkedIBinarySubChannel (IBinaryChannel&			ic, const IProtocolX& protocol = GetBinIProtocolX ());
						ChunkedIBinarySubChannel (IChannelX& icx);
						ChunkedIBinarySubChannel (const IBinaryChannelRef&	icr, const IProtocolX& protocol = GetBinIProtocolX ());
	virtual				~ChunkedIBinarySubChannel ();

	virtual USize			Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;
	virtual UInt64			GetAvailable () const override;
	virtual void			Close () override;

	bool					IsEOI () const;

private:
	void						ReadBlockHeader ();
	void						ReadSize ();

	ChunkedIBinarySubChannel (const ChunkedIBinarySubChannel& source);	// disabled
	ChunkedIBinarySubChannel&	operator= (const ChunkedIBinarySubChannel& source);					// disabled

	const IProtocolX&		protocol;
	Int32					actBlockRemaining;
};


// ___ Class ChunkedIBinarySubChannel ___________________________________________

}	// namespace Communication


#endif
