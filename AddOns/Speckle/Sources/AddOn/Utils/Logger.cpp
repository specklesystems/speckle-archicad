#include "Logger.h"

#pragma warning ( disable: 4244 )


#include <memory>

Logger::Logger(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger))
{
}

void Logger::Trace(const std::string_view& message)
{
	logger->trace(message);
}

void Logger::Debug(const std::string_view& message)
{
	logger->debug(message);
}

void Logger::Info(const std::string_view& message)
{
	logger->info(message);
}

void Logger::Warn(const std::string_view& message)
{
	logger->warn(message);
}

void Logger::Error(const std::string_view& message)
{
	logger->error(message);
}

