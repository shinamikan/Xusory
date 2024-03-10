#pragma once

#include "Header/XusoryEngine.h"

using namespace XusoryEngine;

inline void StdErrorOutput(const std::exception& e)
{
	std::string completeErrorMsg;

	if (!TraceBack::GetTraceBackInfoList().empty())
	{
		completeErrorMsg = "C++ Exception TraceBack :\n";
		for (auto& info : TraceBack::GetTraceBackInfoList())
		{
			completeErrorMsg += "    " + info + "\n";
		}
	}
	
	completeErrorMsg = completeErrorMsg + e.what() + "\n";
	Debug::LogError(completeErrorMsg);
	TraceBack::ClearStack();
}
