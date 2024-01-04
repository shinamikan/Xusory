#include <string>
#include <Windows.h>
#include <DbgHelp.h>

#include "../TraceBack.h"

#pragma comment(lib, "DbgHelp.lib")

struct SymbolInfo : SYMBOL_INFO
{
	char name[UINT8_MAX];
};

std::vector<void*>	TraceBack::sm_funcStack = std::vector<void*>(UINT8_MAX);
std::vector<std::string> TraceBack::sm_backTraceInfoList = std::vector<std::string>();
HANDLE	TraceBack::sm_processHandle = nullptr;
UINT	TraceBack::sm_frameCount = 0;
BOOL	TraceBack::sm_initFlag = false;

void TraceBack::Init()
{
	UpdateProcessHandle();
	sm_initFlag = true;
}

const std::vector<std::string>& TraceBack::GetTraceBackInfoList()
{
	return sm_backTraceInfoList;
}

void TraceBack::AddTraceBackInfo(const std::string& info)
{
	sm_backTraceInfoList.push_back(info);
}

void TraceBack::RemoveTraceBackInfo()
{
	sm_backTraceInfoList.erase(sm_backTraceInfoList.end() - 1);
}

void TraceBack::AddFunctionPtr(void* pFunc)
{
	sm_funcStack.insert(sm_funcStack.begin(), pFunc);
	sm_frameCount++;
	CreateTraceBackInfo(false);
}

void TraceBack::CaptureCurrentStack(UINT captureFrames)
{
	if (!sm_initFlag)
	{
		Init();
	}

	ClearStack();

	sm_frameCount = CaptureStackBackTrace(0, captureFrames, sm_funcStack.data(), nullptr);
	CreateTraceBackInfo(true);
}

void TraceBack::ClearStack()
{
	for (UINT i = 0; i < sm_frameCount; i++)
	{
		sm_funcStack.at(i) = nullptr;
	}

	sm_frameCount = 0;
	sm_backTraceInfoList.clear();
}

void TraceBack::CreateTraceBackInfo(BOOL isCapture)
{
	SymbolInfo symbol;
	symbol.MaxNameLen = UINT8_MAX - 1;
	symbol.SizeOfStruct = sizeof(SYMBOL_INFO);

	IMAGEHLP_LINE64 line;
	DWORD displacement;

	std::string symbolName;

	auto symTraceBack = [&](void* pFunc) -> void
	{
		SymFromAddr(sm_processHandle, reinterpret_cast<DWORD64>(pFunc), nullptr, &symbol);
		SymGetLineFromAddr64(sm_processHandle, reinterpret_cast<DWORD64>(pFunc), &displacement, &line);
		symbolName = symbol.Name;
	};

	auto addTraceBackInfo = [&]() -> void
	{
		const std::string tempTraceBackInfo("Function: " + symbolName + " (file: " + line.FileName + ", line: " + std::to_string(line.LineNumber) + ")");
		AddTraceBackInfo(tempTraceBackInfo);
	};

	if (isCapture)
	{
		BOOL startCaptureFlag = false;

		for (UINT i = sm_frameCount - 1; i > 0; i--)
		{
			symTraceBack(sm_funcStack[i]);

			if (symbolName == "main")
			{
				startCaptureFlag = true;
			}

			if (startCaptureFlag)
			{
				addTraceBackInfo();
			}
		}
	}
	else
	{
		symTraceBack(sm_funcStack[sm_frameCount - 1]);
		addTraceBackInfo();
	}
}

void TraceBack::UpdateProcessHandle()
{
	sm_processHandle = GetCurrentProcess();
	SymInitialize(sm_processHandle, nullptr, true);
}
