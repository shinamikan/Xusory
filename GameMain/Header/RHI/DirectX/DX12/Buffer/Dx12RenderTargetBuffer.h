#pragma once

#include "Dx12Buffer2D.h"

namespace XusoryEngine
{
	class DxSwapChain;
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12RenderTargetBuffer : public Dx12Buffer2D
	{
	public:
		using Dx12Buffer2D::Dx12Buffer2D;

		void CreateRenderTargetBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, const DirectX::XMVECTORF32& clearColor,
			UINT width, UINT height, UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void CreateFromSwapChain(const DxSwapChain* swapChain, UINT bufferIndex);
		void ReSet() override;

		D3D12_RTV_DIMENSION GetRtvDimension() const;
		D3D12_UAV_DIMENSION GetDsvDimension() const;
		const Dx12DescriptorHandle& GetRtvHandle() const;
		const Dx12DescriptorHandle& GetDsvHandle() const;

		void DescribeAsRtv(const Dx12Device* device, Dx12DescriptorAllocator* allocator);
		void DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator);

	private:
		BOOL m_isCreateFromSwapChain = false;

		D3D12_RTV_DIMENSION m_rtvDimension = D3D12_RTV_DIMENSION_UNKNOWN;
		D3D12_UAV_DIMENSION m_uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle m_rtvHandle;
		Dx12DescriptorHandle m_uavHandle;
	};
}
