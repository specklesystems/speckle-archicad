#pragma once

#include <string>
#include <vector>

class ISpeckleToHostConverter
{
public:
	virtual ~ISpeckleToHostConverter() = default;

	virtual void SetSelection(std::vector<std::string> guids) = 0;
	virtual void ShowAllIn3D() = 0;
	virtual void ShowIn3D() = 0;
	virtual void SetLayerVisibility(const std::vector<int>& layerIndices, bool visibility) = 0;
	virtual void SetView(const std::string& viewName) = 0;
};
