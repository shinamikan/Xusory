#include "../../Buffer/Dx12Buffer.h"

namespace XusoryEngine
{
	Dx12Buffer::Dx12Buffer(D3D12_HEAP_TYPE heapType) : m_heapType(heapType) { }

	void Dx12Buffer::ReSet()
	{
		DxObject::ReSet();
		m_usingState = D3D12_RESOURCE_STATES_UNKNOWN;
		m_transitioningState = D3D12_RESOURCE_STATES_UNKNOWN;
		m_gpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;
	}

	D3D12_RESOURCE_DESC Dx12Buffer::GetBufferDesc() const
	{
		return (*this)->GetDesc();
	}

	D3D12_RESOURCE_STATES Dx12Buffer::GetCurrentState() const
	{
		return m_usingState;
	}

	D3D12_RESOURCE_STATES Dx12Buffer::GetTransitioningState() const
	{
		return m_transitioningState;
	}

	D3D12_GPU_VIRTUAL_ADDRESS Dx12Buffer::GetGpuVirtualAddress() const
	{
		return m_gpuVirtualAddress;
	}
}
