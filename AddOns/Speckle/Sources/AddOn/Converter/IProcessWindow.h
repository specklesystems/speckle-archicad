#pragma once

#include <string>
#include <vector>

class IProcessWindow
{
public:
	virtual ~IProcessWindow() = default;

	virtual void Init(const std::string& title, int phaseCount) = 0;
	virtual void SetNextProcessPhase(const std::string& title, int phaseCount) = 0;
	virtual void SetProcessValue(int value) = 0;
	virtual bool IsProcessCanceled() = 0;
	virtual void Close() = 0;
};
