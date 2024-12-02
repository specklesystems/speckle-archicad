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

#ifndef GS_IBINARYCHANNEL_HPP
#define GS_IBINARYCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"ChannelExceptions.hpp"
#include	"Ref.hpp"

namespace GS {

// ------------------------------ Class ReadSome/ReadAllMode	----------------

enum ReadSomeModeSelector {
	ReadSomeMode
};

enum ReadAllModeSelector {
	ReadAllMode
};

// ============================== Class IBinaryChannel =========================

class GSROOT_DLL_EXPORT IBinaryChannel {
public:
	virtual void		Read (char* destination, USize nOfCharToRead, ReadAllModeSelector readAllMode) CAN_THROW((GS::EndOfInputException, GS::UnexpectedEndOfInputDataIntegrityException, GS::Exception));
	virtual USize		Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode) CAN_THROW((GS::Exception)) = 0;
	virtual UInt64		GetAvailable () const CAN_THROW((GS::Exception)) = 0;
	virtual void		Close () CAN_THROW((GS::Exception)) = 0;


	virtual				~IBinaryChannel () CAN_THROW_NOTHING;
};

typedef Ref<IBinaryChannel, AtomicCounter>	IBinaryChannelRef;

// ______________________________ Class IBinaryChannel _________________________

}	// namespace GS


#endif
