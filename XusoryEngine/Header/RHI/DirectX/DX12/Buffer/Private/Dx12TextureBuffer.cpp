#include "../Dx12TextureBuffer.h"
#include "../Dx12Buffer.h"
#include "../Dx12ShaderResourceBuffer.h"
#include "../../Dx12CommandList.h"
#include "../../Dx12DescriptorAllocator.h"
#include "../../Dx12Device.h"

namespace XusoryEngine
{
	Dx12TextureBuffer::Dx12TextureBuffer()
	{
		m_textureBuffer = std::make_unique<Dx12ShaderResourceBuffer>();
		m_uploadBuffer = new Dx12Buffer(D3D12_HEAP_TYPE_UPLOAD);
	}

	Dx12TextureBuffer::~Dx12TextureBuffer()
	{
		if (m_uploadBuffer != nullptr)
		{
			delete m_uploadBuffer;
			m_uploadBuffer = nullptr;
		}
	}

	void Dx12TextureBuffer::CreateTextureBuffer(const Dx12Device* device, UINT width, UINT height, UINT16 arraySize, UINT16 mipLevels) const
	{
		m_textureBuffer->CreateShaderResourceBuffer(device, D3D12_RESOURCE_STATE_COMMON, width, height, arraySize, mipLevels);

		const auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		const auto textureResourceDesc = m_textureBuffer->GetBufferDesc();
		ThrowIfDxFailed((*device)->CreateCommittedResource(
			&heapProperties, D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
			IID_PPV_ARGS(m_uploadBuffer->GetDxObjectAddressOf())));
	}

	void Dx12TextureBuffer::UploadTextureResource(const Dx12CommandList* commandList, const void* textureData) const
	{
		m_textureBuffer->UploadResource(commandList, m_uploadBuffer, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, textureData, GetTextureBufferSize());
	}

	void Dx12TextureBuffer::ClearUploadBuffer()
	{
		if (m_uploadBuffer != nullptr)
		{
			delete m_uploadBuffer;
			m_uploadBuffer = nullptr;
		}
	}

	const Dx12ShaderResourceBuffer* Dx12TextureBuffer::GetTextureBuffer() const
	{
		return m_textureBuffer.get();
	}

	const Dx12Buffer* Dx12TextureBuffer::GetTextureUploadBuffer() const
	{
		return m_uploadBuffer;
	}

	UINT64 Dx12TextureBuffer::GetTextureBufferSize() const
	{
		const auto desc = (*m_textureBuffer)->GetDesc();
		return desc.Width * desc.Height;
	}

	void Dx12TextureBuffer::DescribeShaderResource(const Dx12Device* device, Dx12DescriptorAllocator* allocator, UINT usedMipLevels, UINT mostDetailedMip) const
	{
		m_textureBuffer->DescribeAsSrv(device, allocator, usedMipLevels, mostDetailedMip);
	}
}
