#ifndef GS_ACKEYNOTEEVENTHANDLER_HPP
#define GS_ACKEYNOTEEVENTHANDLER_HPP

#include "KeynoteAPIExport.hpp"

// from APICore
#include "APIdefs_Callback.h"


namespace ACAPI {

class API_IKeynoteItemEventHandler;
class API_IKeynoteFolderEventHandler;

/**
 * @brief Defining an interface for a class that will be used to notify keynote event handlers.
 * @ingroup Notification
 * @class API_IKeynoteEventNotifier
 * @since Archicad 28
 */
class KEYNOTEAPI_DLL_EXPORT API_IKeynoteEventNotifier : public API_IEventNotifier
{
public:
	virtual ~API_IKeynoteEventNotifier ();

	/**
	* @brief Notifies the event handler about keynote item changes.
	* @param eventHandler An instance that handles the event.
	*/
	virtual void NotifyKeynoteItemChanges (const API_IKeynoteItemEventHandler& eventHandler) const = 0;

	/**
	* @brief Notifies the event handler about keynote folder changes.
	* @param eventHandler An instance that handles the event.
	*/
	virtual void NotifyKeynoteFolderChanges (const API_IKeynoteFolderEventHandler& eventHandler) const = 0;
};


/**
 * @brief The base class you need to inherit from in case you want to handle keynote item events.
 * @ingroup Notification
 * @class API_IKeynoteItemEventHandler
 * @since Archicad 28
 */
class KEYNOTEAPI_DLL_EXPORT API_IKeynoteItemEventHandler :	public API_IEventHandler,
															public API_IObjectEventHandler
{
public:
	/**
	 * @return Human readable name of the event handler.
	 */
	virtual GS::UniString GetName () const override final;

	/**
	 * @brief It dispatches the event.
	 * @param eventNotifier The occurrence of an event can be notified via this parameter.
	 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final;
};


/**
 * @brief The base class you need to inherit from in case you want to handle keynote folder events.
 * @ingroup Notification
 * @class API_IKeynoteFolderEventHandler
 * @since Archicad 28
 */
class KEYNOTEAPI_DLL_EXPORT API_IKeynoteFolderEventHandler :	public API_IEventHandler,
																public API_IObjectEventHandler
{
public:
	/**
	 * @return Human readable name of the event handler.
	 */
	virtual GS::UniString GetName () const override final;

	/**
	 * @brief It dispatches the event.
	 * @param eventNotifier The occurrence of an event can be notified via this parameter.
	 */
	virtual void Dispatch (const API_IEventNotifier& eventNotifier) const override final;
};

}

#endif