#include "../Dx12UnorderedAccessBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12UnorderedAccessBuffer::CreateUnorderedAccessBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT64 size)
	{
		CreateFixedBuffer(device, initState, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, size);
		m_uavDimension = D3D12_UAV_DIMENSION_BUFFER;
	}

	void Dx12UnorderedAccessBuffer::CreateUnorderedAccessBuffer2D(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT width, UINT height, UINT16 arraySize, DXGI_FORMAT format)
	{
		CreateTex2DBuffer(device, initState, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, nullptr,
			width, height, arraySize, 1, 0, format);

		if (arraySize < 1)
		{
			ThrowWithErrName(DxLogicError, "The buffer array size is wrong");
		}
		if (arraySize == 1)
		{
			m_uavDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
		}
		else
		{
			m_uavDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
		}
	}

	void Dx12UnorderedAccessBuffer::ReSetBuffer(Dx12DescriptorAllocator* allocator)
	{
		Dx12Buffer::ReSet();
		m_uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;

		allocator->ReleaseDescriptor(m_uavHandle, 1);
		m_uavHandle = Dx12DescriptorHandle();
	}

	D3D12_UAV_DIMENSION Dx12UnorderedAccessBuffer::GetUavDimension() const
	{
		return m_uavDimension;
	}

	const Dx12DescriptorHandle& Dx12UnorderedAccessBuffer::GetUavHandle() const
	{
		return m_uavHandle;
	}

	void Dx12UnorderedAccessBuffer::DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
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

		if (m_uavHandle.IsNull())
		{
			m_uavHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateUnorderedAccessView(GetDxObjectPtr(), nullptr, &uavDesc, m_uavHandle.GetCpuDescriptorHandle());
	}
}
