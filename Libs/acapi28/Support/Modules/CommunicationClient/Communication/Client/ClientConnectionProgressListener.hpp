
// *****************************************************************************
//
// Declaration of ClientConnectionProgressListener interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENER_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"



// --- ClientConnectionProgressListener class ----------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientConnectionProgressListener {

// Construction / destruction:
protected:
			 ClientConnectionProgressListener ();
			 ClientConnectionProgressListener (const ClientConnectionProgressListener&);
public:
	virtual ~ClientConnectionProgressListener ();

// Operator overloading:
protected:
	const ClientConnectionProgressListener&	operator = (const ClientConnectionProgressListener&);

// Operations:
public:
	virtual void							ResponseStarted () = 0;
	virtual void							ResponseProgress (GS::Int64 dataReceived) = 0;
	virtual void							ResponseDone () = 0;

	virtual void							RequestStarted () = 0;
	virtual void							RequestProgress (GS::Int64 dataSent) = 0;
	virtual void							RequestDone () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// ClientConnectionProgressListener inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientConnectionProgressListener::ClientConnectionProgressListener ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientConnectionProgressListener::ClientConnectionProgressListener (const ClientConnectionProgressListener&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientConnectionProgressListener&	ClientConnectionProgressListener::operator = (const ClientConnectionProgressListener&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENER_HPP