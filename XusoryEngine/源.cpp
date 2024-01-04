#include <iostream>
#include <vector>
#include <future>

#include "Header/IScript.h"
#include "Header/NovaEngine.h"

using namespace std;
using namespace NovaEngine::Platform;

constexpr char CPP_EXCEPTION_INFO[] = "C++ Exception TraceBack: ";

int main()
{
	INIT_STATIC_CLASS(TraceBack);
	INIT_STATIC_CLASS(PerformanceTime);

	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	std::streamsize prec = cout.precision(8);

	try
	{
		
	}
	catch (const std::exception& e)
	{
		cout << CPP_EXCEPTION_INFO << endl;
		for (auto& e : TraceBack::GetTraceBackInfoList())
		{
			cout << "  " << e << endl;
		}
		cout << e.what() << endl;
		TraceBack::ClearStack();
	}

	cout.setf(orig, ios_base::floatfield);
	cout.precision(prec);

	return 0;
}
