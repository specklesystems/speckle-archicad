#ifndef GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLEMANAGER_HPP
#define GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLEMANAGER_HPP

// from ARCHICADAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "UserInterfaceAPIExport.hpp"

namespace ACAPI::UI::Notification {

namespace Impl { class NotificationBubbleManagerImpl; }

class NotificationBubble;

/**
 * @brief A class that contains notification bubble related functions.
 * @par Example code snippets from Notification Manager / Show notification bubble at local origo
 *		@snippet NotificationBubble_Test.cpp NotificationBubble-Example
 * @since Archicad 29
 * @ingroup Notification
 */
class USERINTERFACEAPI_DLL_EXPORT NotificationBubbleManager : public ACAPI::Object {
	friend NotificationBubbleManager CreateNotificationBubbleManager ();

public:

	/**
	* @brief Registers a new Notification Bubble.
	* @param guid Unique identifier for the Notification Bubble.
	* @remarks You must call this function as early as possible, in the RegisterInterface function, if your notification bubble has redraw count limit.
	*		   Otherwise, your notification bubble might not be affected correctly by the 'Enable all informational messages' menu command.
	*/
	void RegisterNotificationBubble (const API_Guid& guid) const;

	/**
	* @brief Creates a new Notification Bubble (if it is not registered yet, then registers it).
	* @param guid Unique identifier for the Notification Bubble.
	* @returns The new Notification Bubble.
	*/
	NotificationBubble CreateNotificationBubble (const API_Guid& guid) const;

private:
	explicit NotificationBubbleManager (const API_Token& token);
	static NotificationBubbleManager Create (const API_Token& token);
};


/**
 * @brief A function to create a notification bubble manager, which lets you create notification bubbles from API.
 * @ingroup Notification
 * @returns The notification bubble manager.
 */
inline NotificationBubbleManager CreateNotificationBubbleManager ()
{
	return NotificationBubbleManager::Create (ACAPI_GetToken ());
}

} //namespace ACAPI::UI::Notification

#endif //GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLEMANAGER_HPP
