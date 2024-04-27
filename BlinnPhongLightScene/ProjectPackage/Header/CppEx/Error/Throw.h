#pragma once

#include <type_traits>

#include "Exception.h"
#include "TraceBack.h"

// All standard library errors can be thrown using the following function and macros.
// These functions and macros can capture the function stack when an error is thrown.

template <typename ErrorT>
void StdThrow(const std::string& errorInfo, std::errc errCode = std::errc::invalid_argument)
{
	static_assert(std::is_base_of_v<Exception, ErrorT>);
	TraceBack::CaptureCurrentStack(UINT8_MAX);
	TraceBack::RemoveEndTraceBackInfo();
	throw ErrorT(errorInfo);
}

template <>
[[noreturn]] inline void StdThrow<SystemError>(const std::string& errorInfo, std::errc errCode)
{
	TraceBack::CaptureCurrentStack(UINT8_MAX);
	TraceBack::RemoveEndTraceBackInfo();
	throw SystemError(std::make_error_code(errCode), errorInfo);
}

#define Throw		StdThrow
#define SysThrow	StdThrow<SystemError>

// These two macros add error types to the error code thrown based on the above macro

#define ThrowWithErrName(exceptionType, errorInfo) \
	Throw<exceptionType>(std::string(#exceptionType) + ": " + (errorInfo))
#define SysThrowWithErrName(errorInfo, errCode) \
	SysThrow(std::string("SystemError: ") + (errorInfo), errCode)

// Wrapping a function with the following macro can capture the error thrown by this function

inline void CaptureStdFunc(const std::string& info)
{
	TraceBack::CaptureCurrentStack(UINT8_MAX);
	TraceBack::AddEndTraceBackInfo(info);
}

#define CaptureFunc(function, result)							\
	CaptureStdFunc(std::string("In Code: ") + (#function));		\
	result = function													
#define CaptureNoReturnFunc(function)							\
	CaptureStdFunc(std::string("In Code: ") + (#function));		\
	function

// The Assertion Function of Nova Engine Expansion

inline void Assert(INT expression, const std::string& errorInfo)
{
	if (!expression)
	{
		ThrowWithErrName(AssertionError, errorInfo);
	}
}
