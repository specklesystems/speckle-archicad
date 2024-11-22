#pragma once

#include "Event.h"

class HostAppEvents 
{
public:
	HostAppEvents() = default;
	Event<const std::string&> SelectionChanged;
	Event<const std::string&> ProjectOpened;
};