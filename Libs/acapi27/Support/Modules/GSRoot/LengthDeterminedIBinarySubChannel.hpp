// *****************************************************************************
//
//                        LengthDeterminedIBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_LENGTHDETERMINEDIBINARYSUBCHANNEL_HPP
#define GS_LENGTHDETERMINEDIBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"IBinarySubChannel.hpp"
#include	"IProtocolX.hpp"
#include	"IOBinProtocolXs.hpp"


namespace GS {

class IChannelX;

// === Class LengthDeterminedIBinarySubChannel ==========================================

class GSROOT_DLL_EXPORT LengthDeterminedIBinarySubChannel : public IBinarySubChannel {
public:
						LengthDeterminedIBinarySubChannel (IBinaryChannel&	ic, const IProtocolX& protocol = GetBinIProtocolX ());
						LengthDeterminedIBinarySubChannel (IChannelX&	icx);
						LengthDeterminedIBinarySubChannel (const IBinaryChannelRef&	icr, const IProtocolX& protocol = GetBinIProtocolX ());
	virtual				~LengthDeterminedIBinarySubChannel ();

	virtual USize			Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode /*= ReadSomeMode*/) override;
	virtual UInt64			GetAvailable () const override;
	virtual void			Close () override;

	bool					IsEOI () const;

private:
	void					ReadSize ();

										LengthDeterminedIBinarySubChannel (const LengthDeterminedIBinarySubChannel& source);	// disabled
	LengthDeterminedIBinarySubChannel&	operator= (const LengthDeterminedIBinarySubChannel& source);							// disabled

	const IProtocolX&		protocol;
	UInt64					size;
	UInt64					readed;
};


// ___ Class LengthDeterinedIBinarySubChannel _________________________________________________

}	// namespace Communication


#endif
