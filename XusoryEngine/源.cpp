#include <iostream>
#include <vector>
#include <future>

#include "Header/NovaEngine.h"

using namespace std;
using namespace XusoryEngine::Platform;

constexpr char CPP_EXCEPTION_INFO[] = "C++ Exception TraceBack: ";

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	SetConsoleTitle(L"SHMRenderDebugConsole");
	FILE* tempFile = nullptr;
	freopen_s(&tempFile, "conin$", "r+t", stdin);
	freopen_s(&tempFile, "conout$", "w+t", stdout);

	INIT_STATIC_CLASS(TraceBack, ENTER_FUNC_WIN_MAIN);
	INIT_STATIC_CLASS(PerformanceTime);

	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	std::streamsize prec = cout.precision(8);

	try
	{
		
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
	system("pause");

	return 0;
}
