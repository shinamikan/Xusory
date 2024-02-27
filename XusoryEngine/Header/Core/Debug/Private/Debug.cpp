#include "../Debug.h"

namespace XusoryEngine
{
	void Debug::OutputPrepare(LogType logType)
	{
		switch (logType)
		{
		case LogType::LOG_INFO:
			Console::SetTextColor(ConsoleTextColor::WHITE);
			std::cout << "[Info]";
			break;

		case LogType::LOG_WARNING:
			Console::SetTextColor(ConsoleTextColor::YELLOW_INTENSITY);
			std::cout << "[Warning]";
			break;

		case LogType::LOG_ERROR:
			Console::SetTextColor(ConsoleTextColor::RED_INTENSITY);
			std::cout << "[Error]";
			break;
		}
	}
}
