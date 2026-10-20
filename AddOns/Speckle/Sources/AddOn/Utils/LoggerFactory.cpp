#include "LoggerFactory.h"

#include "spdlog/sinks/null_sink.h"

#include <filesystem>
#include <windows.h>
#include <shlobj.h>

bool LoggerFactory::isEnabled = true;

static std::filesystem::path DefaultLogFile()
{
	wchar_t appDataPath[MAX_PATH];
	if (FAILED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appDataPath)))
		return {};

	return std::filesystem::path(appDataPath) / L"Speckle" / L"Logs" / L"Archicad.log";
}

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

std::shared_ptr<spdlog::logger> LoggerFactory::GetOrCreateLogger(std::string loggerName, std::filesystem::path logFile)
{
	auto logger = spdlog::get(loggerName);
	if (logger)
		return logger;

	// Callers log from catch handlers in Archicad entry points, so an unopenable log file must not throw (ENG-10761).
	try
	{
		return spdlog::basic_logger_mt(loggerName, logFile.string());
	}
	catch (...)
	{
		return spdlog::null_logger_mt(loggerName);
	}
}

void LoggerFactory::DropLogger(std::string loggerName) const
{
	spdlog::drop(loggerName);
}
