#ifndef GS_UD_IFILTERABLE_HPP
#define GS_UD_IFILTERABLE_HPP
#pragma once

#include <memory>

#include "UDDefinitions.hpp"
#include "UDIFilter.hpp"

namespace UD {

class UD_DLL_EXPORT IFilterable {
protected:
	std::shared_ptr<IFilter> filter;
	std::shared_ptr<IFilterCheckpoint> previousFilterCheckpoint;

public:
	IFilterable ();
	virtual ~IFilterable ();

	void AddFilter (std::shared_ptr<IFilter> newFilter);

	bool AllowByFilter (const GS::UniString& name) const;

	bool IsNarrowerSearch () const;

	void	RefreshFiltering ();

	IFilter::State GetFilterState () const;

	IFilter::State GetPreviousCheckpointState () const;

private:
	virtual void	DoRefreshFiltering () = 0;

};

}

#endif  //GS_UD_IFILTERABLE_HPP
