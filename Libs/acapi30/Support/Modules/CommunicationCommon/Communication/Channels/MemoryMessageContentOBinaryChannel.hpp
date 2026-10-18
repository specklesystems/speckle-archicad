
// *****************************************************************************
//
// Declaration of MemoryMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- MemoryMessageContentOBinaryChannel class --------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API MemoryMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	char*									m_buffer;

	GS::USize								m_capacity;
	GS::USize								m_size;

	bool									m_closed;

// Construction / destruction:
public:
	explicit MemoryMessageContentOBinaryChannel (GS::USize initialCapacity = 0);
			 MemoryMessageContentOBinaryChannel (const MemoryMessageContentOBinaryChannel&) = delete;
	virtual ~MemoryMessageContentOBinaryChannel ();

// Operator overloading:
public:
	MemoryMessageContentOBinaryChannel&		operator = (const MemoryMessageContentOBinaryChannel&) = delete;

// Operations:
public:
	const char*								GetBuffer () const;
	GS::USize								GetSize () const;

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

	virtual void							Abort (const GS::UniString& message) override;
	virtual void							Abort () override;

	virtual void							Write (const char* source, USize nOfCharToWrite) override;
	
	virtual void							Flush () override;
	
	virtual void							Close () override;

// Implementation:
private:
	void									CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

	void									EnsureCapacity (GS::USize minimumCapacity);

};

////////////////////////////////////////////////////////////////////////////////
// MemoryMessageContentOBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetBuffer
// -----------------------------------------------------------------------------

inline const char*	MemoryMessageContentOBinaryChannel::GetBuffer () const
{
	return m_buffer;
}

// -----------------------------------------------------------------------------
// GetSize
// -----------------------------------------------------------------------------
	
inline GS::USize	MemoryMessageContentOBinaryChannel::GetSize () const
{
	return m_size;
}

}
}

#endif // COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTOBINARYCHANNEL_HPP