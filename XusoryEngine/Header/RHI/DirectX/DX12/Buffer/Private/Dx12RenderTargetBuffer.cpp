#include "../Dx12RenderTargetBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"
#include "../../../DxSwapChain.h"

namespace XusoryEngine
{
	void Dx12RenderTargetBuffer::CreateRenderTargetBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, const FLOAT clearColor[4],
		UINT width, UINT height, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Format = format;
		memcpy(clearValue.Color, clearColor, sizeof(float) * 4);

		CreateTex2DBuffer(device, initState, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, &clearValue,
			width, height, 1, 0, sampleCount, sampleQuality, format);

		if (sampleCount == 1)
		{
			m_rtvDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		}
		else if (sampleCount > 1)
		{
			m_rtvDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			ThrowWithErrName(DxLogicError, "The buffer sample count is wrong");
		}
		m_srvDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	}

	void Dx12RenderTargetBuffer::CreateFromSwapChain(const DxSwapChain* swapChain, UINT bufferIndex)
	{
		ThrowIfDxFailed((*swapChain)->GetBuffer(bufferIndex, IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = D3D12_RESOURCE_STATE_PRESENT;
		m_isCreateFromSwapChain = true;
	}

	void Dx12RenderTargetBuffer::ReSetBuffer(const Dx12DescriptorAllocator* rtvAllocator, const Dx12DescriptorAllocator* srvAllocator)
	{
		Dx12Buffer2D::ReSet();
		m_rtvDimension = D3D12_RTV_DIMENSION_UNKNOWN;
		m_srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;

		if (m_rtvHandle != nullptr) rtvAllocator->ReleaseDescriptor(*m_rtvHandle, 1);
		if (m_srvHandle != nullptr) srvAllocator->ReleaseDescriptor(*m_srvHandle, 1);
			
		m_rtvHandle = nullptr;
		m_srvHandle = nullptr;

		m_isCreateFromSwapChain = false;
	}

	D3D12_RTV_DIMENSION Dx12RenderTargetBuffer::GetRtvDimension() const
	{
		return m_rtvDimension;
	}

	D3D12_SRV_DIMENSION Dx12RenderTargetBuffer::GetSrvDimension() const
	{
		return m_srvDimension;
	}

	const Dx12DescriptorHandle& Dx12RenderTargetBuffer::GetRtvHandle() const
	{
		return *m_rtvHandle;
	}

	const Dx12DescriptorHandle& Dx12RenderTargetBuffer::GetSrvHandle() const
	{
		return *m_srvHandle;
	}

	void Dx12RenderTargetBuffer::DescribeAsRtv(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_RTV || allocator->GetShaderVisible())
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		if (!m_isCreateFromSwapChain)
		{
			rtvDesc.Format = GetFormat();
			rtvDesc.ViewDimension = m_rtvDimension;

			switch (m_rtvDimension)
			{
			case D3D12_RTV_DIMENSION_TEXTURE2D:
			case D3D12_RTV_DIMENSION_TEXTURE2DMS:
				rtvDesc.Texture2D.MipSlice = 0;
				rtvDesc.Texture2D.PlaneSlice = 0;
				break;

			default:
				ThrowWithErrName(DxLogicError, "The uav dimension is unknown");
			}
		}

		if (m_rtvHandle == nullptr)
		{
			m_rtvHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateRenderTargetView(GetDxObjectPtr(),
			m_isCreateFromSwapChain ? nullptr : &rtvDesc, m_rtvHandle->GetCpuDescriptorHandle());
	}

	void Dx12RenderTargetBuffer::DescribeRenderTargetAsSrv(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		const auto bufferDesc = (*this)->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = bufferDesc.Format;
		srvDesc.ViewDimension = m_srvDimension;
		srvDesc.Texture2D.MipLevels = -1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		if (m_srvHandle == nullptr)
		{
			m_srvHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateShaderResourceView(GetDxObjectPtr(), &srvDesc, m_srvHandle->GetCpuDescriptorHandle());
	}
}
