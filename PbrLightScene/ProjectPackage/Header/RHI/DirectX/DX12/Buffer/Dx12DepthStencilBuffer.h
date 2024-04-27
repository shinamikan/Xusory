#pragma once

#include "Dx12Buffer2D.h"

namespace XusoryEngine
{
	class Dx12DescriptorAllocator;
	class Dx12Device;
	DLL_CLASS(Dx12DepthStencilBuffer) : public Dx12Buffer2D
	{
	public:
		Dx12DepthStencilBuffer() = default;

		void CreateDepthStencilBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, FLOAT clearDepth, UINT8 clearStencil,
			UINT width, UINT height, UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT);
		void ReSetBuffer(const Dx12DescriptorAllocator* allocator);

		D3D12_DSV_DIMENSION GetDsvDimension() const;
		const Dx12DescriptorHandle& GetDsvHandle() const;

		void DescribeAsDsv(const Dx12Device* device, Dx12DescriptorAllocator* allocator, BOOL useDsvDesc = false);

	private:
		D3D12_DSV_DIMENSION m_dsvDimension = D3D12_DSV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle* m_dsvHandle = nullptr;
	};
}
