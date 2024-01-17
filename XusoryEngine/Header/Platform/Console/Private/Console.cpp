#include "../Console.h"

namespace XusoryEngine
{
	HANDLE Console::sm_outputHandle = nullptr;

	BOOL Console::CreateConsole()
	{
		ThrowIfObjectHasCreated(sm_outputHandle, "console");

		const BOOL result = AllocConsole();
		if (result)
		{
			sm_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			if (!sm_outputHandle)
			{
				ThrowWithErrName(RuntimeError, WinFailedInfo("get std handle"));
			}
		}

		return result;
	}

	void Console::RedirectToStd()
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");

		FILE* tempFile = nullptr;
		if (const auto errorConOut = freopen_s(&tempFile, "conout$", "w+t", stdout))
		{
			ThrowWithErrName(RuntimeError, FailedInfoWithErrorCode("redirect to std output", errorConOut));
		}
	}

	BOOL Console::IsCreatedConsole()
	{
		return sm_outputHandle != nullptr;
	}

	void Console::SetSize(INT16 width, INT16 height)
	{
		HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT wrt = { 0, 0, width, height };
		SetConsoleWindowInfo(hStdOutput, TRUE, &wrt);
		COORD coord = { width, height };
		SetConsoleScreenBufferSize(hStdOutput, coord);
	}

	void Console::SetTextColor(ConsoleTextColor consoleTextColor)
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");
		ThrowIfWinFuncFailed(SetConsoleTextAttribute(sm_outputHandle, static_cast<WORD>(consoleTextColor)), "set console text color");
	}

	void Console::SetTextFont(const std::wstring_view& fontName, INT16 fontSize)
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");

		CONSOLE_FONT_INFOEX cfi = {};
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = fontSize;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, fontName.data());

		ThrowIfWinFuncFailed(SetCurrentConsoleFontEx(sm_outputHandle, FALSE, &cfi), "set console text font");
	}

	void Console::SetTitle(const std::wstring_view& title)
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");
		SetConsoleTitle(title.data());
	}

	void Console::Clear()
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");

		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(sm_outputHandle, &info);

		const DWORD cellCount = info.dwSize.X * info.dwSize.Y;

		Replace(TEXT(' '), { 0, 0 }, cellCount);
		MoveCursor({ 0, 0 });
	}

	void Console::MoveCursor(Coordinate coordinate)
	{
		SetConsoleCursorPosition(sm_outputHandle, coordinate);
	}

	void Console::Replace(TCHAR character, Coordinate coordinate, UINT count)
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(sm_outputHandle, &info);

		DWORD writtenCount;
		const BOOL fillCharResult = FillConsoleOutputCharacter(sm_outputHandle, character, count, coordinate, &writtenCount);
		ThrowIfWinFuncFailed(fillCharResult, "Fill Console Output Character");

		const BOOL fillAttrResult = FillConsoleOutputAttribute(sm_outputHandle, info.wAttributes, count, coordinate, &writtenCount);
		ThrowIfWinFuncFailed(fillAttrResult, "Fill Console Output Attribute");
	}

	void Console::Write(const std::wstring_view& buf)
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");
		WriteConsole(sm_outputHandle, buf.data(), static_cast<DWORD>(buf.size()), nullptr, nullptr);
	}

	void Console::WriteLine(const std::wstring_view& buf)
	{
		Write(buf);
		Write(TEXT("\n"));
	}
}
