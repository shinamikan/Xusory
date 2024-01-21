#include <iostream>
#include <vector>
#include <future>

#include "Header/NovaEngine.h"

using namespace std;
using namespace XusoryEngine;

class TestWindow : public Window
{
public:
	void OnResize(const ResizeEvent& event) override
	{
		/*Debug::Log(LOG_INFO, "Client Resize:", event.sizeX, " ", event.sizeY);

		auto windowSize = GetWindowSize();
		Debug::Log(LOG_INFO, "Window size:", windowSize.x, " ", windowSize.y);

		auto clientSize = GetWindowSize(true);
		Debug::Log(LOG_INFO, "Client size:", clientSize.x, " ", clientSize.y);*/
	}

	void OnMousePress(const MouseClickEvent& event) override
	{
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		//KeyBoard::VirtualPressKey(KEY_2);

		//Debug::Log(LOG_INFO, event.mouseKeyCode);

		if (event.mouseKeyCode == EX_BUTTON_1)
		{
			Debug::Log(LOG_INFO, event.mouseKeyCode);
		}
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		if (event.keyCode == KEY_1)
		{
			Console::Clear();
		}
		else if (event.keyCode == KEY_2)
		{
			Debug::Log(LOG_INFO, "Key Press");
		}
		else if (event.keyCode == KEY_3)
		{
			Cursor::MoveCursor(200, 200);
		}
		else if (event.keyCode == KEY_4)
		{
			WindowFactory::MessageWindow(GetWinId(), TEXT("≤‚ ‘¥∞ø⁄"), TEXT("≤‚ ‘ƒ⁄»›Hello World"));
		}
		else if (event.keyCode == KEY_5)
		{
			Debug::Log(LOG_INFO, "Monitoring the directory");
			Directory::MonitorDirChanges(TEXT("Resource/Test1"));

			Debug::Log(LOG_INFO, "Monitor over");
		}
		else if (event.keyCode == KEY_6)
		{
			Cursor::ShowCursor();
		}
	}

	void OnDestroy() override
	{
		PostQuitMessage(0);
	}
};

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	std::streamsize prec = cout.precision(8);

	try
	{
		Console::CreateConsole();
		Console::RedirectToStd();
		Console::SetTitle(TEXT("Console"));

		WindowFactory::StartNewWindowClass();
		WindowFactory::RegisterWindowClass(hIns, TEXT("MainWindow"));

		Window* window = WindowFactory::CreateWindowInstance<TestWindow>(TEXT("MainWindow"), TEXT("Application"), 400, 400, true);
		window->Show();

		window->MessageLoop();
	}
	catch (const std::exception& e)
	{
		cout << "C++ Exception TraceBack :" << endl;
		for (auto& info : TraceBack::GetTraceBackInfoList())
		{
			cout << "  " << info << endl;
		}
		cout << e.what() << endl;
		TraceBack::ClearStack();
	}

	cout.setf(orig, ios_base::floatfield);
	cout.precision(prec);
	cout << endl;
	//system("pause");

	return 0;
}
