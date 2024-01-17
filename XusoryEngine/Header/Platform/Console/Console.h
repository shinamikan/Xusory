#pragma once

#include "../Common/PlatformDefine.h"

namespace XusoryEngine
{
	using Coordinate = COORD;

	enum class ConsoleTextColor : WORD
	{
		COLOR_RED = FOREGROUND_RED,
		COLOR_GREEN = FOREGROUND_GREEN,
		COLOR_BLUE = FOREGROUND_BLUE,
		COLOR_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		COLOR_PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
		COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		COLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		COLOR_RED_INTENSITY = COLOR_RED | FOREGROUND_INTENSITY,
		COLOR_GREEN_INTENSITY = COLOR_GREEN | FOREGROUND_INTENSITY,
		COLOR_BLUE_INTENSITY = COLOR_BLUE | FOREGROUND_INTENSITY,
		COLOR_YELLOW_INTENSITY = COLOR_YELLOW | FOREGROUND_INTENSITY,
		COLOR_PURPLE_INTENSITY = COLOR_PURPLE | FOREGROUND_INTENSITY,
		COLOR_CYAN_INTENSITY = COLOR_CYAN | FOREGROUND_INTENSITY,
		COLOR_WHITE_INTENSITY = COLOR_WHITE | FOREGROUND_INTENSITY
	};

	DLL_STATIC_CLASS(Console)
	{
	public:
		static BOOL CreateConsole();
		static void RedirectToStd();

		static BOOL IsCreatedConsole();

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
	};
}
