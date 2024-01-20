#include "../Debug.h"

namespace XusoryEngine
{
	void Debug::OutputPrepare(LogType logType)
	{
		switch (logType)
		{
		case LOG_INFO:
			Console::SetTextColor(ConsoleTextColor::COLOR_WHITE);
			std::cout << "[Info]";
			break;

		case LOG_WARNING:
			Console::SetTextColor(ConsoleTextColor::COLOR_YELLOW_INTENSITY);
			std::cout << "[Warning]";
			break;

		case LOG_ERROR:
			Console::SetTextColor(ConsoleTextColor::COLOR_RED_INTENSITY);
			std::cout << "[Error]";
			break;
		}
	}
}
