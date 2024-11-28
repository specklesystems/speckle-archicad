
// *****************************************************************************
//
// Declaration of ProgressOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_PROGRESSOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_PROGRESSOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Channels/ProgressListener.hpp"

	// from GSRoot
#include "OBinaryChannel.hpp"



// --- ProgressOBinaryChannel class --------------------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API ProgressOBinaryChannel : public GS::OBinaryChannel {

// Data members:
private:
	GS::OBinaryChannelRef		m_outputChannelRef;
	GS::OBinaryChannel*			m_outputChannel;
	ProgressListener*			m_progressListener;
	GS::UInt64					m_progress;

// Construction / destruction:
public:
	ProgressOBinaryChannel (const GS::OBinaryChannelRef& outputChannel, ProgressListener* progressListener);
	ProgressOBinaryChannel (GS::OBinaryChannel& outputChannel, ProgressListener* progressListener);
	ProgressOBinaryChannel (const ProgressOBinaryChannel&) = delete;

// Operator overloading:
public:
	ProgressOBinaryChannel&		operator = (const ProgressOBinaryChannel&) = delete;

// OBinaryChannel interface implementation:
public:
	virtual void				Write (const char* source, GS::USize length) override;
	
	virtual void				Flush () override;
	virtual void				Close () override;

// Implementation:
private:
	GS::OBinaryChannel&			GetOutputChannel () const;
	GS::OBinaryChannel&			GetOutputChannel ();

	void						UpdateProgress (GS::UInt64 progress);

};

}
}

#endif // COMMUNICATION_CHANNELS_PROGRESSOBINARYCHANNEL_HPP