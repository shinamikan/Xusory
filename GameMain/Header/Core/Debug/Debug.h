#pragma once

#include <cstdio>
#include <iostream>
#include <string_view>

#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	enum LogType
	{
		LOG_INFO,
		LOG_WARNING,
		LOG_ERROR
	};

	DLL_STATIC_CLASS(Debug)
	{
	public:
		template <typename... Args>
		static void Log(LogType logType, Args... args);
		template <typename... Args>
		static void LogFormat(LogType logType, const std::string_view& formatStr, Args... args);

		template <typename... Args>
		static void LogInfo(Args... args);
		template <typename... Args>
		static void LogFormatInfo(const std::string_view & formatStr, Args... args);

		template <typename... Args>
		static void LogWarning(Args... args);
		template <typename... Args>
		static void LogFormatWarning(const std::string_view & formatStr, Args... args);

		template <typename... Args>
		static void LogError(Args... args);
		template <typename... Args>
		static void LogFormatError(const std::string_view & formatStr, Args... args);

	private:
		static void OutputPrepare(LogType logType);
	};

	template <typename... Args>
	void Debug::Log(LogType logType, Args... args)
	{
		OutputPrepare(logType);

		(std::cout << ... << args);
		std::cout << std::endl;
	}

	template<typename ...Args>
	void Debug::LogFormat(LogType logType, const std::string_view& formatStr, Args ...args)
	{
		OutputPrepare(logType);
		printf_s(formatStr.data(), args...);
	}

	template <typename... Args>
	void Debug::LogInfo(Args... args)
	{
		Log(LOG_INFO, args...);
	}

	template <typename... Args>
	void Debug::LogFormatInfo(const std::string_view& formatStr, Args... args)
	{
		LogFormat(LOG_INFO, formatStr, args...);
	}

	template <typename... Args>
	void Debug::LogWarning(Args... args)
	{
		Log(LOG_WARNING, args...);
	}

	template <typename... Args>
	void Debug::LogFormatWarning(const std::string_view& formatStr, Args... args)
	{
		LogFormat(LOG_WARNING, formatStr, args...);
	}

	template <typename... Args>
	void Debug::LogError(Args... args)
	{
		Log(LOG_ERROR, args...);
	}

	template <typename... Args>
	void Debug::LogFormatError(const std::string_view& formatStr, Args... args)
	{
		LogFormat(LOG_ERROR, formatStr, args...);
	}
}
