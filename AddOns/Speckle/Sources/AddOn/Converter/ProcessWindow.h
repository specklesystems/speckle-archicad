#pragma once

#include "IProcessWindow.h"
#include <string>
#include <chrono>
#include <memory>

class ProcessWindow : public IProcessWindow
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> time;

public:
	ProcessWindow();

	void Init(const std::string& title, int phaseCount) override;
	void SetNextProcessPhase(const std::string& title, int phaseCount) override;
	void SetProcessValue(int value) override;
	bool IsProcessCanceled() override;
	void Close() override;
};
