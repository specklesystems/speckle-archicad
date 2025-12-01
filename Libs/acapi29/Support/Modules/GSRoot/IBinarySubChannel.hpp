// *****************************************************************************
//
//                        IBinarySubChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_IBINARYSUBCHANNEL_HPP
#define GS_IBINARYSUBCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

	// from GSRoot
#include	"Definitions.hpp"
#include	"FilterIBinaryChannel.hpp"


namespace GS {

// === Class SubChannelIBinaryChannel ==========================================

class GSROOT_DLL_EXPORT IBinarySubChannel : public FilterIBinaryChannel {
public:
						IBinarySubChannel (IBinaryChannel&			ic);
						IBinarySubChannel (const IBinaryChannelRef&	icr);
	virtual				~IBinarySubChannel ();

	virtual USize			Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode /*= ReadSomeMode*/) override = 0;
	virtual UInt64			GetAvailable () const override = 0;
	virtual void			Close () override = 0;

private:
						IBinarySubChannel (const IBinarySubChannel& source);	// disabled
	IBinarySubChannel&	operator= (const IBinarySubChannel& source);			// disabled
};


// ___ Class IBinarySubChannel _________________________________________________

}	// namespace GS


#endif
