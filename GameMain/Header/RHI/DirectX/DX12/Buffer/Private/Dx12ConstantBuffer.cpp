#include "../Dx12ConstantBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12ConstantBuffer::CreateConstantBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, UINT64 size)
	{
		CreateFixedBuffer(device, initState, D3D12_RESOURCE_FLAG_NONE, size);
	}

	void Dx12ConstantBuffer::ReSetBuffer(const Dx12DescriptorAllocator* allocator)
	{
		Dx12Buffer::ReSet();

		if (m_cbvHandle != nullptr) allocator->ReleaseDescriptor(*m_cbvHandle, 1);
		m_cbvHandle = nullptr;
	}

	const Dx12DescriptorHandle& Dx12ConstantBuffer::GetCbvHandle() const
	{
		return *m_cbvHandle;
	}

	void Dx12ConstantBuffer::DescribeAsCbv(const Dx12Device* device, Dx12DescriptorAllocator* allocator)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
		cbvDesc.BufferLocation = GetGpuVirtualAddress();
		cbvDesc.SizeInBytes = static_cast<UINT>(GetSize());

		if (m_cbvHandle == nullptr)
		{
			m_cbvHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateConstantBufferView(&cbvDesc, m_cbvHandle->GetCpuDescriptorHandle());
	}
}
