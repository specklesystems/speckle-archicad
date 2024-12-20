
// *****************************************************************************
//
// Declaration of ProgressIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_PROGRESSIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_PROGRESSIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Channels/ProgressListener.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"



// --- ProgressIBInaryChannel class --------------------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API ProgressIBinaryChannel : public GS::IBinaryChannel {

// Data members:
private:
	GS::IBinaryChannelRef			m_inputChannelRef;
	GS::IBinaryChannel*				m_inputChannel;
	ProgressListener*				m_progressListener;
	GS::UInt64						m_progress;

// Construction / destruction:
public:
	ProgressIBinaryChannel (const GS::IBinaryChannelRef& inputChannel, ProgressListener* progressListener);
	ProgressIBinaryChannel (GS::IBinaryChannel& inputChannel, ProgressListener* progressListener);
private:
	ProgressIBinaryChannel (const ProgressIBinaryChannel&); // Disabled

// Operator overloading:
private:
	const ProgressIBinaryChannel&	operator = (const ProgressIBinaryChannel&); // Disabled

// IBinaryChannel interface implementation:
public:
	virtual GS::USize				Read (char* buffer, GS::USize size, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual GS::UInt64				GetAvailable () const override;
	virtual void					Close () override;

// Implementation:
private:
	GS::IBinaryChannel&				GetInputChannel () const;
	GS::IBinaryChannel&				GetInputChannel ();

	void							UpdateProgress (GS::Int64 progress);

};

}
}

#endif // COMMUNICATION_CHANNELS_PROGRESSIBINARYCHANNEL_HPP