#pragma once

#include <string>

class ILogger
{     
public:
	virtual ~ILogger() = default;

	virtual void Trace(const std::string_view& message) = 0;
	virtual void Debug(const std::string_view& message) = 0;
	virtual void Info(const std::string_view& message) = 0;
	virtual void Warn(const std::string_view& message) = 0;
	virtual void Error(const std::string_view& message) = 0;
};

