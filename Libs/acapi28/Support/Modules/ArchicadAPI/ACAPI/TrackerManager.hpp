#ifndef ACAPI_TRACKING_TRACKERMANAGER_HPP
#define ACAPI_TRACKING_TRACKERMANAGER_HPP

#include "ACAPI/ArchicadAPIExport.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"


/**
 * @defgroup MainTracker Tracker Manager
 * @brief In Archicad every input level has a tracker which is called the main tracker.
 */


namespace Tracking {
	class Tracker;
}


namespace ACAPI {
namespace Tracking {

namespace v1 {

/**
 * @brief Reference to the type @ref ::Tracking::Tracker
 * @ingroup Tracker
 * @since Archicad 28
 */
using TrackerRef = std::reference_wrapper<::Tracking::Tracker>;


/**
 * @brief TrackerManager is a class to access the main tracker with.
 * @ingroup MainTracker
 * @ingroup Tracker
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT TrackerManager : public Object {
	friend Result<TrackerManager> GetTrackerManager ();

public:
	/**
	 * @brief Returns the main tracker.
	 * @return Returns a reference to the main tracker if the process succeeds, otherwise returns an error.
	 * 		   - APIERR_GENERAL - The main tracker is missing, which is an invalid state.
	 * @par Example code snippets from Test / Tracker Manager
	 * 		@snippet TrackerManager_Test.cpp Get-Main-Tracker-Example
	 */
	Result<TrackerRef> GetMainTracker () const;

private:
	explicit TrackerManager (const API_Token&);
};


/**
 * @brief A function to create TrackerManager instance.
 * @ingroup Tracker
 * @return Returns the TrackerManager instance. This process cannot fail.
 */
inline Result<TrackerManager> GetTrackerManager ()
{
	return Ok (TrackerManager (ACAPI_GetToken ()));
}

}


using v1::TrackerRef;
using v1::TrackerManager;
using v1::GetTrackerManager;

}
}


#endif