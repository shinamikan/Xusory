#pragma once

#include "ConsoleCom.h"

namespace XusoryEngine::Platform
{
	DLL_STATIC_CLASS(Console)
	{
	public:
		static BOOL CreateConsole();
		static void RedirectToStd();

		static BOOL IsCreatedConsole();
		static BOOL IsRedirectToStd();

		static void SetTextColor(CONSOLE_TEXT_COLOR colorCode);
		static void SetTextFont(const std::wstring_view& fontName, INT16 fontSize = 16);
		static void SetTitle(const std::wstring_view& title);

		static void Write(const std::wstring_view& buf);
		static void WriteLine(const std::wstring_view& buf);
		template <typename... Args>
		static void StdWrite(Args... args);
		template <typename... Args>
		static void StdWriteLine(Args... args);

	private:
		static BOOL sm_isCreatedConsole;
		static BOOL sm_isRedirectToStd;

		static HANDLE sm_inputHandle;
		static HANDLE sm_outputHandle;
	};

	template<typename... Args>
	void Console::StdWrite(Args... args)
	{
		if (!sm_isRedirectToStd)
		{
			ThrowWithErrName(LogicError, "The console has not been redirected yet");
		}

		(std::cout << ... << args);
	}

	template<typename ...Args>
	void Console::StdWriteLine(Args ...args)
	{
		if (!sm_isRedirectToStd)
		{
			ThrowWithErrName(LogicError, "The console has not been redirected yet");
		}

		(std::cout << ... << args);
		std::cout << std::endl;
	}
}
