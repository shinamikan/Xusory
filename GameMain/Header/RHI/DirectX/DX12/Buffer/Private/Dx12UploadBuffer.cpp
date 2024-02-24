#include "../Dx12UploadBuffer.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
    UINT64 CalcConstantBufferByteSize(UINT64 byteSize)
    {
        return (byteSize + 255) & ~255;
    }

	Dx12UploadBuffer::Dx12UploadBuffer(BOOL isConstantBuffer) : Dx12Buffer(D3D12_HEAP_TYPE_UPLOAD), m_isConstantBuffer(isConstantBuffer) { }

	Dx12UploadBuffer::~Dx12UploadBuffer()
	{
		DxObject::~DxObject();

		if (GetDxObjectPtr() != nullptr)
		{
			(*this)->Unmap(0, nullptr);
		}
		m_mappedData = nullptr;
	}

	void Dx12UploadBuffer::CreateUploadBuffer(const Dx12Device* device, UINT64 size)
	{
		if (m_isConstantBuffer)
		{
			size = CalcConstantBufferByteSize(size);
		}

		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = D3D12_RESOURCE_STATE_GENERIC_READ;
		m_gpuVirtualAddress = (*this)->GetGPUVirtualAddress();

		m_bufferSize = size;
		ThrowIfDxFailed((*this)->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedData)));
	}

	void Dx12UploadBuffer::CopyDataToBuffer(const void* srcData) const
	{
		memcpy(m_mappedData, srcData, m_bufferSize);
	}
}
