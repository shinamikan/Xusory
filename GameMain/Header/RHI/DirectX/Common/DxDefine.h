#pragma once

#include <comdef.h>
#include "DxInclude.h"

namespace XusoryEngine
{
	STD_ERROR_CLASS(DxLogicError, LogicError)
	END_CLASS;

	STD_ERROR_CLASS(DxRuntimeError, RuntimeError)
	END_CLASS;

	inline std::string DxFailedInfo(HRESULT errorCode)
	{
		const _com_error comErr = _com_error(errorCode);
		const std::wstring msg = comErr.ErrorMessage();

		return StringEx::Format<std::string>("Dx Failed:", StringEx::WStringToString(msg));
	}

	inline void ThrowIfDxFuncFailed(HRESULT errorCode)
	{
		if (FAILED(errorCode))
		{
			ThrowWithErrName(DxRuntimeError, DxFailedInfo(errorCode));
		}
	}
}
