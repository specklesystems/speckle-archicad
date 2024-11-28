
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
	bool										m_closed;

// Construction / destruction:
public:
	NullMessageContentIBinaryChannel ();
private:
	NullMessageContentIBinaryChannel (const NullMessageContentIBinaryChannel&); // Disabled

// Operations:
private:
	const NullMessageContentIBinaryChannel&		operator = (const NullMessageContentIBinaryChannel&); // Disabled

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool								HasMoreContent () const override;
	virtual bool								IsAbortable () const override;
	virtual bool								IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::USize							Read (char* destination, GS::USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual GS::UInt64							GetAvailable () const override;
	virtual void								Close () override;

// Implementation:
private:
	void										CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}
}

#endif // COMMUNICATION_CHANNELS_NULLMESSAGECONTENTIBINARYCHANNEL_HPP