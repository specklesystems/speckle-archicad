#pragma once

#include "ILogger.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <string>

class Logger : public ILogger
{
public:
	Logger(std::shared_ptr<spdlog::logger> logger);

	void Trace(const std::string_view& message) override;
	void Debug(const std::string_view& message) override;
	void Info(const std::string_view& message) override;
	void Warn(const std::string_view& message) override;
	void Error(const std::string_view& message) override;

private:
	std::shared_ptr<spdlog::logger> logger;

};

