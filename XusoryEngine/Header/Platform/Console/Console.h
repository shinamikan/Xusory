#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	using Coordinate = COORD;

	enum class ConsoleTextColor : WORD
	{
		RED = FOREGROUND_RED,
		GREEN = FOREGROUND_GREEN,
		BLUE = FOREGROUND_BLUE,
		YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
		CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED_INTENSITY = RED | FOREGROUND_INTENSITY,
		GREEN_INTENSITY = GREEN | FOREGROUND_INTENSITY,
		BLUE_INTENSITY = BLUE | FOREGROUND_INTENSITY,
		YELLOW_INTENSITY = YELLOW | FOREGROUND_INTENSITY,
		PURPLE_INTENSITY = PURPLE | FOREGROUND_INTENSITY,
		CYAN_INTENSITY = CYAN | FOREGROUND_INTENSITY,
		WHITE_INTENSITY = WHITE | FOREGROUND_INTENSITY
	};

	DLL_STATIC_CLASS(Console)
	{
	public:
		static BOOL CreateConsole();
		static void RedirectToStd();

		static BOOL IsConsoleCreated();

		static void SetSize(INT16 width, INT16 height);
		static void SetTextColor(ConsoleTextColor consoleTextColor);
		static void SetTextFont(const std::wstring_view& fontName, INT16 fontSize = 16);
		static void SetTitle(const std::wstring_view& title);

		static void Clear();
		static void MoveCursor(Coordinate coordinate);
		static void Replace(TCHAR character, Coordinate coordinate, UINT count);

		static void Write(const std::wstring_view& buf);
		static void WriteLine(const std::wstring_view& buf);

	private:
		static HANDLE sm_outputHandle;
		static ConsoleTextColor sm_usingColor;
	};
}
