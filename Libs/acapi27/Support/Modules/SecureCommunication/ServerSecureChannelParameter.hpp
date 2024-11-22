
// *****************************************************************************
//
// Declaration of ServerSecureChannelParameter structure
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Server
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_SERVERSECURECHANNELPARAMETER_HPP
#define SECURECOMMUNICATION_SERVERSECURECHANNELPARAMETER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationExport.hpp"

#include "Ref.hpp"
#include "UniString.hpp"


namespace SecureCommunication {
namespace Server {

class Verification {

public:
	enum Verify {
		None = 0x01,
		Peer = 0x02,
		VerifyFailIfNoPeerCert = 0x04,
		VerifyClientOnce = 0x08
	};

};

class ServerMethod {

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

class SECURECOMMUNICATION_API ServerSecureChannelParameter {

private:
	
	ServerMethod::Method	m_method;
	UInt32					m_disabledMethods;

	UInt32					m_verification;
	UInt32					m_verifyDepth;

	GS::UniString			m_cipherSuite;
	bool					m_serverCipherPreference;

	GS::UniString			m_encryptedFilePassword;

	GS::UniString			m_certificateFile;
	GS::UniString			m_certificateKeyFile;
	GS::UniString			m_certificateChainFile;

	GS::UniString			m_caCertificatePath;
	GS::UniString			m_caCertificateFile;

public:
	ServerSecureChannelParameter ();
	~ServerSecureChannelParameter ();

public:
	ServerMethod::Method	GetMethod () const;
	void 					SetMethod (ServerMethod::Method method);
	UInt32					GetDisabledMethods () const;
	void 					SetDisabledMethods (UInt32 disabledMethods);

	UInt32					GetVerification () const;
	void					SetVerification (UInt32 verification);
	UInt32					GetVerifyDepth () const;
	void					SetVerifyDepth (UInt32 verifyDepth);

	GS::UniString			GetCipherSuite () const;
	void					SetCipherSuite (const GS::UniString& cipherSuite);
	bool					GetServerCipherPreference () const;
	void					SetServerCipherPreference (bool serverCipherPreference);

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

};

typedef GS::Ref<ServerSecureChannelParameter, GS::AtomicCounter> ServerSecureChannelParameterRef;

}
}

#endif
