#pragma once

#include "Header/XusoryEngine.h"

using namespace XusoryEngine;

inline void StdErrorOutput(const std::exception& e)
{
	std::string completeErrorMsg = "C++ Exception TraceBack :\n";
	for (auto& info : TraceBack::GetTraceBackInfoList())
	{
		completeErrorMsg += "    " + info + "\n";
	}
	completeErrorMsg += e.what();
	Debug::LogError(completeErrorMsg);
	TraceBack::ClearStack();
}

#define StdTryCatch(tryContext, catchContext)	\
	try											\
	tryContext									\
	catch (const std::exception& e)				\
	catchContext
