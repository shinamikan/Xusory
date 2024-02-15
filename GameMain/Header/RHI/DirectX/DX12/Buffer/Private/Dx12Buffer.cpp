#include "../Dx12Buffer.h"
#include "../../Dx12CommandList.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12Buffer::Dx12Buffer(D3D12_HEAP_TYPE heapType) : m_heapType(heapType) { }

	void Dx12Buffer::ReSet()
	{
		DxObject::ReSet();
		m_usingState = D3D12_RESOURCE_STATES_UNKNOWN;
		m_transitioningState = D3D12_RESOURCE_STATES_UNKNOWN;
		m_gpuVirtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_NULL;
	}

	void Dx12Buffer::UploadResource(const Dx12Device* device, Dx12CommandList* commandList, D3D12_RESOURCE_STATES finishState, const void* pData, UINT64 dataSize)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");

		const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		const auto resourceDesc = GetBufferDesc();

		auto uploadBuffer = Dx12Buffer(D3D12_HEAP_TYPE_UPLOAD);
		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(uploadBuffer.GetDxObjectAddressOf())));

		D3D12_SUBRESOURCE_DATA subResourceData;
		subResourceData.pData = pData;
		subResourceData.RowPitch = static_cast<LONG_PTR>(dataSize);
		subResourceData.SlicePitch = subResourceData.RowPitch;

		commandList->TranslationBufferState(this, D3D12_RESOURCE_STATE_COPY_DEST);
		UpdateSubresources<1>(commandList->GetDxObjectPtr(), GetDxObjectPtr(), uploadBuffer.GetDxObjectPtr(), 0, 0, 1, &subResourceData);
		commandList->TranslationBufferState(this, finishState, true);
	}

	D3D12_RESOURCE_DESC Dx12Buffer::GetBufferDesc() const
	{
		return (*this)->GetDesc();
	}

	D3D12_RESOURCE_STATES Dx12Buffer::GetCurrentState() const
	{
		return m_usingState;
	}

	D3D12_RESOURCE_STATES Dx12Buffer::GetTransitioningState() const
	{
		return m_transitioningState;
	}

	D3D12_GPU_VIRTUAL_ADDRESS Dx12Buffer::GetGpuVirtualAddress() const
	{
		return m_gpuVirtualAddress;
	}
}
