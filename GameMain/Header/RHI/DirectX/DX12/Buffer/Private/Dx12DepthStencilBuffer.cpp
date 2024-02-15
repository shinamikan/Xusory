#include "../Dx12DepthStencilBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12DepthStencilBuffer::CreateDepthStencilBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, FLOAT clearDepth, UINT8 clearStencil,
		UINT width, UINT height, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		D3D12_CLEAR_VALUE clearValue;
		clearValue.Format = GetFormat();
		clearValue.DepthStencil.Depth = clearDepth;
		clearValue.DepthStencil.Stencil = clearStencil;

		CreateTex2DBuffer(device, initState, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL, &clearValue,
			width, height, 1, 0, sampleCount, sampleQuality, format);

		if (sampleCount == 1)
		{
			m_dsvDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		}
		else if (sampleCount > 1)
		{
			m_dsvDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			ThrowWithErrName(DxLogicError, "The buffer sample count is wrong");
		}
	}

	void Dx12DepthStencilBuffer::ReSetBuffer(Dx12DescriptorAllocator* allocator)
	{
		Dx12Buffer::ReSet();
		m_dsvDimension = D3D12_DSV_DIMENSION_UNKNOWN;

		allocator->ReleaseDescriptor(m_dsvHandle, 1);
		m_dsvHandle = Dx12DescriptorHandle();
	}

	D3D12_DSV_DIMENSION Dx12DepthStencilBuffer::GetDsvDimension() const
	{
		return m_dsvDimension;
	}

	const Dx12DescriptorHandle& Dx12DepthStencilBuffer::GetDsvHandle() const
	{
		return m_dsvHandle;
	}

	void Dx12DepthStencilBuffer::DescribeAsDsv(const Dx12Device* device, Dx12DescriptorAllocator* allocator, BOOL useDsvDesc)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_DSV || allocator->GetShaderVisible())
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		D3D12_DEPTH_STENCIL_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = GetFormat();
		rtvDesc.ViewDimension = m_dsvDimension;

		switch (m_dsvDimension)
		{
		case D3D12_DSV_DIMENSION_TEXTURE2D:
		case D3D12_DSV_DIMENSION_TEXTURE2DMS:
			rtvDesc.Texture2D.MipSlice = 0;
			break;

		default:
			ThrowWithErrName(DxLogicError, "The uav dimension is unknown");
		}

		if (m_dsvHandle.IsNull())
		{
			m_dsvHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateDepthStencilView(GetDxObjectPtr(), useDsvDesc ? &rtvDesc : nullptr, m_dsvHandle.GetCpuDescriptorHandle());
	}
}
