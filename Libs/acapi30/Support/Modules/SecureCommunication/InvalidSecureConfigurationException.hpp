
// *****************************************************************************
//
// Declaration of Invalid Secure Configuration Exception classes
//
// Module:			InvalidSecureConfigurationException
// Namespace:		InvalidSecureConfigurationException
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SERCURECOMMUNICATION_INVALIDSECURECONFIGURATIONEXCEPTION_HPP
#define SERCURECOMMUNICATION_INVALIDSECURECONFIGURATIONEXCEPTION_HPP

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationException.hpp"


namespace SecureCommunication {

DECLARE_EXCEPTION_CLASS (InvalidSecureConfigurationException, SecureCommunicationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCipherSuiteException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCertificateFileException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCertificateKeyFileException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCertificateChainFileException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCACertificateLocationsException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);
DECLARE_EXCEPTION_CLASS (InvalidCACertificateException, InvalidSecureConfigurationException, GS::Error, SECURECOMMUNICATION_API);

}

#endif
