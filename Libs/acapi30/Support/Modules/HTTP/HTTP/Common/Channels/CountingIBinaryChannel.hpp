
// *****************************************************************************
//
// Declaration of CountingIBinaryChannel class
//
// Module:			HTTP
// Namespace:		HTTP::Common::Channels
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_COMMON_CHANNELS_COUNTINGIBINARYCHANNEL_HPP
#define HTTP_COMMON_CHANNELS_COUNTINGIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "HTTP/HTTPExport.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"



// --- CountingIBinaryChannel class --------------------------------------------

namespace HTTP {
namespace Common {
namespace Channels {

class HTTP_API CountingIBinaryChannel : public GS::IBinaryChannel {

// Data members:
private:
	GS::IBinaryChannelRef			m_inputChannelRef;
	GS::IBinaryChannel*				m_inputChannel;

	GS::UInt64						m_count;

// Construction / destruction:
public:
	explicit CountingIBinaryChannel (const GS::IBinaryChannelRef& inputChannel);
	explicit CountingIBinaryChannel (GS::IBinaryChannel& inputChannel);
private:
			 CountingIBinaryChannel (const CountingIBinaryChannel&); // Disabled

// Operator overloading:
private:
	const CountingIBinaryChannel&	operator = (const CountingIBinaryChannel&); // Disabled

// Operations:
public:
	GS::UInt64						GetCount () const;
	GS::UInt64						ResetCount ();

// IBinaryChannel interface implementation:
public:
	virtual GS::USize				Read (char* destination, GS::USize length, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual GS::UInt64				GetAvailable () const override;
	virtual void					Close () override;

// Implementation:
private:
	GS::IBinaryChannel&				GetInputChannel () const;
	GS::IBinaryChannel&				GetInputChannel ();

};

typedef GS::Ref<CountingIBinaryChannel, GS::AtomicCounter> CountingIBinaryChannelRef;

////////////////////////////////////////////////////////////////////////////////
// CountingIBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingIBinaryChannel::GetCount () const
{
	return m_count;
}

// -----------------------------------------------------------------------------
// ResetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingIBinaryChannel::ResetCount ()
{
	GS::UInt64 count = m_count;

	m_count = 0;

	return count;
}

}
}
}

#endif // HTTP_COMMON_CHANNELS_COUNTINGIBINARYCHANNEL_HPP
