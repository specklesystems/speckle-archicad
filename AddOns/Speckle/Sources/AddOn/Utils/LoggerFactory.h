#pragma once

#include "Logger.h"
#include "ILogger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <memory>
#include <string>

#define CLASS_NAME typeid(*this).name()
#define FUNCTION_NAME __FUNCTION__

#define GET_LOGGER(loggerName) LoggerFactory::Get().GetLogger(loggerName)
#define GET_LOGGER_F(loggerName, logFilePath) LoggerFactory::Get().GetLogger(loggerName, logFilePath)

class LoggerFactory
{
private:
	static bool isEnabled;

public:
	static LoggerFactory& Get();
	std::shared_ptr<ILogger> GetLogger(std::string loggerName, std::wstring logFile = L"") const;
	void DropLogger(std::string loggerName) const;
	static void Enable();
	static void Disable();

private:
	static std::shared_ptr<spdlog::logger> GetOrCreateLogger(std::string loggerName, std::wstring logFile);
};
