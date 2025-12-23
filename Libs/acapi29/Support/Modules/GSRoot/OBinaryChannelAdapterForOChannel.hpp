// *****************************************************************************
//
//                        OBinaryChannelAdapterForOChannel
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	FM
//
// SG compatible
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELADAPTERFOROCHANNEL_HPP
#define GS_OBINARYCHANNELADAPTERFOROCHANNEL_HPP

// --------------------------------- Includes ----------------------------------

#include	"Definitions.hpp"
#include	"GSException.hpp"
#include	"OBinaryChannel.hpp"

namespace GS {

// --------------------------------- Predeclarations ---------------------------

class AtomicCounter;
class OChannel;
template<typename T, typename CounterT>				class CountedPtr;
typedef CountedPtr<OChannel, AtomicCounter>			OChannelRef;

// ============================== Class OBinaryChannelAdapterForOChannel =======

class GSROOT_DLL_EXPORT OBinaryChannelAdapterForOChannel : public OBinaryChannel {
public:
						OBinaryChannelAdapterForOChannel (OChannel& ic);
						OBinaryChannelAdapterForOChannel (const OChannelRef& ic);

	virtual				~OBinaryChannelAdapterForOChannel ();

	virtual void		Write (const char* source, USize nOfCharToWrite) override;
	virtual void		Flush () override;
	virtual void		Close () override;

	OChannel&				GetBaseChannel ()		{ PRECOND_R_DEPRECATED(adaptee);  return *adaptee; }
	const OChannel&			GetBaseChannel () const { PRECOND_R_DEPRECATED(adaptee);  return *adaptee; }
private:
											OBinaryChannelAdapterForOChannel (const OBinaryChannelAdapterForOChannel& source);	// disabled
		OBinaryChannelAdapterForOChannel&	operator= (const OBinaryChannelAdapterForOChannel& source);							// disabled

	OChannel*			adaptee;
	OChannelRef*		adapteeRef;
};

// ___________ Class OBinaryChannelAdapterForOChannel __________________________

}	// namespace GS


#endif
