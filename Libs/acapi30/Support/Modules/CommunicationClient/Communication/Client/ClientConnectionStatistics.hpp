
// *****************************************************************************
//
// Declaration of ClientConnectionStatistics class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATISTICS_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATISTICS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"



// --- ClientConnectionStatistics class ----------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientConnectionStatistics {

// Data members:
private:
	GS::UInt64		m_messagesReceived;
	GS::UInt64		m_messagesSent;

	GS::UInt64		m_dataReceived;
	GS::UInt64		m_dataSent;

// Construction / destruction:
public:
	explicit ClientConnectionStatistics (
		GS::UInt64 messagesReceived = 0, GS::UInt64 messagesSent = 0,
		GS::UInt64 dataReceived = 0, GS::UInt64 dataSent = 0);

// Operations:
public:
	GS::UInt64		GetMessagesReceived () const;
	GS::UInt64		GetMessagesSent () const;

	GS::UInt64		GetDataReceived () const;
	GS::UInt64		GetDataSent () const;

};

////////////////////////////////////////////////////////////////////////////////
// ClientConnectionStatistics

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetMessagesReceived
// -----------------------------------------------------------------------------

inline GS::UInt64	ClientConnectionStatistics::GetMessagesReceived () const
{
	return m_messagesReceived;
}

// -----------------------------------------------------------------------------
// GetMessagesSent
// -----------------------------------------------------------------------------

inline GS::UInt64	ClientConnectionStatistics::GetMessagesSent () const
{
	return m_messagesSent;
}

// -----------------------------------------------------------------------------
// GetDataReceived
// -----------------------------------------------------------------------------

inline GS::UInt64	ClientConnectionStatistics::GetDataReceived () const
{
	return m_dataReceived;
}

// -----------------------------------------------------------------------------
// GetDataSent
// -----------------------------------------------------------------------------

inline GS::UInt64	ClientConnectionStatistics::GetDataSent () const
{
	return m_dataSent;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATISTICS_HPP