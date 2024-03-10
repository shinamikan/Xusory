#pragma once

#include "Dx12Buffer1D.h"
#include "Dx12Buffer2D.h"

namespace XusoryEngine
{
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12UnorderedAccessBuffer : public Dx12Buffer
	{
	public:
		Dx12UnorderedAccessBuffer();

		void CreateFixedUnorderedAccessBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT64 size);
		void CreateUnorderedAccessBuffer2D(const Dx12Device* device, D3D12_RESOURCE_STATES initState,
			UINT width, UINT height, UINT16 arraySize = 1, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void ReSetBuffer(const Dx12DescriptorAllocator* allocator);

		D3D12_UAV_DIMENSION GetUavDimension() const;
		const Dx12DescriptorHandle& GetUavHandle() const;
		void SetUavDimension(D3D12_UAV_DIMENSION dimension);

		void DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator);

	protected:
		D3D12_UAV_DIMENSION m_uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle* m_uavHandle = nullptr;
	};
}
