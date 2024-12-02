#ifndef GEOM_PPE_EDGEPOSSIDEINDICATORTYPE_HPP
#define GEOM_PPE_EDGEPOSSIDEINDICATORTYPE_HPP

#pragma once

enum class EdgePosSideIndicatorType
{
	OnLeft, OnRight, Undefined
};

inline EdgePosSideIndicatorType Flipp (const EdgePosSideIndicatorType& input)
{
	switch (input) {
	case EdgePosSideIndicatorType::OnLeft:
		return EdgePosSideIndicatorType::OnRight;
	case EdgePosSideIndicatorType::OnRight:
		return EdgePosSideIndicatorType::OnLeft;
	}

	return EdgePosSideIndicatorType::Undefined;
}
#endif //GEOM_PPE_EDGEPOSSIDEINDICATORTYPE_HPP
