#include "LoggerFactory.h"

#pragma warning ( disable: 4244 )

bool LoggerFactory::isEnabled = true;
static const std::wstring logFileName = L"zonestamp_addon_log.txt";

LoggerFactory& LoggerFactory::Get()
{
	static LoggerFactory loggerFactory;
	return loggerFactory;
}

std::shared_ptr<ILogger> LoggerFactory::GetLogger(std::string loggerName, std::wstring logFile) const
{
	if (logFile.empty())
	{
		return std::make_shared<Logger>(GetOrCreateLogger(loggerName, L"C:\\logs\\log.txt"));
	}

	return std::make_shared<Logger>(GetOrCreateLogger(loggerName, logFile));
}

void LoggerFactory::Enable()
{
	isEnabled = true;
}

void LoggerFactory::Disable()
{
	isEnabled = false;
}

std::shared_ptr<spdlog::logger> LoggerFactory::GetOrCreateLogger(std::string loggerName, std::wstring logFile)
{
	auto logger = spdlog::get(loggerName);
	if (!logger)
		return spdlog::basic_logger_mt(loggerName, std::string(logFile.begin(), logFile.end()));

	return logger;
}

void LoggerFactory::DropLogger(std::string loggerName) const
{
	spdlog::drop(loggerName);
}
