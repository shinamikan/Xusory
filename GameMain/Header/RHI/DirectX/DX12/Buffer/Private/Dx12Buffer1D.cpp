#include "../Dx12Buffer1D.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12Buffer1D::Dx12Buffer1D() : Dx12Buffer(D3D12_HEAP_TYPE_DEFAULT) { }

	void Dx12Buffer1D::CreateFixedBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, UINT64 size)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size, flag);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, nullptr,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;
		m_gpuVirtualAddress = (*this)->GetGPUVirtualAddress();
	}

	void Dx12Buffer1D::CreateTex1DBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, UINT64 size, UINT16 arraySize, UINT16 mipLevels, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex1D(format, size, arraySize, mipLevels, flag);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, nullptr,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;
		m_gpuVirtualAddress = (*this)->GetGPUVirtualAddress();
	}

	UINT64 Dx12Buffer1D::GetSize() const
	{
		return (*this)->GetDesc().Width;
	}

	UINT16 Dx12Buffer1D::GetArraySize() const
	{
		return (*this)->GetDesc().DepthOrArraySize;
	}

	UINT16 Dx12Buffer1D::GetMipLevels() const
	{
		return (*this)->GetDesc().MipLevels;
	}
}
