#include "../Dx12Fence.h"
#include "../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12Fence::Create(const Dx12Device* device, UINT64 initFenceValue)
	{
		ThrowIfDxFailed((*device)->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	UINT64 Dx12Fence::GetCompletedFenceValue() const
	{
		return (*this)->GetCompletedValue();
	}

	void Dx12Fence::SetCompletedEvent(UINT64 fenceValue, HANDLE eventHandle) const
	{
		ThrowIfDxFailed((*this)->SetEventOnCompletion(fenceValue, eventHandle));
	}
}
