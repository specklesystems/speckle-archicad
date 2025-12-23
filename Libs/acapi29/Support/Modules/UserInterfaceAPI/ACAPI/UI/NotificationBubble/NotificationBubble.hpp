#ifndef GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLE_HPP
#define GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLE_HPP

// from ARCHICADAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "UserInterfaceAPIExport.hpp"


#include <optional>


namespace DG {
class Icon;
}


namespace ACAPI::UI::Notification {


namespace Impl { class NotificationBubbleImpl; }

/**
 * @brief NotificationBubble is a tooltip-like small window, which can display various informations for the user.
 * @ingroup Notification
 * @par Example code snippets from Notification Manager / Show notification bubble at local origo
 *		@snippet NotificationBubble_Test.cpp NotificationBubble-Example
 * @since Archicad 29
 */
class USERINTERFACEAPI_DLL_EXPORT NotificationBubble : public ACAPI::Object {
	friend class NotificationBubbleManager;

public:
	/**
	 * @brief Returns the text of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 * @return the text of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 */
	std::optional<GS::UniString> GetText () const;

	/**
	 * @brief Changes the text of the notification bubble.
	 * @param text Notification bubble text to set.
	 */
	void	SetText (const GS::UniString& text);

	/**
	 * @brief Returns the icon of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 * @return the icon of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 */
	std::optional <DG::Icon> GetIcon () const;

	/**
	 * @brief Changes the icon of the notification bubble.
	 * @param icon Notification bubble icon to set.
	 */
	void	SetIcon (const DG::Icon& icon);

	/**
	 * @brief Returns the large icon of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 * @return the large icon of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 * @remarks The large icon, if set, is used, when "Use large alert cues" option is on in Work Environment.
	 */
	std::optional <DG::Icon> GetLargeIcon () const;

	/**
	 * @brief Changes the large icon of the notification bubble.
	 * @param largeIcon Notification bubble large icon to set.
	 * @remarks The large icon, if set, is used, when "Use large alert cues" option is on in Work Environment.
	 */
	void	SetLargeIcon (const DG::Icon& largeIcon);

	/**
	 * @brief Returns the timeout, or, the lifetime of the notification bubble, in milliseconds.
	 * @return the timeout, or, the lifetime of the notification bubble, in milliseconds.
	 */
	UInt32 GetTimeout () const;

	/**
	 * @brief The timeout, or, the lifetime of the notification bubble, in milliseconds.
	 * @param timeoutMillisecs The bubble will disappear after this amount of milliseconds. Default value is 1000 milliseconds, or 1 seconds.
	 */
	void	SetTimeout (const UInt32 timeoutMillisecs);

	/**
	 * @brief Returns the redraw count limit of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 * @return the redraw count limit of the notification bubble, if there is any. Otherwise, returns std::nullopt.
	 */
	std::optional <UInt32> GetRedrawCountLimit () const;

	/**
	 * @brief The redraw count limit, which determines, that maximum how many times can the bubble appear.
	 * @param redrawCountLimit determines, that maximum how many times can the bubble appear.
	 * @remarks: after the bubble is shown redrawCountLimit times, it won't appear again. Until, user executes the 'Enable all informational messages' command.
	 */
	void	SetRedrawCountLimit (const UInt32 redrawCountLimit);

	/**
	 * @brief Disable showing of the notification bubble.
	 * @remarks: If this is called, then the bubble won't appear again. The 'Enable all informational messages' command reenables the bubble.
	 */
	void	SetDisabled ();

	/**
	 * @brief Returns the offset of the bubble from the mouse origin.
	 * @return the offset of the bubble from the mouse origin.
	 */
	API_Point GetOffset () const;

	/**
	 * @brief Sets the offset of the bubble from the mouse origin.
	 * @param newOffset the new offset of the bubble from the mouse origin to be set.
	 */
	void	SetOffset (const API_Point& newOffset);

	/**
	 * @brief Shows the notification bubble.
	 * @param point The pixel coordinate, where the notification will be displayed.
	 */
	void	Show (const API_Point& point);

private:
	explicit NotificationBubble (std::shared_ptr<Impl::NotificationBubbleImpl> impl);
};

} //namespace ACAPI::UI::Notification

#endif //GS_ACAPIUINOTIFICATION_NOTIFICATIONBUBBLE_HPP
