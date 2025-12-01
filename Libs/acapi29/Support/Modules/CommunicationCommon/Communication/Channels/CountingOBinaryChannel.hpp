
// *****************************************************************************
//
// Declaration of CountingOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_COUNTINGOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_COUNTINGOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "OBinaryChannel.hpp"



// --- CountingOBinaryChannel class --------------------------------------------

namespace Communication {
namespace Channels {
	
class COMMUNICATIONCOMMON_API CountingOBinaryChannel : public GS::OBinaryChannel {

// Data members:
private:
	GS::OBinaryChannelRef		m_outputChannelRef;
	GS::OBinaryChannel*			m_outputChannel;

	GS::UInt64					m_count;

// Construction / destruction:
public:
	explicit CountingOBinaryChannel (const GS::OBinaryChannelRef& outputChannel);
	explicit CountingOBinaryChannel (GS::OBinaryChannel& outputChannel);
			 CountingOBinaryChannel (const CountingOBinaryChannel&) = delete;

// Operator overloading:
public:
	CountingOBinaryChannel&		operator = (const CountingOBinaryChannel&) = delete;

// Operations:
public:
	GS::UInt64					GetCount () const;
	GS::UInt64					ResetCount ();

// OBinaryChannel interface implementation:
public:
	virtual void				Write (const char* source, GS::USize length) override;
	
	virtual void				Flush () override;
	virtual void				Close () override;

// Implementation:
private:
	GS::OBinaryChannel&			GetOutputChannel () const;
	GS::OBinaryChannel&			GetOutputChannel ();

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

#endif // COMMUNICATION_CHANNELS_COUNTINGOBINARYCHANNEL_HPP