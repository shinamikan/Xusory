#include "../Dx12UnorderedAccessBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12UnorderedAccessBuffer::Dx12UnorderedAccessBuffer() : Dx12Buffer(D3D12_HEAP_TYPE_DEFAULT) { }

	void Dx12UnorderedAccessBuffer::CreateFixedUnorderedAccessBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT64 size)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, nullptr,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;
		m_uavDimension = D3D12_UAV_DIMENSION_BUFFER;
	}

	void Dx12UnorderedAccessBuffer::CreateUnorderedAccessBuffer2D(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT width, UINT height, UINT16 arraySize, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, arraySize, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, nullptr,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;

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

	void Dx12UnorderedAccessBuffer::ReSetBuffer(const Dx12DescriptorAllocator* allocator)
	{
		Dx12Buffer::ReSet();
		m_uavDimension = D3D12_UAV_DIMENSION_UNKNOWN;

		if (m_uavHandle != nullptr) allocator->ReleaseDescriptor(*m_uavHandle, 1);
		m_uavHandle = nullptr;
	}

	D3D12_UAV_DIMENSION Dx12UnorderedAccessBuffer::GetUavDimension() const
	{
		return m_uavDimension;
	}

	const Dx12DescriptorHandle& Dx12UnorderedAccessBuffer::GetUavHandle() const
	{
		return *m_uavHandle;
	}

	void Dx12UnorderedAccessBuffer::SetUavDimension(D3D12_UAV_DIMENSION dimension)
	{
		m_uavDimension = dimension;
	}

	void Dx12UnorderedAccessBuffer::DescribeAsUav(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		const auto bufferDesc = (*this)->GetDesc();
		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = bufferDesc.Format;
		uavDesc.ViewDimension = m_uavDimension;

		switch (m_uavDimension)
		{
		case D3D12_UAV_DIMENSION_BUFFER:
			uavDesc.Buffer.FirstElement = 0;
			break;

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

		if (m_uavHandle == nullptr)
		{
			m_uavHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateUnorderedAccessView(GetDxObjectPtr(), nullptr, &uavDesc, m_uavHandle->GetCpuDescriptorHandle());
	}
}
