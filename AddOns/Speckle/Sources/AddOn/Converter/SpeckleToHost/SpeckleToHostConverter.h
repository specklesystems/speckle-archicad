#pragma once

#include "ISpeckleToHostConverter.h"

class SpeckleToHostConverter : public ISpeckleToHostConverter
{
public:
	SpeckleToHostConverter() = default;

	void SetSelection(std::vector<std::string> guids) override;
	void ShowAllIn3D() override;
	void ShowIn3D() override;
	void SetLayerVisibility(const std::vector<int>& layerIndices, bool visibility) override;
	void SetView(const std::string& viewName) override;
};
