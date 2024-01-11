#include "../Console.h"

namespace XusoryEngine::Platform
{
	BOOL Console::sm_isCreatedConsole = false;
	BOOL Console::sm_isRedirectToStd = false;
	HANDLE Console::sm_inputHandle = nullptr;
	HANDLE Console::sm_outputHandle = nullptr;

	void ThrowIfConsoleNotCreated()
	{
		if (!Console::IsCreatedConsole())
		{
			ThrowWithErrName(LogicError, "The console has not been created yet");
		}
	}

	BOOL Console::CreateConsole()
	{
		if (sm_isCreatedConsole)
		{
			ThrowWithErrName(LogicError, "The console has been created");
		}

		const BOOL result = AllocConsole();

		if (result)
		{
			sm_isCreatedConsole = true;

			sm_inputHandle = GetStdHandle(STD_INPUT_HANDLE);
			sm_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (!sm_inputHandle || !sm_outputHandle)
			{
				ThrowWithErrName(RuntimeError, WinFailedInfo("get std handle"));
			}
		}

		return result;
	}

	void Console::RedirectToStd()
	{
		ThrowIfConsoleNotCreated();

		FILE* tempFile = nullptr;
		const auto errorConIn = freopen_s(&tempFile, "conin$", "r+t", stdin);
		const auto errorConOut = freopen_s(&tempFile, "conout$", "w+t", stdout);

		if (errorConIn)
		{
			ThrowWithErrName(RuntimeError, FailedInfoWithErrorCode("redirect to std input", errorConIn));
		}
		if (errorConOut)
		{
			ThrowWithErrName(RuntimeError, FailedInfoWithErrorCode("redirect to std output", errorConOut));
		}

		sm_isRedirectToStd = true;
	}

	BOOL Console::IsCreatedConsole()
	{
		return sm_isCreatedConsole;
	}

	BOOL Console::IsRedirectToStd()
	{
		return sm_isRedirectToStd;
	}

	void Console::SetTextColor(CONSOLE_TEXT_COLOR colorCode)
	{
		ThrowIfConsoleNotCreated();

		if (!SetConsoleTextAttribute(sm_outputHandle, colorCode))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("set console text color"));
		}
	}

	void Console::SetTextFont(const std::wstring_view& fontName, INT16 fontSize)
	{
		CONSOLE_FONT_INFOEX cfi = {};
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = fontSize;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, fontName.data());

		if (!SetCurrentConsoleFontEx(sm_outputHandle, FALSE, &cfi))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("set console text font"));
		}
	}

	void Console::SetTitle(const std::wstring_view& title)
	{
		ThrowIfConsoleNotCreated();

		if (!SetConsoleTitle(title.data()))
		{
			ThrowWithErrName(RuntimeError, WinFailedInfo("set console title"));
		}
	}

	void Console::Write(const std::wstring_view& buf)
	{
		ThrowIfConsoleNotCreated();
		WriteConsole(sm_outputHandle, buf.data(), static_cast<DWORD>(buf.size()), nullptr, nullptr);
	}

	void Console::WriteLine(const std::wstring_view& buf)
	{
		Write(buf);
		Write(TEXT("\n"));
	}
}
