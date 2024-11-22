
// *****************************************************************************
//
// Declaration of CountingOBinaryChannel class
//
// Module:			HTTP
// Namespace:		HTTP::Common::Channels
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_COMMON_CHANNELS_COUNTINGOBINARYCHANNEL_HPP
#define HTTP_COMMON_CHANNELS_COUNTINGOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "HTTP/HTTPExport.hpp"

	// from GSRoot
#include "OBinaryChannel.hpp"



// --- CountingOBinaryChannel class --------------------------------------------

namespace HTTP {
namespace Common {
namespace Channels {

class HTTP_API CountingOBinaryChannel : public GS::OBinaryChannel {

// Data members:
private:
	GS::OBinaryChannelRef			m_outputChannelRef;
	GS::OBinaryChannel*				m_outputChannel;
	
	GS::UInt64						m_count;

// Construction / destruction:
public:
	explicit CountingOBinaryChannel (const GS::OBinaryChannelRef& outputChannel);
	explicit CountingOBinaryChannel (GS::OBinaryChannel& outputChannel);
private:
			 CountingOBinaryChannel (const CountingOBinaryChannel&); // Disabled

// Operator overloading:
private:
	const CountingOBinaryChannel&	operator = (const CountingOBinaryChannel&); // Disabled

// Operations:
public:
	GS::UInt64						GetCount () const;
	GS::UInt64						ResetCount ();

// OBinaryChannel interface implementation:
public:
	virtual void					Write (const char* source, GS::USize length) override;
	virtual void					Flush () override;
	virtual void					Close () override;

// Implementation:
private:
	GS::OBinaryChannel&				GetOutputChannel () const;
	GS::OBinaryChannel&				GetOutputChannel ();

};

typedef GS::Ref<CountingOBinaryChannel, GS::AtomicCounter> CountingOBinaryChannelRef;

////////////////////////////////////////////////////////////////////////////////
// CountingOBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingOBinaryChannel::GetCount () const
{
	return m_count;
}

// -----------------------------------------------------------------------------
// ResetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingOBinaryChannel::ResetCount ()
{
	GS::UInt64 count = m_count;
	
	m_count = 0;
	
	return count;
}

}
}
}

#endif // HTTP_COMMON_CHANNELS_COUNTINGOBINARYCHANNEL_HPP