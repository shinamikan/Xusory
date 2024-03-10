#pragma once

#include "Dx12Buffer2D.h"

namespace XusoryEngine
{
	class Dx12DescriptorAllocator;
	class Dx12Device;
	class Dx12ShaderResourceBuffer : public Dx12Buffer2D
	{
	public:
		Dx12ShaderResourceBuffer() = default;

		void CreateShaderResourceBuffer(const Dx12Device* device, D3D12_RESOURCE_STATES initState,
			UINT width, UINT height, UINT16 arraySize = 1, UINT16 mipLevels = 0, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void ReSetBuffer(const Dx12DescriptorAllocator* allocator);

		D3D12_SRV_DIMENSION GetSrvDimension() const;
		const Dx12DescriptorHandle& GetSrvHandle() const;
		void SetSrvDimension(D3D12_SRV_DIMENSION dimension);

		void DescribeAsSrv(const Dx12Device* device, Dx12DescriptorAllocator* allocator, UINT usedMipLevels = -1, UINT mostDetailedMip = 0);

	private:
		D3D12_SRV_DIMENSION m_srvDimension = D3D12_SRV_DIMENSION_UNKNOWN;
		Dx12DescriptorHandle* m_srvHandle;
	};
}
