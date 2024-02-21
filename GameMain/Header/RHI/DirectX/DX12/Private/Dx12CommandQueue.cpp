#include "../Dx12CommandQueue.h"
#include "../Dx12CommandList.h"
#include "../Dx12Device.h"
#include "../Dx12Fence.h"

namespace XusoryEngine
{
	void Dx12CommandQueue::Create(const Dx12Device* device, D3D12_COMMAND_LIST_TYPE cmdListType, D3D12_COMMAND_QUEUE_FLAGS flag)
	{
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Type = cmdListType;
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

		ThrowIfDxFailed((*device)->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	void Dx12CommandQueue::ReSet()
	{
		DxObject::ReSet();
		m_queueFenceValue = 0;
	}

	D3D12_COMMAND_LIST_TYPE Dx12CommandQueue::GetCommandListType() const
	{
		return (*this)->GetDesc().Type;
	}

	void Dx12CommandQueue::ExecuteCommandList(const std::vector<Dx12CommandList*>& commandLists) const
	{
		std::vector<ID3D12CommandList*> d3dCommandLists;
		for (UINT i = 0; i < commandLists.size(); i++)
		{
			d3dCommandLists.push_back(commandLists[i]->GetDxObjectPtr());
		}
		(*this)->ExecuteCommandLists(static_cast<UINT>(d3dCommandLists.size()), d3dCommandLists.data());
	}

	void Dx12CommandQueue::SignalQueue(const Dx12Fence* fence, UINT64 completedValue) const
	{
		ThrowIfDxFailed((*this)->Signal(fence->GetDxObjectPtr(), completedValue));
	}

	void Dx12CommandQueue::AddQueueFenceValue(UINT64 value)
	{
		m_queueFenceValue += value;
	}

	void Dx12CommandQueue::SetQueueFenceValue(UINT64 value)
	{
		m_queueFenceValue = value;
	}

	void Dx12CommandQueue::WaitForFence(const Dx12Fence* fence) const
	{
		if (fence->GetCompletedFenceValue() < m_queueFenceValue)
		{
			const HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);
			fence->SetCompletedEvent(m_queueFenceValue, eventHandle);

			WaitForSingleObject(eventHandle, INFINITE);
			CloseHandle(eventHandle);
		}
	}

	void Dx12CommandQueue::SignalAndWaitForNextFence(const Dx12Fence* fence)
	{
		AddQueueFenceValue(1);
		SignalQueue(fence, m_queueFenceValue);
		WaitForFence(fence);
	}
}
