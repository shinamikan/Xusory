#include "../Dx12ShaderResourceBuffer.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	void Dx12ShaderResourceBuffer::CreateShaderResourceBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState,
		UINT width, UINT height, UINT16 arraySize, UINT16 mipLevels, DXGI_FORMAT format)
	{
		CreateTex2DBuffer(device, initState, D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE, nullptr,
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

	void Dx12ShaderResourceBuffer::ReSetBuffer(const Dx12DescriptorAllocator* allocator)
	{
		Dx12Buffer::ReSet();
		m_srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;

		if (m_srvHandle != nullptr) allocator->ReleaseDescriptor(*m_srvHandle, 1);
		m_srvHandle = nullptr;
	}

	D3D12_SRV_DIMENSION Dx12ShaderResourceBuffer::GetSrvDimension() const
	{
		return m_srvDimension;
	}

	const Dx12DescriptorHandle& Dx12ShaderResourceBuffer::GetSrvHandle() const
	{
		return *m_srvHandle;
	}

	void Dx12ShaderResourceBuffer::SetSrvDimension(D3D12_SRV_DIMENSION dimension)
	{
		m_srvDimension = dimension;
	}

	void Dx12ShaderResourceBuffer::DescribeAsSrv(const Dx12Device* device, Dx12DescriptorAllocator* allocator, UINT usedMipLevels, UINT mostDetailedMip)
	{
		ThrowIfDxObjectNotCreated(GetDxObjectPtr(), "buffer");
		if (allocator->GetHeapType() != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
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

		if (m_srvHandle == nullptr)
		{
			m_srvHandle = allocator->AllocateDescriptor(device, 1);
		}
		(*device)->CreateShaderResourceView(GetDxObjectPtr(), &srvDesc, m_srvHandle->GetCpuDescriptorHandle());
	}
}
