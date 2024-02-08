#pragma once

#include "Dx12Buffer2D.h"

namespace XusoryEngine
{
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12UnorderedAccessBuffer : public Dx12Buffer2D
	{
	public:
		using Dx12Buffer2D::Dx12Buffer2D;

		void CreateUnorderedAccessBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, const D3D12_CLEAR_VALUE* clearValue,
			UINT width, UINT height, UINT16 arraySize = 1, UINT16 mipLevels = 0,
			UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void ReSet() override;

		D3D12_UAV_DIMENSION GetUavDimension() const;
		const Dx12DescriptorHandle& GetUavHandle() const;

		void DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator);

	private:
		D3D12_UAV_DIMENSION m_uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle m_uavHandle;
	};
}