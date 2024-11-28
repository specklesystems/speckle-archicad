
// *****************************************************************************
//
// Declaration of CountingIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_COUNTINGIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_COUNTINGIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"



// --- CountingIBinaryChannel class --------------------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API CountingIBinaryChannel : public GS::IBinaryChannel {

// Data members:
private:
	GS::IBinaryChannelRef		m_inputChannelRef;
	GS::IBinaryChannel*			m_inputChannel;

	GS::UInt64					m_count;

// Construction / destruction:
public:
	explicit CountingIBinaryChannel (const GS::IBinaryChannelRef& inputChannel);
	explicit CountingIBinaryChannel (GS::IBinaryChannel& inputChannel);
			 CountingIBinaryChannel (const CountingIBinaryChannel&) = delete;

// Operator overloading:
public:
	CountingIBinaryChannel&		operator = (const CountingIBinaryChannel&) = delete;

// Operations:
public:
	GS::UInt64					GetCount () const;
	GS::UInt64					ResetCount ();

// IBinaryChannel interface implementation:
public:
	virtual GS::UInt64			GetAvailable () const override;

	virtual GS::USize			Read (char* target, GS::USize targetSize, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void				Close () override;

// Implementation:
private:
	GS::IBinaryChannel&			GetInputChannel () const;
	GS::IBinaryChannel&			GetInputChannel ();

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
	const GS::UInt64 count = m_count;

	m_count = 0;

	return count;
}

}
}

#endif // COMMUNICATION_CHANNELS_COUNTINGIBINARYCHANNEL_HPP