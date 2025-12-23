// *****************************************************************************
//
//                        IBinaryChannelAdapterForIChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELADAPTERFORICHANNEL_HPP
#define GS_IBINARYCHANNELADAPTERFORICHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"GSException.hpp"
#include	"IBinaryChannel.hpp"

namespace GS {

class IChannel;

// --------------------------------- Predeclarations ---------------------------

class AtomicCounter;
template<typename T, typename CounterT>				class CountedPtr;
typedef CountedPtr<IChannel, AtomicCounter>			IChannelRef;

// ============================== Class IBinaryChannelAdapterForIChannel =======

class GSROOT_DLL_EXPORT IBinaryChannelAdapterForIChannel : public IBinaryChannel {
public:
						IBinaryChannelAdapterForIChannel (IChannel& ic);
						IBinaryChannelAdapterForIChannel (const IChannelRef& ic);
	virtual USize		Read (char* destination, USize nOfCharToRead, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;
	virtual UInt64		GetAvailable () const override;
	virtual void		Close () override;

	virtual				~IBinaryChannelAdapterForIChannel ();
private:
private:
											IBinaryChannelAdapterForIChannel (const IBinaryChannelAdapterForIChannel& source);	// disabled
		IBinaryChannelAdapterForIChannel&	operator= (const IBinaryChannelAdapterForIChannel& source);							// disabled

	IChannel*			adaptee;
	IChannelRef*		adapteeRef;
};


// ______________________________ Class IBinaryChannel _________________________

}	// namespace GS


#endif
