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

	void Console::SetTextColor(CONSOLE_TEXT_COLOR colorCode)
	{
		ThrowIfObjectNotCreated(sm_outputHandle, "console");
		ThrowIfWinFuncFailed(SetConsoleTextAttribute(sm_outputHandle, colorCode), "set console text color");
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
		ThrowIfWinFuncFailed(SetConsoleTitle(title.data()), "set console title");
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
