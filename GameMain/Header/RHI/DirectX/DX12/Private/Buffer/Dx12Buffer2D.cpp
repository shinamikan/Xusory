#include "../../Buffer/Dx12Buffer2D.h"
#include "../../Dx12Device.h"
#include "../../Dx12DescriptorAllocator.h"

namespace XusoryEngine
{
	Dx12Buffer2D::Dx12Buffer2D() : Dx12Buffer(D3D12_HEAP_TYPE_DEFAULT) { }

	void Dx12Buffer2D::CreateTex2DBuffer(const Dx12Device* device,
		D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
		UINT width, UINT height, UINT16 arraySize, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, arraySize, mipLevels, sampleCount, sampleQuality);
		resourceDesc.Flags = flag;

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, clearValue,
			IID_PPV_ARGS(GetDxObjectAddressOf())));
	}

	void Dx12Buffer2D::CreateTex2DCubeBuffer(const Dx12Device* device,
		D3D12_RESOURCE_STATES initState, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* clearValue,
		UINT width, UINT height, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality, DXGI_FORMAT format)
	{
		const CD3DX12_HEAP_PROPERTIES heapProperties(m_heapType);
		CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, 6, mipLevels, sampleCount, sampleQuality);
		resourceDesc.Flags = flag;

		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&resourceDesc, initState, clearValue,
			IID_PPV_ARGS(GetDxObjectAddressOf())));

		m_srvDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
	}

	void Dx12Buffer2D::CreateShaderResourceBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState,
		UINT width, UINT height, UINT16 arraySize, UINT16 mipLevels, DXGI_FORMAT format)
	{
		CreateTex2DBuffer(device, initState, D3D12_RESOURCE_FLAG_NONE, nullptr,
			width, height, arraySize, mipLevels, 1, 0, format);

		if (arraySize < 1)
		{
			ThrowWithErrName(DxLogicError, "The buffer array size is wrong");
		}
		if (arraySize == 1)
		{
			m_srvDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		}
		else
		{
			m_srvDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
		}
	}

	void Dx12Buffer2D::ReSet()
	{
		Dx12Buffer::ReSet();
		m_srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;
		m_srvHandle = Dx12DescriptorHandle();
	}

	D3D12_SRV_DIMENSION Dx12Buffer2D::GetSrvDimension() const
	{
		return m_srvDimension;
	}

	const Dx12DescriptorHandle& Dx12Buffer2D::GetSrvHandle() const
	{
		return m_srvHandle;
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

	void Dx12Buffer2D::DescribeAsSrv(const Dx12Device* device, Dx12DescriptorAllocator* allocator, UINT usedMipLevels, UINT mostDetailedMip)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV || !allocator->GetShaderVisible())
		{
			ThrowWithErrName(DxLogicError, "The attribute of the descriptor allocator does not match");
		}

		const auto bufferDesc = (*this)->GetDesc();
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = bufferDesc.Format;
		srvDesc.ViewDimension = m_srvDimension;

		switch (m_srvDimension)
		{
		case D3D12_SRV_DIMENSION_TEXTURE2D:
			srvDesc.Texture2D.MipLevels = usedMipLevels;
			srvDesc.Texture2D.MostDetailedMip = mostDetailedMip;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE2DARRAY:
			srvDesc.Texture2DArray.MipLevels = usedMipLevels;
			srvDesc.Texture2DArray.MostDetailedMip = mostDetailedMip;
			srvDesc.Texture2DArray.FirstArraySlice = 0;
			srvDesc.Texture2DArray.ArraySize = bufferDesc.DepthOrArraySize;
			break;

		case D3D12_SRV_DIMENSION_TEXTURECUBE:
			srvDesc.TextureCube.MipLevels = usedMipLevels;
			srvDesc.TextureCube.MostDetailedMip = mostDetailedMip;
			break;

		default:
			ThrowWithErrName(DxLogicError, "The srv dimension is unknown");
		}

		if (!m_srvHandle.IsNull())
		{
			allocator->ReleaseDescriptor(m_srvHandle, 1);
		}
		m_srvHandle = allocator->AllocateDescriptor(device, 1);
		(*device)->CreateShaderResourceView(GetDxObjectPtr(), &srvDesc, m_srvHandle.GetCpuDescriptorHandle());
	}
}
