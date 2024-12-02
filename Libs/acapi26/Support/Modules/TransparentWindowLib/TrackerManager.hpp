// **********************************************************************************************
// File:			TrackerManager.hpp
//
// Description:		The TrackerManager keeps track of the active Trackers. Used for GSAT
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
	GS::Array<const Tracker*> activeTracker;

	TrackerManager ();
	TrackerManager (const TrackerManager&); // disabled
	TrackerManager& operator= (const TrackerManager&); // disabled

	void AddTracker (const Tracker* tracker);
	void RemoveTracker (const Tracker* tracker);

public:
	static TrackerManager& Instance ();
	const GS::Array<const Tracker*>& GetTrackers () const;
};

} // Tracker

#endif // TRACKERMANAGER_HPP
