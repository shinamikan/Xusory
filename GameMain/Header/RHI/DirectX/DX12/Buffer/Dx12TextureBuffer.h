#pragma once

#include "../../Common/DxDefine.h"

namespace XusoryEngine
{
	class Dx12Buffer;
	class Dx12CommandList;
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12ShaderResourceBuffer;
	class Dx12TextureBuffer
	{
	public:
		Dx12TextureBuffer();
		DELETE_COPY_OPERATOR(Dx12TextureBuffer);
		DELETE_MOVE_OPERATOR(Dx12TextureBuffer);
		~Dx12TextureBuffer();

		void CreateTextureBuffer(const Dx12Device* device, UINT width, UINT height, UINT16 arraySize = 1, UINT16 mipLevels = 0) const;
		void UploadTextureResource(const Dx12CommandList* commandList, const void* textureData) const;
		void ClearUploadBuffer();

		const Dx12ShaderResourceBuffer* GetTextureBuffer() const;
		const Dx12Buffer* GetTextureUploadBuffer() const;
		UINT64 GetTextureBufferSize() const;

		void DescribeShaderResource(const Dx12Device* device, Dx12DescriptorAllocator* allocator, UINT usedMipLevels = -1, UINT mostDetailedMip = 0) const;

	private:
		std::unique_ptr<Dx12ShaderResourceBuffer> m_textureBuffer;
		Dx12Buffer* m_uploadBuffer = nullptr;
	};
}
