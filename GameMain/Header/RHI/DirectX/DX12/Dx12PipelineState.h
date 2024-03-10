#pragma once

#include "../Common/DxObject.h"

namespace XusoryEngine
{
	class Dx12Device;
	class Dx12RootSignature;
	class Dx12PipelineState : public DxObject<ID3D12PipelineState>
	{
	public:
		Dx12PipelineState() = default;

		const Dx12RootSignature* GetRootSignature() const;
		void SetRootSignature(Dx12RootSignature* rootSignature);

	protected:
		Dx12RootSignature* m_rootSignature = nullptr;
	};

	class Dx12GraphicsPipelineState : public Dx12PipelineState
	{
	public:
		Dx12GraphicsPipelineState();

		void Create(const Dx12Device* device);

		void SetVertexShader(const void* shaderByteCode, SIZE_T size);
		void SetPixelShader(const void* shaderByteCode, SIZE_T size);
		void SetDomainShader(const void* shaderByteCode, SIZE_T size);
		void SetHullShader(const void* shaderByteCode, SIZE_T size);
		void SetGeometryShader(const void* shaderByteCode, SIZE_T size);

		void SetBlendState(const D3D12_BLEND_DESC& blendDesc);
		void SetDepthStencilState(const D3D12_DEPTH_STENCIL_DESC& depthStencilDesc);

		void SetFillMode(D3D12_FILL_MODE fillMode);
		void SetCullMode(D3D12_CULL_MODE cullMode);
		void SetFrontCounterClockwise(BOOL frontCounterClockwise);

		void SetRenderTargetNum(UINT renderTargetNum);
		void SetDepthFormat(DXGI_FORMAT format);
		void SetRenderTargetFormat(DXGI_FORMAT format);
		void SetRenderTargetFormats(UINT renderTargetNum, const DXGI_FORMAT* formatList);

		void SetInputLayout(const D3D12_INPUT_LAYOUT_DESC& inputLayout);
		void SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType);
		void SetSampleQuality(UINT sampleCount, UINT sampleQuality);

		void SetNodeMask(UINT nodeMask);
		void SetSampleMask(UINT sampleMask);

	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_psoDescTemp{};
	};

	class Dx12ComputePipelineState : public Dx12PipelineState
	{
	public:
		Dx12ComputePipelineState() = default;

		void Create(const Dx12Device* device);
		void SetComputeShader(const void* shaderByteCode, SIZE_T size);

	private:
		D3D12_COMPUTE_PIPELINE_STATE_DESC m_psoDescTemp{};
	};
}
