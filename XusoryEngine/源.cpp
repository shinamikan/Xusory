#include <iostream>
#include <vector>
#include <future>

#include "Header/NovaEngine.h"

using namespace std;
using namespace XusoryEngine;

constexpr char CPP_EXCEPTION_INFO[] = "C++ Exception TraceBack: ";

class TestWindow : public Window
{
public:
	void OnResize(const ResizeEvent& event) override
	{
		cout << "Client Resize:" << event.sizeX << "  " << event.sizeY << endl;

		auto windowSize = GetWindowSize();
		cout << "Window size:" << windowSize.x << "  " << windowSize.y << endl;

		auto clientSize = GetWindowSize(true);
		cout << "Client size:" << clientSize.x << "  " << clientSize.y << endl;
	}

	void OnMousePress(const MouseClickEvent& event) override
	{
		Console::Clear();
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		cout << 12345;
	}

	void OnDestroy() override
	{
		PostQuitMessage(0);
	}
};

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	INIT_STATIC_CLASS(TraceBack, ENTER_FUNC_WIN_MAIN);
	INIT_STATIC_CLASS(PerformanceTime, );

	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	std::streamsize prec = cout.precision(8);

	try
	{
		Console::CreateConsole();
		Console::RedirectToStd();
		Console::SetTitle(TEXT("Console"));
		Console::SetTextColor(ConsoleTextColor::COLOR_BLUE_INTENSITY);
		Console::SetTextFont(TEXT("Î¢ÈíÑÅºÚ"), 25);
		Console::SetSize(200, 10);

		WindowFactory::StartNewWindowClass();
		WindowFactory::RegisterWindowClass(hIns, TEXT("MainWindow"));

		Window* window = WindowFactory::CreateWindowInstance<TestWindow>(TEXT("MainWindow"), TEXT("Application"), 400, 400, true);
		window->Show();

		window->MessageLoop();
	}
	catch (const std::exception& e)
	{
		cout << CPP_EXCEPTION_INFO << endl;
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
