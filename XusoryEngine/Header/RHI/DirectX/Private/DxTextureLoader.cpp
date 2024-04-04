#include "../DxTextureLoader.h"

#include "../DX12/Buffer/Dx12Buffer.h"
#include "../DX12/Buffer/Dx12ShaderResourceBuffer.h"

#include "../DX12/Dx12CommandList.h"
#include "../DX12/Dx12Device.h"

#include "../Common/DDSTextureLoader.h"

namespace XusoryEngine
{
	void DxTextureLoader::LoadDdsTextureFile(const std::wstring_view& texFilePath, const Dx12Device* device, const Dx12CommandList* commandList, Dx12ShaderResourceBuffer* textureBuffer, Dx12Buffer* uploadBuffer)
	{
		ThrowIfDxFailed(DirectX::CreateDDSTextureFromFile12(device->GetDxObjectPtr(), commandList->GetDxObjectPtr(),
			texFilePath.data(), textureBuffer->GetDxObjectComRef(), uploadBuffer->GetDxObjectComRef()));
		textureBuffer->SetSrvDimension(D3D12_SRV_DIMENSION_TEXTURE2D);
	}
}
