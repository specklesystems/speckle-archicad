#pragma once

#include "Event.h"

class HostAppEvents 
{
public:
	HostAppEvents() = default;
	Event<> SelectionChanged;
	Event<> ProjectOpened;
	Event<> ProjectClosed;
	Event<> ProjectSaving;
};
