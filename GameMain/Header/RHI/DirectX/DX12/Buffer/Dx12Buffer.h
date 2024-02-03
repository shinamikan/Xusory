#pragma once

#include "../../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12Buffer : public DxObject<ID3D12Resource>
	{
	public:
		Dx12Buffer(D3D12_HEAP_TYPE heapType);

		void ReSet() override;
		void Upload();

		D3D12_RESOURCE_DESC	  GetBufferDesc() const;
		D3D12_RESOURCE_STATES GetCurrentState() const;
		D3D12_RESOURCE_STATES GetTransitioningState() const;
		D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const;

	protected:
		D3D12_HEAP_TYPE m_heapType;

		D3D12_RESOURCE_STATES m_usingState = D3D12_RESOURCE_STATES_UNKNOWN;
		D3D12_RESOURCE_STATES m_transitioningState = D3D12_RESOURCE_STATES_UNKNOWN;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;
	};
}
