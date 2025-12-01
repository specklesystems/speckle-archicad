#ifndef GS_ACAPI_ADDONNOTIFICATIONINTERFACE_HPP
#define GS_ACAPI_ADDONNOTIFICATIONINTERFACE_HPP


// from ARCHICADAPI
#include "API_Guid.hpp"
#include "ACAPI/ArchicadAPIExport.hpp"


namespace ACAPI {


/**
 * @brief AddonNotificationInterface is the abstract base class for every concrete notification interface class.
 * @ingroup APIInfrastructure
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT AddonNotificationInterface {
protected:
	/**
	 * @brief Identifier given by constructor.
	 */
	const API_Guid	notificationIdentifier;

public:
	/**
	* @brief Creates and registers the AddonNotificationInterface.
	* @param notificationIdentifier API guid that identifies the notification implementation.
	*/
	explicit AddonNotificationInterface (const API_Guid& notificationIdentifier);
	virtual ~AddonNotificationInterface ();

};


} // ACAPI

#endif
