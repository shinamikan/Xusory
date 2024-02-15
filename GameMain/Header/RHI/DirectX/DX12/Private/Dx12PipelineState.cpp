#include "../Dx12PipelineState.h"

#include "../Dx12Device.h"
#include "../Dx12RootSignature.h"

namespace XusoryEngine
{
	const Dx12RootSignature* Dx12PipelineState::GetRootSignature() const
	{
		return m_rootSignature;
	}

	void Dx12PipelineState::SetRootSignature(Dx12RootSignature* rootSignature)
	{
		m_rootSignature = rootSignature;
	}

	Dx12GraphicsPipelineState::Dx12GraphicsPipelineState()
	{
		m_psoDescTemp.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		m_psoDescTemp.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		m_psoDescTemp.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

		SetSampleQuality(1, 0);
		SetSampleMask(UINT_MAX);
	}

	void Dx12GraphicsPipelineState::Create(const Dx12Device* device)
	{
		if (m_psoDescTemp.pRootSignature == nullptr || m_psoDescTemp.PrimitiveTopologyType == NULL ||
			m_psoDescTemp.VS.pShaderBytecode == nullptr || m_psoDescTemp.PS.pShaderBytecode == nullptr)
		{
			ThrowWithErrName(DxLogicError, "pipeline state parameter error");
		}

		ThrowIfDxFailed((*device)->CreateGraphicsPipelineState(&m_psoDescTemp, IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	void Dx12GraphicsPipelineState::SetVertexShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.VS = { shaderByteCode, size };
	}

	void Dx12GraphicsPipelineState::SetPixelShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.PS = { shaderByteCode, size };
	}

	void Dx12GraphicsPipelineState::SetDomainShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.DS = { shaderByteCode, size };
	}

	void Dx12GraphicsPipelineState::SetHullShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.HS = { shaderByteCode, size };
	}

	void Dx12GraphicsPipelineState::SetGeometryShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.GS = { shaderByteCode, size };
	}

	void Dx12GraphicsPipelineState::SetBlendState(const D3D12_BLEND_DESC& blendDesc)
	{
		m_psoDescTemp.BlendState = blendDesc;
	}

	void Dx12GraphicsPipelineState::SetDepthStencilState(const D3D12_DEPTH_STENCIL_DESC& depthStencilDesc)
	{
		m_psoDescTemp.DepthStencilState = depthStencilDesc;
	}

	void Dx12GraphicsPipelineState::SetFillMode(D3D12_FILL_MODE fillMode)
	{
		m_psoDescTemp.RasterizerState.FillMode = fillMode;
	}

	void Dx12GraphicsPipelineState::SetCullMode(D3D12_CULL_MODE cullMode)
	{
		m_psoDescTemp.RasterizerState.CullMode = cullMode;
	}

	void Dx12GraphicsPipelineState::SetFrontCounterClockwise(BOOL frontCounterClockwise)
	{
		m_psoDescTemp.RasterizerState.FrontCounterClockwise = frontCounterClockwise;
	}

	void Dx12GraphicsPipelineState::SetRenderTargetNum(UINT renderTargetNum)
	{
		m_psoDescTemp.NumRenderTargets = renderTargetNum;
	}

	void Dx12GraphicsPipelineState::SetDepthFormat(DXGI_FORMAT format)
	{
		m_psoDescTemp.DSVFormat = format;
	}

	void Dx12GraphicsPipelineState::SetRenderTargetFormat(DXGI_FORMAT format)
	{
		m_psoDescTemp.RTVFormats[0] = format;
	}

	void Dx12GraphicsPipelineState::SetRenderTargetFormats(UINT renderTargetNum, const DXGI_FORMAT* formatList)
	{
		if (renderTargetNum < 1 || renderTargetNum > 8 || renderTargetNum != m_psoDescTemp.NumRenderTargets)
		{
			ThrowWithErrName(DxLogicError, "the render target num is wrong");
		}
		for (UINT i = 0; i < renderTargetNum; i++)
		{
			m_psoDescTemp.RTVFormats[i] = formatList[i];
		}
	}

	void Dx12GraphicsPipelineState::SetInputLayout(const D3D12_INPUT_LAYOUT_DESC& inputLayout)
	{
		m_psoDescTemp.InputLayout = inputLayout;
	}

	void Dx12GraphicsPipelineState::SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType)
	{
		m_psoDescTemp.PrimitiveTopologyType = topologyType;
	}

	void Dx12GraphicsPipelineState::SetSampleQuality(UINT sampleCount, UINT sampleQuality)
	{
		m_psoDescTemp.SampleDesc.Count = sampleCount;
		m_psoDescTemp.SampleDesc.Quality = sampleQuality;
	}

	void Dx12GraphicsPipelineState::SetNodeMask(UINT nodeMask)
	{
		m_psoDescTemp.NodeMask = nodeMask;
	}

	void Dx12GraphicsPipelineState::SetSampleMask(UINT sampleMask)
	{
		m_psoDescTemp.SampleMask = sampleMask;
	}


	void Dx12ComputePipelineState::Create(const Dx12Device* device)
	{
		if (m_psoDescTemp.pRootSignature == nullptr || m_psoDescTemp.CS.pShaderBytecode == nullptr)
		{
			ThrowWithErrName(DxLogicError, "pipeline state parameter error");
		}

		ThrowIfDxFailed((*device)->CreateComputePipelineState(&m_psoDescTemp, IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	void Dx12ComputePipelineState::SetComputeShader(const void* shaderByteCode, SIZE_T size)
	{
		m_psoDescTemp.CS = { shaderByteCode, size };
	}
}
