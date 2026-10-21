
// *****************************************************************************
//
// Declaration of NullMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_NULLMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_NULLMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- NullMessageContentOBinaryChannel class ----------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API NullMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	bool								m_closed;

// Construction / destruction:
public:
	NullMessageContentOBinaryChannel ();
	NullMessageContentOBinaryChannel (const NullMessageContentOBinaryChannel&) = delete;

// Operator overloading:
public:
	NullMessageContentOBinaryChannel&	operator = (const NullMessageContentOBinaryChannel&) = delete;

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool						IsAbortable () const override;
	virtual bool						IsAborted () const override;

	virtual void						Abort (const GS::UniString& message) override;
	virtual void						Abort () override;

// OBinaryChannel interface implementation:
public:
	virtual void						Write (const char* source, USize nOfCharToWrite) override;
	
	virtual void						Flush () override;
	virtual void						Close () override; 

// Implementation:
private:
	void								CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}
}

#endif // COMMUNICATION_CHANNELS_NULLMESSAGECONTENTOBINARYCHANNEL_HPP