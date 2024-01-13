#pragma once

#include "ConsoleCom.h"

namespace XusoryEngine
{
	DLL_STATIC_CLASS(Console)
	{
	public:
		static BOOL CreateConsole();
		static void RedirectToStd();

		static BOOL IsCreatedConsole();
		static void SetTextColor(CONSOLE_TEXT_COLOR colorCode);
		static void SetTextFont(const std::wstring_view& fontName, INT16 fontSize = 16);
		static void SetTitle(const std::wstring_view& title);

		static void Write(const std::wstring_view& buf);
		static void WriteLine(const std::wstring_view& buf);

	private:
		static HANDLE sm_outputHandle;
	};
}
