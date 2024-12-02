
// *****************************************************************************
//
// Declaration of MemoryMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- MemoryMessageContentIBinaryChannel class --------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API MemoryMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Type definitions:
public:
	enum BufferOwnership {
		PassBufferOwnership,
		KeepBufferOwnership
	};

// Data members:
private:
	BufferOwnership							m_bufferOwnership;
	const char*								m_buffer;

	GS::UInt32								m_position;
	GS::USize								m_size;

	bool									m_closed;

// Construction / destruction:
public:
			 MemoryMessageContentIBinaryChannel (const char* buffer, GS::USize size, BufferOwnership bufferOwnership = PassBufferOwnership);
			 MemoryMessageContentIBinaryChannel (const MemoryMessageContentIBinaryChannel&) = delete;
	virtual ~MemoryMessageContentIBinaryChannel ();

// Operator overloading:
public:
	MemoryMessageContentIBinaryChannel&		operator = (const MemoryMessageContentIBinaryChannel&) = delete;

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool							HasMoreContent () const override;
	
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

	virtual GS::UInt64						GetAvailable () const override;

	virtual GS::USize						Read (char* target, GS::USize targetSize, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void							Close () override;

// Implementation:
private:
	void									CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}
}

#endif // COMMUNICATION_CHANNELS_MEMORYMESSAGECONTENTIBINARYCHANNEL_HPP