#pragma once

#include "Common/DxDefine.h"

namespace XusoryEngine
{
	class Dx12Buffer;
	class Dx12ShaderResourceBuffer;
	class Dx12CommandList;
	class Dx12Device;
	DLL_STATIC_CLASS(DxTextureLoader)
	{
	public:
		static void LoadDdsTextureFile(const std::wstring_view& texFilePath, const Dx12Device* device, const Dx12CommandList* commandList,
			Dx12ShaderResourceBuffer* textureBuffer, Dx12Buffer* uploadBuffer);
	};
}
