#include "../../Buffer/Dx12RenderTargetBuffer.h"
#include "../../Dx12Device.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../../DxSwapChain.h"

namespace XusoryEngine
{
	void Dx12RenderTargetBuffer::CreateRenderTargetBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, const DirectX::XMVECTORF32& clearColor,
		UINT width, UINT height, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Format = GetFormat();
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
	}

	void Dx12RenderTargetBuffer::CreateFromSwapChain(const DxSwapChain* swapChain, UINT bufferIndex)
	{
		ThrowIfDxFailed((*swapChain)->GetBuffer(bufferIndex, IID_PPV_ARGS(GetDxObjectAddressOf())));
		m_isCreateFromSwapChain = true;
	}

	void Dx12RenderTargetBuffer::ReSet()
	{
		Dx12Buffer2D::ReSet();
		m_rtvDimension = D3D12_RTV_DIMENSION_UNKNOWN;
		m_rtvHandle = Dx12DescriptorHandle();
	}

	D3D12_RTV_DIMENSION Dx12RenderTargetBuffer::GetRtvDimension() const
	{
		return m_rtvDimension;
	}

	D3D12_UAV_DIMENSION Dx12RenderTargetBuffer::GetDsvDimension() const
	{
		return m_uavDimension;
	}

	const Dx12DescriptorHandle& Dx12RenderTargetBuffer::GetRtvHandle() const
	{
		return m_rtvHandle;
	}

	const Dx12DescriptorHandle& Dx12RenderTargetBuffer::GetDsvHandle() const
	{
		return m_uavHandle;
	}

	void Dx12RenderTargetBuffer::DescribeAsRtv(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_RTV || allocator->GetShaderVisible())
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = GetFormat();
		rtvDesc.ViewDimension = m_rtvDimension;

		if (!m_rtvHandle.IsNull())
		{
			allocator->ReleaseDescriptor(m_rtvHandle, 1);
		}
		m_rtvHandle = allocator->AllocateDescriptor(device, 1);
		(*device)->CreateRenderTargetView(GetDxObjectPtr(),
			m_isCreateFromSwapChain ? nullptr : &rtvDesc, m_rtvHandle.GetCpuDescriptorHandle());
	}

	void Dx12RenderTargetBuffer::DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV || !allocator->GetShaderVisible())
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		const auto bufferDesc = (*this)->GetDesc();
		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = bufferDesc.Format;
		uavDesc.ViewDimension = m_uavDimension;

		switch (m_uavDimension)
		{
		case D3D12_UAV_DIMENSION_TEXTURE2D:
			uavDesc.Texture2D.MipSlice = 0;
			uavDesc.Texture2D.PlaneSlice = 0;
			break;

		case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
			uavDesc.Texture2DArray.MipSlice = 0;
			uavDesc.Texture2DArray.FirstArraySlice = 0;
			uavDesc.Texture2DArray.ArraySize = bufferDesc.DepthOrArraySize;
			uavDesc.Texture2DArray.PlaneSlice = 0;
			break;

		default:
			ThrowWithErrName(DxLogicError, "The uav dimension is unknown");
		}

		if (!m_uavHandle.IsNull())
		{
			allocator->ReleaseDescriptor(m_uavHandle, 1);
		}
		m_uavHandle = allocator->AllocateDescriptor(device, 1);
		(*device)->CreateUnorderedAccessView(GetDxObjectPtr(), nullptr, &uavDesc, m_uavHandle.GetCpuDescriptorHandle());
	}
}
