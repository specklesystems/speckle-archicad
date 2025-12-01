
// *****************************************************************************
//
// Declaration of NullMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_NULLMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_NULLMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- NullMessageContentIBinaryChannel class ----------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API NullMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	bool								m_closed;

// Construction / destruction:
public:
	NullMessageContentIBinaryChannel ();
	NullMessageContentIBinaryChannel (const NullMessageContentIBinaryChannel&) = delete;

// Operations:
public:
	NullMessageContentIBinaryChannel&	operator = (const NullMessageContentIBinaryChannel&) = delete;

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool						HasMoreContent () const override;
	virtual bool						IsAbortable () const override;
	virtual bool						IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::UInt64					GetAvailable () const override;

	virtual GS::USize					Read (char* destination, GS::USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void						Close () override;

// Implementation:
private:
	void								CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}
}

#endif // COMMUNICATION_CHANNELS_NULLMESSAGECONTENTIBINARYCHANNEL_HPP