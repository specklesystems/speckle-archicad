// **********************************************************************************************
// File:			TrackerManager.hpp
//
// Description:		The TrackerManager keeps track of the active Trackers
//
// Project:
//
// Namespace:
//
// Contact person:	TBa
// **********************************************************************************************

#ifndef TRACKERMANAGER_HPP
#define TRACKERMANAGER_HPP
#pragma once

#include "TransparentWindowLibDefinitions.hpp"

namespace Tracking {

class Tracker;

class TRANSPARENTWINDOWLIB_DLL_EXPORT TrackerManager {
	friend class Tracker;

private:
	GS::Array<Tracker*> activeTrackers;
	bool				isInSwitchingState;

	TrackerManager ();
	TrackerManager (const TrackerManager&); // disabled
	TrackerManager& operator= (const TrackerManager&); // disabled

	void AddTracker (Tracker* tracker);
	void RemoveTracker (Tracker* tracker);

public:
	static TrackerManager& Instance ();
	const GS::Array<Tracker*>& GetTrackers ();
	const GS::Array<const Tracker*>& GetConstTrackers () const;
	bool IsInNumericInput () const;
	void SetSwitchingTheActiveTrackerInProgress (bool switchingInProgress);
};

} // Tracker

#endif // TRACKERMANAGER_HPP
