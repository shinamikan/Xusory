#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>

#include "../ClassEx/ClassEx.h"

STATIC_CLASS(TraceBack)
{
public:
	static void Init(const std::string_view& enterFunc);

	static const std::vector<std::string>& GetTraceBackInfoList();

	static void AddTraceBackInfo(const std::string& info);
	static void RemoveTraceBackInfo();

	static void AddFunctionPtr(void* pFunc);
	static void CaptureCurrentStack(UINT captureFrames);
	static void ClearStack();
	
private:
	static void CreateTraceBackInfo(BOOL isCapture);
	static void UpdateProcessHandle();

private:
	static BOOL		sm_initFlag;
	static HANDLE	sm_processHandle;

	static UINT		sm_frameCount;

	static std::string				sm_enterFunc;
	static std::vector<void*>		sm_funcStack;
	static std::vector<std::string> sm_backTraceInfoList;
};
