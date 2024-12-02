#ifndef GS_UD_IFILTER_HPP
#define GS_UD_IFILTER_HPP
#pragma once

#include "UDDefinitions.hpp"

namespace UD {

class IFilterCheckpoint;

class UD_DLL_EXPORT IFilter {
public:
	enum class State {
		Off,
		On
	};

	virtual ~IFilter ();

	virtual State GetState () const = 0;

	virtual bool Allow (const GS::UniString& name) const = 0;

	virtual bool IsNarrowerThan (const std::shared_ptr<IFilterCheckpoint>& checkPoint) const = 0;

	virtual std::shared_ptr<IFilterCheckpoint> ToCheckPoint () = 0;
};


class UD_DLL_EXPORT IFilterCheckpoint {
public:
	virtual ~IFilterCheckpoint ();

	virtual IFilter::State GetState () const = 0;
};


}

#endif  //GS_UD_IFILTER_HPP
