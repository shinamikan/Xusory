#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>

#include "../ClassEx/ClassEx.h"

#pragma warning(disable : 4251)

DLL_STATIC_CLASS(TraceBack)
{
public:
	static const std::vector<std::string>& GetTraceBackInfoList();

	static void AddTraceBackInfo(const std::string& info);
	static void RemoveTraceBackInfo();

	static void AddFunctionPtr(void* pFunc);
	static void CaptureCurrentStack(UINT captureFrames);
	static void ClearStack();
	
private:
	static void CreateTraceBackInfo(BOOL isCapture);
	static void UpdateProcessHandle();

	INTERNAL_CLASS(TraceBack)
	{
	public:
		TraceBack_Internal();

		HANDLE m_processHandle = nullptr;
		UINT m_frameCount = 0;

		std::vector<void*> m_funcStack;
		std::vector<std::string> m_backTraceInfoList;
	};
};
