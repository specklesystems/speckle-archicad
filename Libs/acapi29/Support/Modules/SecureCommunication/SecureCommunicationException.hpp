
// *****************************************************************************
//
// Declaration of Secure Communication Exception class
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SERCURECOMMUNICATION_SERCURECOMMUNICATIONEXCEPTION_HPP
#define SERCURECOMMUNICATION_SERCURECOMMUNICATIONEXCEPTION_HPP

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationExport.hpp"

#include "GSException.hpp"
#include "Ref.hpp"


namespace SecureCommunication {
	
typedef GS::Ref<GS::Exception, GS::AtomicCounter> GSExceptionRef;

class SECURECOMMUNICATION_API SecureCommunicationException : public GS::GeneralException {

public:
	SecureCommunicationException (const GS::UniString& msg, const char* sourceFile, UInt32 sourceLine, const GS::Exception& cause = GS::NoCauseException);
	SecureCommunicationException (const GS::UniString& msg, const char* sourceFile, UInt32 sourceLine, const GSExceptionRef& cause);

protected:
	SecureCommunicationException ();

public:
	virtual const char*		GetName () const override;
	virtual GS::Exception*	Clone () const override;

};

typedef GS::Ref<SecureCommunicationException, GS::AtomicCounter> SecureCommunicationExceptionRef;

class SECURECOMMUNICATION_API SecureCommunicationHandshakeException : public SecureCommunicationException {

private:
	GS::UInt32	m_errorCode;

public:
	SecureCommunicationHandshakeException (const GS::UniString& msg, GS::UInt32	errorCode, const char* sourceFile, UInt32 sourceLine, const GS::Exception& cause = GS::NoCauseException);
	SecureCommunicationHandshakeException (const GS::UniString& msg, GS::UInt32	errorCode, const char* sourceFile, UInt32 sourceLine, const GSExceptionRef& cause);

public:
	virtual const char*		GetName () const override;
	virtual GS::Exception*	Clone () const override;

	GS::UInt32				GetErrorCode () const;

};

typedef GS::Ref<SecureCommunicationHandshakeException, GS::AtomicCounter> SecureCommunicationHandshakeExceptionRef;

}

#endif
