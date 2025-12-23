#ifndef GS_ACAPI_EDITNOTIFICATIONINTERFACE_HPP
#define GS_ACAPI_EDITNOTIFICATIONINTERFACE_HPP

// from ARCHICADAPI
#include "AddonNotificationInterface.hpp"


struct API_ActTranPars;


namespace ACAPI {

/**
 * @brief EditNotificationInterface is responsible for handling Edit Notifications through API. You can make your own notification implementation, which will be executed after element editings.
 * @ingroup Notification
 * @since Archicad 29
 */
//TODO #SeD: snippet

class ARCHICADAPI_EXPORT EditNotificationInterface : public ACAPI::AddonNotificationInterface {
public:

	/**
	 * @brief Constructs a new Edit Notification Interface.
	 */
	EditNotificationInterface ();


	virtual ~EditNotificationInterface () override;

	/**
	 * @brief The callback to be overridden in your implementation. This is called, when elements are edited.
	 * @param changedItemGuids The changed item guids during the editing.
	 * @param actTranPars The transformation parameters of the editing.
	 */
	virtual void ElementsEdited (const GS::HashSet<API_Guid>& changedItemGuids, const API_ActTranPars& actTranPars) = 0;

};

} //namespace ACAPI

#endif //GS_ACAPI_EDITNOTIFICATIONINTERFACE_HPP
