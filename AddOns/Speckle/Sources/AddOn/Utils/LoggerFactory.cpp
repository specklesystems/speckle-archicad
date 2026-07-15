#include "LoggerFactory.h"
#include "PlatformPaths.h"

#ifdef _MSC_VER
#pragma warning ( disable: 4244 )
#endif

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
		const auto defaultPath = PlatformPaths::GetSpeckleApplicationDataDirectory()
			/ "Archicad" / "Logs" / "connector.log";
		std::filesystem::create_directories(defaultPath.parent_path());
		const std::string path = PlatformPaths::ToUtf8(defaultPath);
		return std::make_shared<Logger>(GetOrCreateLogger(
			loggerName, std::wstring(path.begin(), path.end())));
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
