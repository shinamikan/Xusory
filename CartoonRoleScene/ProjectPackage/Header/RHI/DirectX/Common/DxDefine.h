#pragma once

#include <comdef.h>
#include "DxInclude.h"

#define D3D12_COMMAND_LIST_TYPE_UNKNOWN		((D3D12_COMMAND_LIST_TYPE)-1)
#define D3D12_DESCRIPTOR_HEAP_TYPE_UNKNOWN  ((D3D12_DESCRIPTOR_HEAP_TYPE)-1)
#define D3D12_RESOURCE_STATES_UNKNOWN  ((D3D12_RESOURCE_STATES)-1)
#define D3D12_GPU_VIRTUAL_ADDRESS_NULL ((D3D12_GPU_VIRTUAL_ADDRESS)0)

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

		return StringEx::Format<std::string>("Dx Failed, errorCode(HResult): %d", errorCode);
	}

	inline void ThrowIfDxFailed(HRESULT errorCode)
	{
		if (FAILED(errorCode))
		{
			ThrowWithErrName(DxRuntimeError, DxFailedInfo(errorCode));
		}
	}

	inline void ThrowIfDxObjectNotCreated(const void* dxObjectPtr, const std::string_view& objectInfo)
	{
		if (!dxObjectPtr)
		{
			ThrowWithErrName(DxLogicError, HasNotCreatedInfo(objectInfo));
		}
	}
}
