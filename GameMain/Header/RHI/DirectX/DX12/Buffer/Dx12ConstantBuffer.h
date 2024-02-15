#pragma once

#include "Dx12Buffer1D.h"

namespace XusoryEngine
{
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12ConstantBuffer : public Dx12Buffer1D
	{
	public:
		Dx12ConstantBuffer() = default;

		void CreateConstantBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT64 size);
		void ReSetBuffer(Dx12DescriptorAllocator* allocator);

		const Dx12DescriptorHandle& GetUavHandle() const;

		void DescribeAsCbv(const Dx12Device* device, Dx12DescriptorAllocator* allocator);

	private:
		Dx12DescriptorHandle m_cbvHandle;
	};
}
