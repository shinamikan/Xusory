#include <string>
#include <Windows.h>
#include <DbgHelp.h>

#include "../TraceBack.h"

#pragma comment(lib, "DbgHelp.lib")

struct SymbolInfo : SYMBOL_INFO
{
	char name[UINT8_MAX];
};

TraceBack::TraceBack_Internal TraceBack::sm_internalTraceBack;
const std::vector<std::string>& TraceBack::GetTraceBackInfoList()
{
	return sm_internalTraceBack.m_backTraceInfoList;
}

void TraceBack::AddTraceBackInfo(const std::string& info)
{
	sm_internalTraceBack.m_backTraceInfoList.push_back(info);
}

void TraceBack::RemoveTraceBackInfo()
{
	sm_internalTraceBack.m_backTraceInfoList.erase(sm_internalTraceBack.m_backTraceInfoList.end() - 1);
}

void TraceBack::AddFunctionPtr(void* pFunc)
{
	sm_internalTraceBack.m_funcStack.insert(sm_internalTraceBack.m_funcStack.begin(), pFunc);
	sm_internalTraceBack.m_frameCount++;
	CreateTraceBackInfo(false);
}

void TraceBack::CaptureCurrentStack(UINT captureFrames)
{
	ClearStack();

	sm_internalTraceBack.m_frameCount = CaptureStackBackTrace(0, captureFrames, sm_internalTraceBack.m_funcStack.data(), nullptr);
	CreateTraceBackInfo(true);
}

void TraceBack::ClearStack()
{
	for (UINT i = 0; i < sm_internalTraceBack.m_frameCount; i++)
	{
		sm_internalTraceBack.m_funcStack.at(i) = nullptr;
	}

	sm_internalTraceBack.m_frameCount = 0;
	sm_internalTraceBack.m_backTraceInfoList.clear();
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
		SymFromAddr(sm_internalTraceBack.m_processHandle, reinterpret_cast<DWORD64>(pFunc), nullptr, &symbol);
		SymGetLineFromAddr64(sm_internalTraceBack.m_processHandle, reinterpret_cast<DWORD64>(pFunc), &displacement, &line);
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

		for (UINT i = sm_internalTraceBack.m_frameCount - 1; i > 0; i--)
		{
			symTraceBack(sm_internalTraceBack.m_funcStack[i]);

			if (symbolName == "WinMain")
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
		symTraceBack(sm_internalTraceBack.m_funcStack[sm_internalTraceBack.m_frameCount - 1]);
		addTraceBackInfo();
	}
}

void TraceBack::UpdateProcessHandle()
{
	sm_internalTraceBack.m_processHandle = GetCurrentProcess();
	SymInitialize(sm_internalTraceBack.m_processHandle, nullptr, true);
}

TraceBack::TraceBack_Internal::TraceBack_Internal()
	: m_funcStack(std::vector<void*>(UINT8_MAX))
{
	UpdateProcessHandle();
}
