#pragma once

#include "IProcessWindow.h"

class ProcessWindow : public IProcessWindow
{
public:
	ProcessWindow() = default;

	void Init(const std::string& title, int phaseCount) override;
	void SetNextProcessPhase(const std::string& title, int phaseCount) override;
	void SetProcessValue(int value) override;
	bool IsProcessCanceled() override;
	void Close() override;
};
