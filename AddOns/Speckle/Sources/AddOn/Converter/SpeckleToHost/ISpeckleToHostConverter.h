#pragma once

#include <string>
#include <vector>

class ISpeckleToHostConverter
{
public:
	virtual ~ISpeckleToHostConverter() = default;

	virtual void SetSelection(std::vector<std::string> guids) = 0;
	virtual void ShowAllIn3D() = 0;
};
