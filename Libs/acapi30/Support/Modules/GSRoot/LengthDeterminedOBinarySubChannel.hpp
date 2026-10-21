// *****************************************************************************
//
//                        LengthDeterminedOBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_LENGTHDETERMINEDOBINARYSUBCHANNEL_HPP
#define GS_LENGTHDETERMINEDOBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"OBinarySubChannel.hpp"
#include	"OProtocolX.hpp"
#include	"MemoryOBinaryChannel.hpp"
#include	"IOBinProtocolXs.hpp"


namespace GS {

class OChannelX;

// === Class LengthDeterminedOBinarySubChannel =================================

class GSROOT_DLL_EXPORT LengthDeterminedOBinarySubChannel : public OBinarySubChannel {
public:
						LengthDeterminedOBinarySubChannel (OChannelX&	ocx);
						LengthDeterminedOBinarySubChannel (OBinaryChannel&			oc, const OProtocolX& protocol = GetBinOProtocolX ());
						LengthDeterminedOBinarySubChannel (const OBinaryChannelRef&	ocr, const OProtocolX& protocol = GetBinOProtocolX ());
	virtual				~LengthDeterminedOBinarySubChannel ();

	virtual void		Write (const char* source, USize nOfCharToWrite) override;
	virtual void		Flush () override;
	virtual void		Close () override;

private:
											LengthDeterminedOBinarySubChannel (const LengthDeterminedOBinarySubChannel& source);	// disabled
	LengthDeterminedOBinarySubChannel&		operator= (const LengthDeterminedOBinarySubChannel& source);			// disabled

	MemoryOBinaryChannel	buffer;
	const OProtocolX&		protocol;
	bool					closed;
};


// ___ Class LengthDeterminedOBinarySubChannel _________________________________

}	// namespace GS


#endif
