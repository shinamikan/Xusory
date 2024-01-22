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
}
