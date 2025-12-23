
// *****************************************************************************
//
// Declaration of SslContext class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef COMMUNICATION_SSLCONTEXT_HPP
#define COMMUNICATION_SSLCONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "Ref.hpp"
#include "UniString.hpp"


// --- SslContext class ----------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API SslMethod {

public:
	enum Method {
		SSLv2 = 0x01,
		SSLv3 = 0x02,
		SSLv23 = 0x04,
		TLSv1 = 0x08,
		TLSv1_1 = 0x10,
		TLSv1_2 = 0x20,
		TLSv1_3 = 0x40
	};
};


class COMMUNICATIONCOMMON_API SslContext {

// Data members:
private:
	SslMethod::Method		m_method;
	UInt32					m_disabledMethods;

	UInt32					m_verifyDepth;

	GS::UniString			m_cipherSuite;

	GS::UniString			m_encryptedFilePassword;

	GS::UniString			m_certificateFile;
	GS::UniString			m_certificateKeyFile;
	GS::UniString			m_certificateChainFile;

	GS::UniString			m_caCertificatePath;
	GS::UniString			m_caCertificateFile;
	GS::UniString			m_caCertificate;

// Construction / destruction:
protected:
			 SslContext (Communication::SslMethod::Method method, UInt32 defaultDisabledMethod);
public:
	virtual ~SslContext ();

// Operations:
public:
	SslMethod::Method		GetMethod () const;
	void 					SetMethod (SslMethod::Method method);
	UInt32					GetDisabledMethods () const;
	void 					SetDisabledMethods (UInt32 disabledMethods);

	UInt32					GetVerifyDepth () const;
	void					SetVerifyDepth (UInt32 verifyDepth);

	GS::UniString			GetCipherSuite () const;
	void					SetCipherSuite (const GS::UniString& cipherSuite);

	GS::UniString			GetEncryptedFilePassword () const;
	void					SetEncryptedFilePassword (const GS::UniString& password);

	GS::UniString			GetCertificateFile () const;
	void					SetCertificateFile (const GS::UniString& certificateFile);
	GS::UniString			GetCertificateKeyFile () const;
	void					SetCertificateKeyFile (const GS::UniString& certificateKeyFile);

	GS::UniString			GetCertificateChainFile () const;
	void					SetCertificateChainFile (const GS::UniString& certificateChainFile);
	GS::UniString			GetCACertificatePath () const;
	void					SetCACertificatePath (const GS::UniString& caCertificatePath);
	GS::UniString			GetCACertificateFile () const;
	void					SetCACertificateFile (const GS::UniString& caCertificateFile);
	GS::UniString			GetCACertificate () const;
	void					SetCACertificate (const GS::UniString& caCertificate);

};

typedef GS::Ref<SslContext, GS::Counter> SslContextRef;

}

#endif // COMMUNICATION_SSLCONTEXT_HPP