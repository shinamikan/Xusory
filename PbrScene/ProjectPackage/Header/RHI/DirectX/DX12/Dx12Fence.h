#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12Device;
	DLL_CLASS(Dx12Fence) : public DxObject<ID3D12Fence>
	{
	public:
		Dx12Fence() = default;

		void Create(const Dx12Device* device, UINT64 initFenceValue = 0);

		UINT64 GetCompletedFenceValue() const;
		void SetCompletedEvent(UINT64 fenceValue, HANDLE eventHandle) const;
	};
}
