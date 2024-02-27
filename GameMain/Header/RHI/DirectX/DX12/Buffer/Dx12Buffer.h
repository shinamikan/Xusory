#pragma once

#include "../../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12CommandList;
	class Dx12Device;
	class Dx12Buffer : public DxObject<ID3D12Resource>
	{
		friend class Dx12CommandList;
		friend class Dx12MeshBuffer;

	public:
		Dx12Buffer(D3D12_HEAP_TYPE heapType);

		void ReSet() override;
		void UploadResource(const Dx12CommandList* commandList, D3D12_RESOURCE_STATES finishState, const Dx12Buffer* uploadBuffer, const void* pData, UINT64 dataSize);

		D3D12_RESOURCE_DESC	  GetBufferDesc() const;
		D3D12_RESOURCE_STATES GetCurrentState() const;
		D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress() const;

	protected:
		D3D12_HEAP_TYPE m_heapType;
		D3D12_RESOURCE_STATES m_usingState = D3D12_RESOURCE_STATES_UNKNOWN;
	};
}
