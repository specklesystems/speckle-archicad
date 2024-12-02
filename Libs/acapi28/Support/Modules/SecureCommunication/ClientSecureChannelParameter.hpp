
// *****************************************************************************
//
// Declaration of ClientSecureChannelParameter structure
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_CLIENTSECURECHANNELPARAMETER_HPP
#define SECURECOMMUNICATION_CLIENTSECURECHANNELPARAMETER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationExport.hpp"

#include "Ref.hpp"
#include "UniString.hpp"


namespace SecureCommunication {
namespace Client {

class Verification {

public:
	enum Verify {
		None = 0x01,
		Peer = 0x02
	};

};

class ClientMethod {

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

class SECURECOMMUNICATION_API ClientSecureChannelParameter {

private:
	ClientMethod::Method	m_method;
	UInt32					m_disabledMethods;

	Verification::Verify	m_verification;
	UInt32					m_verifyDepth;

	GS::UniString			m_cipherSuite;

	GS::UniString			m_encryptedFilePassword;

	GS::UniString			m_certificateFile;
	GS::UniString			m_certificateKeyFile;
	GS::UniString			m_certificateChainFile;

	GS::UniString			m_caCertificatePath;
	GS::UniString			m_caCertificateFile;
	GS::UniString			m_caCertificate;

	GS::UniString			m_serverName;

public:
	ClientSecureChannelParameter ();
	~ClientSecureChannelParameter ();

public:
	ClientMethod::Method	GetMethod () const;
	void 					SetMethod (ClientMethod::Method method);
	UInt32					GetDisabledMethods () const;
	void 					SetDisabledMethods (UInt32 disabledMethods);

	Verification::Verify	GetVerification () const;
	void					SetVerification (Verification::Verify verification);
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

	void					SetServerName (const GS::UniString& serverName);
	const GS::UniString&	GetServerName () const;
	bool					HasServerName () const;

};

typedef GS::Ref<ClientSecureChannelParameter, GS::AtomicCounter> ClientSecureChannelParameterRef;

}
}

#endif
