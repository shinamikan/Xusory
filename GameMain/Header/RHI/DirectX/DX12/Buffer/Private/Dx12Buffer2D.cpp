#include "../Dx12Buffer2D.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12Buffer2D::Dx12Buffer2D() : Dx12Buffer(D3D12_HEAP_TYPE_DEFAULT) { }

	void Dx12Buffer2D::CreateTex2DBuffer(const Dx12Device* device,
		D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
		UINT width, UINT height, UINT16 arraySize, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, arraySize, mipLevels, sampleCount, sampleQuality, flag);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, clearValue,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;
		m_gpuVirtualAddress = (*this)->GetGPUVirtualAddress();
	}

	void Dx12Buffer2D::CreateTex2DCubeBuffer(const Dx12Device* device,
		D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
		UINT width, UINT height, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		const CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, 6, mipLevels, sampleCount, sampleQuality, flag);

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, clearValue,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_usingState = initState;
		m_gpuVirtualAddress = (*this)->GetGPUVirtualAddress();
	}

	DXGI_FORMAT Dx12Buffer2D::GetFormat() const
	{
		return (*this)->GetDesc().Format;
	}

	UINT64 Dx12Buffer2D::GetWidth() const
	{
		return (*this)->GetDesc().Width;
	}

	UINT Dx12Buffer2D::GetHeight() const
	{
		return (*this)->GetDesc().Height;
	}

	UINT16 Dx12Buffer2D::GetArraySize() const
	{
		return (*this)->GetDesc().DepthOrArraySize;
	}

	UINT16 Dx12Buffer2D::GetMipLevels() const
	{
		return (*this)->GetDesc().MipLevels;
	}

	UINT Dx12Buffer2D::GetSampleCount() const
	{
		return (*this)->GetDesc().SampleDesc.Count;
	}

	UINT Dx12Buffer2D::GetSampleQuality() const
	{
		return (*this)->GetDesc().SampleDesc.Quality;
	}
}
