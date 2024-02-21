#pragma once

#include "../../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12CommandList;
	class Dx12Device;
	class Dx12Buffer : public DxObject<ID3D12Resource>
	{
		friend class Dx12CommandList;

	public:
		Dx12Buffer(D3D12_HEAP_TYPE heapType);

		void ReSet() override;
		void UploadResource(const Dx12Device* device, Dx12CommandList* commandList, D3D12_RESOURCE_STATES finishState, const void* pData, UINT64 dataSize);

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
