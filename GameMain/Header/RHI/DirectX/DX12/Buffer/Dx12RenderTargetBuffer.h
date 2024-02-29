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
		Dx12RenderTargetBuffer() = default;

		void CreateRenderTargetBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, const FLOAT clearColor[4],
			UINT width, UINT height, UINT sampleCount = 1, UINT sampleQuality = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void CreateFromSwapChain(const DxSwapChain* swapChain, UINT bufferIndex);
		void ReSetBuffer(const Dx12DescriptorAllocator* rtvAllocator, const Dx12DescriptorAllocator* srvAllocator);

		D3D12_RTV_DIMENSION GetRtvDimension() const;
		D3D12_SRV_DIMENSION GetSrvDimension() const;
		const Dx12DescriptorHandle& GetRtvHandle() const;
		const Dx12DescriptorHandle& GetSrvHandle() const;

		void DescribeAsRtv(const Dx12Device* device, Dx12DescriptorAllocator* allocator);
		void DescribeRenderTargetAsSrv(const Dx12Device* device, Dx12DescriptorAllocator* allocator);

	private:
		BOOL m_isCreateFromSwapChain = false;

		D3D12_RTV_DIMENSION m_rtvDimension = D3D12_RTV_DIMENSION_UNKNOWN;
		D3D12_SRV_DIMENSION m_srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle* m_rtvHandle = nullptr;
		Dx12DescriptorHandle* m_srvHandle = nullptr;
	};
}
