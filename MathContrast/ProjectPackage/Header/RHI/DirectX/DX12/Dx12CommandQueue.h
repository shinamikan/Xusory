#pragma once

#include <vector>
#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12CommandList;
	class Dx12Device;
	class Dx12Fence;
	DLL_CLASS(Dx12CommandQueue) : public DxObject<ID3D12CommandQueue>
	{
	public:
		Dx12CommandQueue() = default;

		void Create(const Dx12Device* device, D3D12_COMMAND_LIST_TYPE cmdListType, D3D12_COMMAND_QUEUE_FLAGS flag = D3D12_COMMAND_QUEUE_FLAG_NONE);
		void ReSet() override;

		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

		void ExecuteCommandList(const std::vector<Dx12CommandList*>& commandLists) const;
		void SignalQueue(const Dx12Fence* fence, UINT64 completedValue) const;

		void AddQueueFenceValue(UINT64 value);
		void SetQueueFenceValue(UINT64 value);
		void WaitForFence(const Dx12Fence* fence) const;
		void SignalAndWaitForNextFence(const Dx12Fence* fence);

	private:
		UINT64 m_queueFenceValue = 0;
	};
}

