#pragma once

#include "ISpeckleToHostConverter.h"

class SpeckleToHostConverter : public ISpeckleToHostConverter
{
public:
	SpeckleToHostConverter() = default;

	void SetSelection(std::vector<std::string> guids) override;
	void ShowAllIn3D() override;
};
