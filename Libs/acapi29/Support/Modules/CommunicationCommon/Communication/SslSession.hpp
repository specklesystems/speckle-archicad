
// *****************************************************************************
//
// Declaration of SslSession class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_SSLSESSION_HPP
#define COMMUNICATION_SSLSESSION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "Ref.hpp"


// --- ServerSslSession class --------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API SslSession {

// Data members:
private:
	UInt32					m_verifyResult;

// Construction / destruction:
protected:
			 SslSession ();
public:
	virtual ~SslSession ();

// Operations:
public:
	UInt32		GetVerifyResult () const;
	void 		SetVerifyResult (UInt32 verifyResult);

};

typedef GS::Ref<SslSession, GS::Counter> SslSessionRef;

}

#endif // COMMUNICATION_SSLSESSION_HPP