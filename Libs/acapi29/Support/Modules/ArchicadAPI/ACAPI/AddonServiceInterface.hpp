#ifndef ACAPI_ADDON_SERVICE_INTERFACE_HPP
#define ACAPI_ADDON_SERVICE_INTERFACE_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Result.hpp"

#include "API_Guid.hpp"


namespace ACAPI {


/**
 * @brief AddonServiceInterface is the abstract base class for every concrete service interface class.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT AddonServiceInterface {
protected:
	/**
	 * @brief The error status of the registration.
	 */
	ACAPI::Error	status;

	/**
	 * @brief Identifier given by constructor.
	 */
	const API_Guid	serviceIdentifier;

public:
	/**
	* @brief Creates and registers the AddonServiceInterface.
	* @param serviceIdentifier API guid that identifies the service implementation.
	*/
	AddonServiceInterface (const API_Guid& serviceIdentifier);
	virtual ~AddonServiceInterface () = 0;

	/**
	 * @brief Get the status of the service registration.
	 * @param token The token of the AddOn.
	 * @return The error code and message if there is any, otherwise nothing.
	 */
	Result<void> GetStatus (const API_Token& token) const;

	/**
	 * @brief The callback function for the initialization phase.
	 * @return NoError if everything went well, otherwise the error code.
	 */
	virtual GSErrCode Initialize ();

	/**
	 * @brief The callback function for the interface registration phase.
	 * @return NoError if everything went well, otherwise the error code.
	 */
	virtual GSErrCode RegisterInterface ();
};


} // ACAPI

#endif